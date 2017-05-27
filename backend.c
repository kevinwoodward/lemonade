//backend.c
//CMPS 115 Lemonade music player

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>

#include "backend.h"

static const char FILEDIR[] = "/usr/share/lemonade/";

//char currentDirectory[512];

void createScreen(int killPrev) {
  //creates a new detachted screen terminal instance with the name lemonade

  if(killPrev == 0) {
    system("screen -d -m -S lemonade");
  } else if(killPrev == 1) {
    system("pkill screen; screen -d -m -S lemonade");
  } else {
    fprintf(stderr, "Internal error, bad usage of createScreen");
  }
  sleep(0.1);
  return;
}

void sendScreenCommand(char* command) {
  //takes the passed string and shoves it into the previously opened screen and auto executes it within said screen

  if(checkIfScreenExists() == 0) {
    return;
  }
  char str[300];
  strcpy(str, "screen -S lemonade -X stuff '");
  strcat(str, command);
  strcat(str, "^M'");
  char buffer[500];
  snprintf(
    buffer,
    sizeof(buffer),
    "screen -S lemonade -X stuff '%s^M 2> /dev/null' 2> /dev/null",
    command
  );
  //printf("%s\n", buffer);
  system(buffer);
  return;
}

void playPause() {
  sendScreenCommand(" ");
  return;
}

void endPlayback() {
  sendScreenCommand("q");
  return;
}

void startSingleSong(char* filePath) {
  //sendScreenCommand("cd ~/Documents/github/lemonade"); //TODO: change to /usr/share/lemonade after development
  createScreen(1);
  char fileStr[512];
  strcpy(fileStr, "mpg123 -C ");
  strcat(fileStr, filePath);
  sendScreenCommand(fileStr);
}

void startPlaylist(char* fileName) {
  createScreen(1);
  char playlistStr[100];
  strcpy(playlistStr, "mpg123 -C -@ ");
  strcat(playlistStr, FILEDIR);
  strcat(playlistStr, fileName);
  sendScreenCommand(playlistStr);
}

int createPlaylistFile(char* fileName, char* songFilePaths[]) {

  int i = 0;

  char fileInDir[200];
  sprintf(fileInDir, "%s%s", FILEDIR, fileName);
  printf("%s\n", fileInDir);
  FILE *fptr;
  fptr = fopen(fileInDir, "w");

  while(strcmp(songFilePaths[i], "") != 0) {
    printf("%s\n", songFilePaths[i]);
    fprintf(fptr, "%s\n", songFilePaths[i]);
    i++;
  }

  fclose(fptr);

  return 0;

}


int currentPlaylistToFile(char* playlistName) {
	return 0;
}

int countLines(){

	int numItems = 0;
	char buf[50];
	FILE* ls = popen("ls -d */ 2> /dev/null","r");

	while(fgets(buf,sizeof(buf),ls) !=0)
	{
		numItems++;
	}
	pclose(ls);

	ls = popen("ls *.mp3 2> /dev/null","r");
	while(fgets(buf,sizeof(buf),ls) !=0)
	{
		numItems++;
	}
	pclose(ls);
	return numItems;
}

void lsOutput(char** choices)
{
  char buf[1024];
  char* tok;
  int count = 0;

  FILE *ls = popen("ls -d */ 2> /dev/null", "r");

  ls = popen("ls *.mp3 -d */ 2> /dev/null", "r");
  while(fgets(buf,sizeof(buf),ls) !=0)
  {
  	tok = strtok(buf, "\n");
    if(str_end(tok, ".mp3")) {
      strcpy(choices[count], escapedString(tok));
    } else {
      strcpy(choices[count], tok);
    }

    count++;
  }

  //free(buf);
}

void createPlaylistFromDir(char* dirPath, char* fileName) {
  char fileInDir[200];
  sprintf(fileInDir, "%s%s", FILEDIR, fileName);

  struct dirent **namelist;
  int n, i = 0;
  FILE *fptr;
  fptr = fopen(fileInDir, "w");

  n = scandir(dirPath, &namelist, NULL, alphasort);
  if (n < 0) {
    perror("scandir");
  } else {
    while (i < n) {
      char *dot = strrchr(namelist[i]->d_name, '.');
      if (dot && !strcmp(dot, ".mp3")){
        fprintf(fptr, "%s/%s\n", dirPath, namelist[i]->d_name);
      }
      free(namelist[i]);
      ++i;
    }
    free(namelist);
  }
  fclose(fptr);

}

void setInitialDirectory() {
}

void upDirectory() {
  chdir("..");
}

void downDirectory(const char* dir) {
  chdir(dir);
}

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

int checkIfScreenExists() {
  char buf[512];
  FILE* check = popen("screen -S lemonade -Q select . ; echo $?", "r");
  fgets(buf, sizeof(buf), check);

  if(buf[0] == '0') {
    return 1;
  } else {
    return 0;
  }
}
