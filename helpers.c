#include <ctype.h>
#include <string.h>

#include "helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "backend.h"



char *trimwhitespace(char *str) {
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}


//getPath()
//Returns name of file with current directory prepended
char *getPath(const char* fileName){
	FILE* pwd = popen("pwd","r");
	char* buf = calloc(512, sizeof(char));
	fgets(buf,sizeof(buf),pwd);
	pclose(pwd);
	strcpy(buf, strtok(buf, "\n")); //removes newline
	strcat(buf, "/");
	strcat(buf, fileName);
	strcpy(buf, escapedString(buf));
	return buf;
}


//str_end()
//Checks if a string ends with another string
int str_end(const char *s, const char *t)
{
  size_t ls = strlen(s); // find length of s
  size_t lt = strlen(t); // find length of t
  if (ls >= lt)  // check if t can fit in s
  {
      // point s to where t should start and compare the strings from there
      return (0 == memcmp(t, s + (ls - lt), lt));
  }
  return 0; // t was longer than s
}


//escapedString()
//Escapes certain characters if needed by calling command
char* escapedString(char* buffer){

  int bufferLen = strlen(buffer);
  int spaceCount = 0;
  for(int n = 0; n < bufferLen; n++) {
    if(buffer[n] == ' ') {
      spaceCount++;
    }
  }

  char* str = calloc(bufferLen + spaceCount , sizeof(char));
  int currentNumberOfSpaces = 0;

  for(int i = 0; i < bufferLen; i++) {
    if(buffer[i] == ' ' && buffer[i-1] != '\\') {
      str[i + currentNumberOfSpaces] = '\\';
      str[i + currentNumberOfSpaces + 1] = ' ';
      currentNumberOfSpaces++;
    } else {
      str[i + currentNumberOfSpaces] = buffer[i];
    }
  }

  return str;
}
