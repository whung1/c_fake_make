
/** Seperates first word of a input string from the rest.
 *  
 *  NOTE: NEED TO FREED
 *  @param inString the input string
 *  @returns dynamic char* of the first word
 **/
char* get_first_word(char* inString) {
    char* token = strstr(inString, " ");
    int size = token - inString + 1;
    char* word = malloc(size);

    char* wordIter = word;
    int i;
    for(i = 0; i < size; i++) {
        *wordIter = *inString;
        wordIter++;
        inString++;
    }
    *wordIter = '\0';

    return word;
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
    
    token = strstr(inString, delim);
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
    return outStrings;
}

/** Parses a string and returns a new string with escapes for all quotes in it
 *
 *  Copies inString char by char into outString, except when it
 *  hits a quote, and then reallocs outString to the former size+1
 *  and then puts a \"
 *  @param inString input string to change
 *  @returns malloced char* string.
 **/
char* escape_quotes(char* inString) {
    int size = strlen(inString) + 1;

    fprintf(stderr, "%s\n", inString);
    char* outString = malloc(size);
    char* outStringIter = outString;
    char* inStringIter = inString;
    while(*inStringIter) {
        if(*(inStringIter) == '\"') {
            //  Escape the quote in new string
            size++;
            outString = realloc(outString, size);
            *outStringIter = '\\';
            outStringIter++;
            *outStringIter = '\"';
        } else {
            *outStringIter = *inStringIter; 
        }
        inStringIter++;
        outStringIter++;
        fprintf(stderr, "outString: %s\n", outString);
    }
    *(outStringIter) = '\0';
    return outString;
}

