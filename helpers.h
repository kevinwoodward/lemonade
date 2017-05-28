//helpers.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef HELPERS_H
#define HELPERS_H

//Trims whitespace from beginning and end of char array for sanitization
char *trimwhitespace(char *str);


//Returns name of file with working current directory prepended
char *getPath(const char* fileName);

#endif 
