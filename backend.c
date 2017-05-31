//backend.c
//CMPS 115 Lemonade music player

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <ncurses.h>

#include "backend.h"

#include "helpers.h"

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
    "screen -S lemonade -X stuff '%s^M'",
    command
  );

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

  FILE *ls;
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

int countAll() {
  char buf[1024];
  int itemCount = 0;
  FILE* ls;
  ls = popen("ls 2> /dev/null", "r");
  while(fgets(buf,sizeof(buf), ls) !=0) {
    itemCount++;
  }
  return itemCount;
}

void lsAll(char** choices) {
  char buf[1024];
  char* tok;
  int count = 0;
  FILE* ls;
  ls = popen("ls 2> /dev/null", "r");
  while(fgets(buf,sizeof(buf),ls) !=0) {
    tok = strtok(buf, "\n");
    strcpy(choices[count], tok);
    count++;
  }

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

void nextSong() {
  sendScreenCommand("f");
}

void prevSong() {
  sendScreenCommand("d");
}

void restartSong() {
  sendScreenCommand("b");
}

void upDirectory() {
  char dir[512];
  getcwd(dir, sizeof(dir));
  if(strlen(dir) < 6) {
    //checks to make sure user isn't going into files without root access, prevents segfaults and security concerns
    return;
  }
  chdir("..");
}

void downDirectory(const char* dir) {
  chdir(dir);
}

void toDirectory(char* dir) {
  chdir(dir);
}

void startVisualizer() {
  system("x-terminal-emulator -e cava");
}

void editTags(const char* fileName) {

  int ch;

  //get and display current tag info
  char tagCommand[128];
  char tagGet[512];
  sprintf(tagCommand, "id3v2 --list-rfc822 %s", fileName);
  FILE* tags = popen(tagCommand, "r");
  int count = 0;
  while(fgets(tagGet, sizeof(tagGet), tags) !=0) {
    if(count > 14) {
      break;
    }
    mvaddnstr(7 + count, 35, strtok(tagGet, "\n"), 39);
    count++;
  }
  pclose(tags);

  //option selection and string building
  char buf[512];
  strcpy(buf, "id3v2 ");
  ch = getTagOptionChar();
  switch (ch) {
    case '\e':
      return;
      break;
    case 'a':
      strcat(buf, "--artist ");
      break;
    case 'l':
      strcat(buf, "--album ");
      break;
    case 's':
      strcat(buf, "--song ");
      break;
    case 'g':
      strcat(buf, "--genre ");
      break;
    case 'y':
      strcat(buf, "--year ");
      break;
    case 't':
      strcat(buf, "--track ");
      break;
    default:
       break;
  }


  char textInput[256];
  echo();
  mvaddstr(20, 7, "Value: ");
  mvgetstr(20, 15, textInput);

  //getstr(textInput);
  strcpy(textInput, escapedString(textInput));
  strcat(buf, textInput);
  strcat(buf, " ");
  strcat(buf, fileName);
  strcat(buf, " 2> /dev/null");

  noecho();

  system(buf);

}

char getTagOptionChar() {
  char ch = getch();
  if(
    ch == 'a' ||
    ch == 'l' ||
    ch == 's' ||
    ch == 'g' ||
    ch == 'y' ||
    ch == 't' ||
    ch == '\e'
  ) {
    return ch;
  } else {
    getTagOptionChar();
  }
  return ch;
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
