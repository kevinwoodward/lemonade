//helpers.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef HELPERS_H
#define HELPERS_H

//Trims whitespace from beginning and end of char array for sanitization
char *trimwhitespace(char *str);


//Returns name of file with working current directory prepended
char *getPath(const char* fileName, int shouldEscape);

//Checks if a string ends with another string
int str_end(const char *, const char*);

//Escapes certain characters if needed by calling command
char* escapedString(char* buffer);

#endif
