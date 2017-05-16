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
  createScreen(1);
  char fileStr[100];
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

  //int len;
  // struct dirent *pDirent;
  // DIR* pDir;
  // pDir = opendir (dirPath);
  // while ((pDirent = readdir(pDir)) != NULL) {
  //   printf ("%s\n", pDirent->d_name);
  // }
  // closedir(pDir);



  // FILE *fp = popen("ls *.mp3", "r");
  // char* buf[1024];
  // while(fgets(buf, sizeof(buf), fp) == 0) {
  //   printf(buf);
  // }
}

//ON HOLD
// int currentPlaylistToFile(char* playlistName) {
//   char pl[300];
//   sendScreenCommand("l");
//   printf("%s\n", pl);
//   return 1;
// }
