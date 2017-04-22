//! The core of fake, reading and executing the fakefile
/**
 *  The read_fake_file function first calls find_target
 *  in order to find the starting point of a fakefile
 *  for commands. Then it reads commands and passes them to
 *  execute_fake
 *
 *  Execute_fake forks for the child to execute and waits
 *
 *  Child calls execute_bash_command, which then calls
 *  parse_and_exec which parses the command and runs
 *  execvp. If there is an error, execute_bash_command
 *  prints it and returns.
 *
 *
 **/

////////////
//Includes//
////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/////////////
//Functions//
////////////

/** Finds a target string in a file for file pointer
 *
 *  (NOTE: Assumes that the params are valid)
 *  Sets the file pointer to the next line after
 *  Assumes that the actual target is the target param appended with colon.
 *  @param inFile the input file
 *  @param inTarget the target to find
 *  @returns filestream with offset position of next line of target
 *      (NOTE: returns NULL if target was not found in file)
 **/
FILE* find_target(FILE* inFile, char* inTarget) {
    char* currentLine = NULL;
    size_t currentLineSize = 0;
    ssize_t charactersRead = 0;
    //  Setup what the target actually looks like for getline
    char* target = malloc(sizeof(strlen(inTarget) + 1 + 1 + 1)); // For ":" "\n" and "\0" respectively
    //  Copy strings
    char* tempTarget = target;
    char* tempInTarget = inTarget;
    while((*tempTarget++ = *tempInTarget++)) {}
    strcat(target, ":\n");

    // Read lines until eof
    while((charactersRead = getline(&currentLine, &currentLineSize, inFile)) != -1) {
        if(!strcmp(currentLine, target)) {
            return inFile;
        }
        //  Prepare to get next line.
        free(currentLine);
        currentLine = NULL;
        currentLineSize = 0;
    }
    fprintf(stderr, "Error: Couldn't find target %s\n", inTarget);
    free(target);
    return NULL;
}


/** Tokenizes a char* to an char** via delimiter
 *
 *  (NOTE: returns malloced char**, needs to be freed later)
 *  @param inString the input string
 *  @param delim the delimiter specification
 *  @param outStrings unallocated char** to return
 *  @return dynamic char** array
 **/
char** get_delim_char_array(char* inString, const char* delim) {
    char** outStrings = malloc(sizeof(char*));
    char* token = NULL;
    int i;
    
    token = strtok(inString, delim);
    for(i = 0; token; i++) {
        outStrings = realloc(outStrings, sizeof(char*) * i+1);
        outStrings[i] = malloc(strlen(token)+1);
        outStrings[i] = token;

        //  Copy strings
        char* tokenIter = token;
        char* outStringIter = outStrings[i];
        while((*tokenIter++ = *outStringIter++)) {}

        token = strtok(NULL, delim);
    }
    outStrings = realloc(outStrings, sizeof(char*) * i);
    outStrings[i] = '\0';
    return outStrings;
}

/** Helper function for child to parse and execute a command
 *
 *  @param command the command to be executed
 **/

void parse_and_exec(char* command) {
    int execError;

    /*
    //  If command is in the current directory, execute with execl immediately
    if(access(command, X_OK)) {
        execError = execl(command, params, (char*) NULL);
        if(execError == -1) {
            fprintf(stderr, "Error: Child failed its execlp\n");
        }
    }*/
    
    // cheating for segfault, delete later.
    /*if(!strncmp(command, "./", 2)) {
        command+=2;
    }*/
    if(strstr(command, ">")) {
        execlp("bash", "bash", "-c", command, (char*) NULL);
    }

    //  Set up params for execvp
    char** argv = get_delim_char_array(command, " "); // Can't free?
    
    //  Execvp
    execError = execvp(argv[0], argv);   
    if(execError == -1) {
        fprintf(stderr, "Error: Child failed its execvp\n");
        //  WILL LEAK PARAMSARRAY
    }

}

/** Executes a command in shell
 *
 *  Makes a child via fork to exec a shell command
 *  @param command bash command to execute
 *  @returns 0 if executed, 1 in failure.
 **/
int execute_bash_command(char* command) {
    pid_t currentPID = fork();

    //  Check if fork succeeded
    if(currentPID < 0) {
        fprintf(stderr, "Error: Fork failed in execute_bash_command\n");
    }

    if(currentPID == 0) { // Child
        fprintf(stdout, "Running %s\n", command);
        parse_and_exec(command);
        exit(1);
    } else {    // Parent
        int status = 0;
        waitpid(currentPID, &status, 0);
        if(WIFSIGNALED(status)) {
            fprintf(stderr, "Error: Child was terminated by a signal\n");
        }
        return status;
    }
}

/** Executes the lines of fake
 *
 *  Assumes all lines of fake are bash commands.
 *  @see fork
 *  @see execlp
 *  @returns 
 **/
void execute_fake(FILE* inFile) {
    char* currentLine = NULL;
    size_t currentLineSize = 0;
    ssize_t charactersRead = 0;
    // Read lines until an empty line (newline)
    while((charactersRead = getline(&currentLine, &currentLineSize, inFile)) > 1) {
        //  Get rid of newline
        if(currentLine[charactersRead-1] == '\n') {
            currentLine[charactersRead-1] = '\0';
        }
        char* command = currentLine;
        //  Ignore beginning whitespace
        while((command[0] == ' ')) {
            command++;
        }

        if(execute_bash_command(command)) {
            fprintf(stderr, "Execute bash failed.\n");
        }
        //  Prepare to get next line.
        free(currentLine);
        currentLine = NULL;
        currentLineSize = 0;
    }
}

/** Reads and executes fakefile starting from target
 *  
 *  @param inFile file to read from
 *  @param target target to search for
 *  @returns an exit status number
 **/
int read_fake_file(FILE* inFile, char* target) {
    fprintf(stdout, "Reading...\n");
    //  Setup for target
    inFile = find_target(inFile, target);
    //  Execute on target
    if(inFile) {
        execute_fake(inFile);
    }
    //  Couldnt find target, stop
    return 1;
}
