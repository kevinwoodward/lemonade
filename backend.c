//backend.c
//CMPS 115 Lemonade music player

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "backend.h"

static const char FILEDIR[] = "/usr/share/lemonade/";

void createScreen(int killPrev) {
  //creates a new detachted screen terminal instance with the name lemonade
  
  if(killPrev == 0) {
    printf("only make\n");
    system("screen -d -m -S lemonade");
  } else if(killPrev == 1) {
    printf("kill and make\n");
    system("pkill screen; screen -d -m -S lemonade");
  } else {
    fprintf(stderr, "Internal error, bad usage of createScreen");
  }
  return;
}

void sendScreenCommand(char* command) {
  //takes the passed string and shoves it into the previously opened screen and auto executes it within said screen
  char str[300];
  strcpy(str, "screen -S lemonade -X stuff '");
  strcat(str, command);
  strcat(str, "^M'");
  char buffer[500];
  snprintf(
    buffer,
    sizeof(buffer),
    "screen -S lemonade -X stuff '%s^M'",
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
  char fileStr[100];
  strcpy(fileStr, "mpg123 -C ");
  strcat(fileStr, filePath);
  sendScreenCommand(fileStr);
}

void startPlaylist(char* fileName) {
  char playlistStr[100];
  strcpy(playlistStr, "mpg123 -C -@ ");
  strcat(playlistStr, FILEDIR);
  strcat(playlistStr, fileName);
  sendScreenCommand(playlistStr);
}

int createPlaylistFile(char* fileName, char* songFilePaths[]) {

  int i = 0;

  FILE *fptr;
  fptr = fopen(fileName, "w");

  //while(songFilePaths[i] != "") {
  while(strcmp(songFilePaths[i], "") != 0) {
    fprintf(fptr, "%s\n", songFilePaths[i]);
    i++;
  }

  fclose(fptr);

  return 0;

}


//ON HOLD
// int currentPlaylistToFile(char* playlistName) {
//   char pl[300];
//   sendScreenCommand("l");
//   printf("%s\n", pl);
//   return 1;
// }
