//! Main function and set up of fake
/**
 * main.c shows welcome and attempts to run fake
 * by first opening a valid fakefile and then
 * reading and executing it on a given target.
 * @see fake.h
 * @see file_handle.h
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "main.h"
#include "file_handle.h"
#include "fake.h"

/////////////
//Functions//
/////////////

/** Function that returns a string pointer of an passed argument
 *
 *  @param argc number of arguments passed in program
 *  @param argv array of strings passed into program
 *  @returns string pointer to of given argument number
 *      (NOTE: returns 0 if invalid)
 **/
char* get_argument_string(int argc, char** argv, int argNum) {
    char* argString = NULL;
    if(argc > 2) {
        argString = argv[argNum];
    } else {
        fprintf(stderr, "Missing the %dth string argument\n", argNum);
    }
    return argString;
}

/** Function that returns name of current running program
 *
 *  Assumes argv is initialized and has content
 *  @param argv argument strings program was passed with
 **/
char* get_program_name(char** argv) {
    return argv[0]+2;
}

/** Main function for the fake program.
 *
 *  First opens a valid Fakefile,
 *  and then calls to execute it.
 *  @param argc
 *  @param argv
 **/
int main(int argc, char** argv) {
    char* name = get_program_name(argv);
    fprintf(stdout, "Welcome to %s!\n", name);
    fprintf(stdout, "%s should be opened in the following form: ", name);
    fprintf(stdout, "%s Fakefile target\n", argv[0]);

    // Check arguments and open file
    FILE* userFile = co_file(argc, argv, 1);
    if(userFile) {
        char* target = get_argument_string(argc, argv, 2);
        fprintf(stdout, "Starting to read file...\n");
        read_fake_file(userFile, target);
    }
    printf("%s has finished all commands and exited\n", name);
    return 0;
}
