#ifndef FILE_HANDLE_H_ /*   Include guard   */
#define FILE_HANDLE_H_

/////////////
//Functions//
/////////////

// File Status
int check_file_empty(FILE* inFile);

// File Opening and Reading
FILE* open_file(const char* filepath, const char* mode);
FILE* co_file(int argc, char** argv, int argNum);

#endif  //  FILE_HANDLE_H_
