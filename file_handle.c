//! Contains file handling functions tailored to main.c
/** 
 *
 **/

////////////
//Includes//
////////////
#include <stdio.h>
#include <assert.h>
#include <string.h>

/////////////
//Functions//
/////////////

/** Function to check if a file is empty
 *
 *  This file assumes that the filestream is valid.
 *  It checks by setting the pointer to the last
 *  position of the filestream and checking if
 *  it is equal to zero, the start of the filestream.
 *  @param inFile the input, opened filestream
 *  @returns true(1) if empty, false(0) if not empty
 **/
int check_file_empty(FILE* inFile) {
    int error;
    
    // Check if file is empty
    error = fseek(inFile, 0, SEEK_END);
    assert(error != -1);
    if(!ftell(inFile)) {
        // File is empty, return 1
        return 1;
    }

    // Not empty, reset pointer and return
    fseek(inFile, 0, SEEK_SET);
    assert(error != -1);
    return 0;
}

/** Function to open user specified filepath
 *
 *  @param filepath a string file path to the possible existing file
 *  @param mode the mode to open the user file in
 *  @returns the file stream that it opened 
 *      (NOTE: returns 0 if no file exists or fopen fails)
 **/
FILE * open_file(const char* filepath, const char* mode) {
    fprintf(stdout, "Attempting to open your file...\n");
    //  Attempt to open file
    FILE* newFile = fopen(filepath, mode);
    if(newFile) {
        fprintf(stdout, "File opened! \n");
        if(check_file_empty(newFile)) {
            fprintf(stdout, "NOTE: File was empty.\n");
        }
    } else {
        fprintf(stderr, "Error: Opening %s failed. Does not exist or open error.\n", filepath);
    }
    return newFile;
}

/** Function greet and check + open file specified by user
 *   
 *  Assumes a valid filepath is in the first argument.
 *  @param argc number of arguments program is started with
 *  @param argv strings of arguments program is started with
 *  @param argNum the argument number that the user filepath is specified at
 *  @returns the filepath stream specified by the user
 *      (NOTE: returns 0 if there was none or invalid)
 **/
FILE* co_file(int argc, char** argv, int argNum) {
    char* mode = "r";
    FILE* inFile = NULL;

    //  Check if user put enough arguments in program
    if(argc > argNum) {
        printf("Your file is %s\n", argv[argNum]);

        //  Try to open the file
        inFile = open_file(argv[argNum], mode);
    } else {
        fprintf(stdout, "Error: There was no specified file to read.\n");
    }
    return inFile;
}
