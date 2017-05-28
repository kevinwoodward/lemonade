#include <ctype.h>
#include <string.h>

#include "helpers.h"

#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

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
