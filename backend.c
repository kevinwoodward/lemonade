//backend.c
//CMPS 115 Lemonade music player

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "backend.h"

void createScreen() {
  //creates a new detachted screen terminal instance with the name lemonade
  system("screen -d -m -S lemonade");
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
  system(buffer);
  return;
}

void playpause() {
  //send the space char to the screen, causing a pause or play depending on current state.
  sendScreenCommand(" ");
  return;
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

int currentPlaylistToFile(char* playlistName) {
  
}
