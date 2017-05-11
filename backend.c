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

void startSingleSong(char* filePath) {
  system("killall screen");
  createScreen();
  sendScreenCommand("cd ~/Documents/github/lemonade");
  char fileStr[100];
  strcpy(fileStr, "mpg123 -C ");
  strcat(fileStr, filePath);
  sendScreenCommand(fileStr);
}



/*char * testList() {
  //in progress for getting ls output and handling accordingly
  FILE *ls = popen("ls *.mp3", "r");
  char buf[256];
  while (fgets(buf, sizeof(buf), ls) != 0) {
    //handle the contents of the ls here, including file vs dir, playback, cding, etc
    //printf("%s", buf);
  }
  pclose(ls);

  return buf;

}*/
