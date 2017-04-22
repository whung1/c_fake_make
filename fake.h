#ifndef FAKE_H_ /*  Include guard   */
#define FAKE_H_

/////////////
//Functions//
/////////////

// Helper functions
FILE* find_target(FILE* inFile, char* target);
char** get_delim_char_array(char* inString, const char* delim);
void parse_and_exec(char* command);


// Main functions
int execute_bash_command(char* command);
int execute_fake(FILE* inFile);
int read_fake_file(FILE* inFile, char* target);

#endif  //  FAKE_H_
