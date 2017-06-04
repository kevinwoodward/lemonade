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
#include "tests/CuTest.h"

#include "helpers.h"

static const char FILEDIR[] = "/usr/share/lemonade/";

//char currentDirectory[512];

void createScreen(int killPrev) {
  //creates a new detachted screen terminal instance with the name lemonade

  if(killPrev == 0) {
    system("screen -d -m -S lemonade"); //create detached screen with name lemonade
  } else if(killPrev == 1) {
    system("pkill screen; screen -d -m -S lemonade"); //kill and create detached screen with name lemonade
  } else {
    fprintf(stderr, "Internal error, bad usage of createScreen");
  }
  sleep(0.1); //To ensure screen is invoked (async) before anything is sent to it
  return;
}

void sendScreenCommand(char* command) {
  //takes the passed string, shoves into the previously opened screen, and auto executes it within said screen

  if(checkIfScreenExists() == 0) {
    return; //if no screen exists
  }

  //building string to send
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

  system(buffer); //execute command
  return;
}

void playPause() {
  sendScreenCommand(" "); //Pass literal press of space bar to screen
  return;
}

void endPlayback() {
  sendScreenCommand("q"); //Pass literal press of q key to screen
  return;
}

void startSingleSong(char* filePath) {
  createScreen(1);
  char fileStr[512];
  strcpy(fileStr, "mpg123 -C "); //building command to invoke mpg123 with controls enabled to specified song
  strcat(fileStr, filePath);
  sendScreenCommand(fileStr);
}

void startPlaylist(const char* fileName) {
  createScreen(1);

  char subName[256];

  //check if the playlist has a forward slash at the end or not (both cases occur)
  if(fileName[strlen(fileName) - 1] == '/') {
    int nameLen = strlen(fileName);
    strcpy(subName, fileName);
    subName[nameLen - 1] = '\0';
  } else {
      strcpy(subName, fileName);
  }

  char playlistStr[100];
  strcpy(playlistStr, "mpg123 -C -@ "); //building command to invoke mpg123 with controls enabled with playlist file parameter as input list
  strcat(playlistStr, FILEDIR);
  strcat(playlistStr, subName);
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
	FILE* ls = popen("ls -d */ 2> /dev/null","r"); //popen ls to get directories only

	while(fgets(buf,sizeof(buf),ls) !=0)
	{
		numItems++;
	}
	pclose(ls);

	ls = popen("ls *.mp3 2> /dev/null","r"); //popen ls to get mp3s only
	while(fgets(buf,sizeof(buf),ls) !=0)
	{
		numItems++;
	}
	pclose(ls);
	return numItems;
}

void lsOutput(char** choices) {
  char buf[1024];
  char* tok;
  int count = 0;

  FILE *ls;
  ls = popen("ls *.mp3 -d */ 2> /dev/null", "r"); //popen ls to get all dirs and mp3s
  while(fgets(buf,sizeof(buf),ls) !=0) {
  	tok = strtok(buf, "\n"); //remove trailing carriage return
    if(str_end(tok, ".mp3")) {
      //if mp3, escape spaces in string and put into char**
      strcpy(choices[count], escapedString(tok));
    } else {
      //if dir, put into char**
      strcpy(choices[count], tok);
    }

    count++;
  }
}

int countAll() {
  char buf[1024];
  int itemCount = 0;
  FILE* ls;
  ls = popen("ls 2> /dev/null", "r"); //popen ls to get total number of contents in dir
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
  ls = popen("ls 2> /dev/null", "r"); //popen ls to get names of all contents in dir
  while(fgets(buf,sizeof(buf),ls) !=0) {
    tok = strtok(buf, "\n");
    strcpy(choices[count], tok);
    count++;
  }

}

void createPlaylistFromDir(char* dirPath, const char* fileName) {
  char fileInDir[200];

  //remove '/' char at end of dir name
  char subName[256];
  int nameLen = strlen(fileName);
  strcpy(subName, fileName);
  subName[nameLen - 1] = '\0';

  //concat path and name
  sprintf(fileInDir, "%s%s", FILEDIR, subName);

  struct dirent **namelist;
  int n, i = 0;
  FILE *fptr;
  fptr = fopen(fileInDir, "w");

  n = scandir(dirPath, &namelist, NULL, alphasort);
  if (n < 0) {
    perror("scandir");
  } else {
    while (i < n) {
      //for each result, print name to file
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
  sendScreenCommand("f"); //Pass literal press of f key to screen
}

void prevSong() {
  sendScreenCommand("d"); //Pass literal press of d key to screen
}

void restartSong() {
  sendScreenCommand("b"); //Pass literal press of b key to screen
}

void upDirectory() {
  char dir[512];
  getcwd(dir, sizeof(dir));
  if(strlen(dir) < 6) {
    //checks to make sure user isn't going into files without root access, prevents root-related segfaults and security concerns
    return;
  }
  chdir(".."); //working directory up one level
}

void downDirectory(const char* dir) {
  chdir(dir); //to specified dir (const)
}

void toDirectory(char* dir) {
  chdir(dir); //to specified dir
}

void startVisualizer() {
  system("xterm -e \"cava\" &"); //invoke cava for alsa in new xterm window and pass control back to parent process
}

void editTags(const char* fileName) {

  int ch;

  //get and display current tag info
  printCurrentTagInfo(fileName);

  //option selection and string building
  char buf[512];
  strcpy(buf, "id3v2 ");
  ch = getTagOptionChar(); //Loop over getting input key until one of the cases below is chosen

  //build string to be called based on selection, or quit tag menu
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
  curs_set(2); //enable cursor for clarity
  echo(); //echo user input to screen
  mvaddstr(20, 7, "Value: "); //put string on screen for prompt
  mvgetstr(20, 15, textInput); //get input string and echo

  //finish building string
  strcpy(textInput, escapedString(textInput));
  strcat(buf, textInput);
  strcat(buf, " ");
  strcat(buf, fileName);
  strcat(buf, " 2> /dev/null");

  noecho(); //end echoing
  curs_set(0); //turn cursor off

  system(buf); //execute tag edit

}

char getTagOptionChar() {
  //loops over getting input until one of the acceptable options is pressed
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

void printCurrentTagInfo(const char* fileName) {
  char tagCommand[128];
  char tagGet[512];
  sprintf(tagCommand, "id3v2 --list-rfc822 %s", fileName); //building string to retrieve tag info for specified mp3
  FILE* tags = popen(tagCommand, "r");
  int count = 0;
  while(fgets(tagGet, sizeof(tagGet), tags) !=0) {
    if(count > 14) {
      //to prevent border clipping
      break;
    }
    mvaddnstr(7 + count, 35, strtok(tagGet, "\n"), 39); //print strings in ncurses window, trailing carriage returns removed
    count++;
  }
  pclose(tags);
}

void displayArt(const char* selectedItemName) {

  if(str_end(selectedItemName, ".mp3") != 1) {
    //if selected item is not an mp3
    return;
  }

  //building image name as a hidden file (mp3 filename prepended with '.' and ending as .jpg)
  char imgName[128];

  strcpy(imgName, ".");
  strcat(imgName, selectedItemName);
  strcat(imgName, ".jpg");

  if( access(imgName, F_OK ) != -1) {
    // image file already exists
    invokeImageToAscii(imgName);
    return;
  } else {
    extractImageFromMp3(selectedItemName, imgName);
  }

  if(access(imgName, F_OK) != -1) {
    //file created successfully, now exists
    invokeImageToAscii(imgName);
  } else {
    //invoke new xterm with jp2a to convert extracted image to ascii (with color!)
    system("xterm -hold -geometry 50x2 -e echo No embedded album art for selected song! & 2> /dev/null");
    return;
  }
}

void extractImageFromMp3(const char* selectedItemName, char* imgName) {
  //builds string to invoke ffmpeg to extract image from mp3.
  //Detail: treats mp3 as video input stream as 1 frame and prints result to mp3 format. Only command line method we could find for embedded mp3 art
  char buf[512];
  strcpy(buf, "ffmpeg -i ");
  strcat(buf, selectedItemName);
  strcat(buf, " -an -vcodec copy ");
  strcat(buf, imgName);
  strcat(buf, " 2> /dev/null");
  system(buf);
}

void invokeImageToAscii(char* imgName) {
  //uses jp2a with extracted image to display art in new xterm window with some pretty parameters (color, size, bg color, etc) and passes control back to parent process
  char displayCommand[512];
  strcpy(displayCommand, "xterm -hold -geometry 100x50 -e jp2a -b --color --fill --background=dark ");
  strcat(displayCommand, imgName);
  strcat(displayCommand, " & 2> /dev/null");
  system(displayCommand);
}

int checkIfScreenExists() {
  char buf[512];
  FILE* check = popen("screen -S lemonade -Q select . ; echo $?", "r"); //queries all active screens and attempts to find screen lemonade
  fgets(buf, sizeof(buf), check);

  if(buf[0] == '0') {
    return 1;
  } else {
    return 0;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TESTS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestCountLines(CuTest *tc) {
  //No input
  int actual = countLines();
  int expected = 8; //Change the expected value based on your files. Expected = sum(#directories + #mp3s)
  CuAssertIntEquals(tc, expected, actual);
}

void TestCountAll(CuTest *tc) {
  int actual = countAll();
  int expected = 29; //Change the expected value based on your files. Expected = result of the command "ls | wc -l" in the project directory
  CuAssertIntEquals(tc, expected, actual);
}

void TestCheckIfScreenExistsTrue (CuTest *tc) {
  //setup screen
  createScreen(1);

  int actual = checkIfScreenExists();
  int expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void TestCheckIfScreenExistsFalse (CuTest *tc) {
  //kill screens
  system("pkill screen");

  int actual = checkIfScreenExists();
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}

void TestLsOutput(CuTest *tc) {
  //setup
  int num = countLines();

  char** actual = calloc(num, sizeof(char*));
	for(int i=0; i<num; i++){
		actual[i] = calloc(30, sizeof(char));
	}

  char** expected = calloc(num, sizeof(char*));
  for(int j=0; j<num; j++){
		expected[j] = calloc(30, sizeof(char));
	}
  //end setup

  /*char** actual =*/ lsOutput(actual); //modifies passed value

  //change these values based on your current file structure. Number of elements = number of mp3s and directories, values are the names of them
  strcpy(expected[0], "docs/");
  strcpy(expected[1], "em.mp3");
  strcpy(expected[2], "humble.mp3");
  strcpy(expected[3], "In\\ The\\ Dark.mp3");
  strcpy(expected[4], "InTheDark.mp3");
  strcpy(expected[5], "Megan.mp3");
  strcpy(expected[6], "tests/");
  strcpy(expected[7], "This Will Destroy You - Another Language/");


  for(int k = 0; k < num; k++) {
    CuAssertStrEquals(tc, expected[k], actual[k]);
  }

}

// void TestGetTagOptionChar(CuTest *tc) {
//   char actual = getTagOptionChar();
//   char expected = 'e';
//
//   CuAssertIntEquals(tc, expected, actual);
// }

CuSuite* backendGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestCountLines);
  SUITE_ADD_TEST(suite, TestCountAll);
  SUITE_ADD_TEST(suite, TestCheckIfScreenExistsTrue);
  SUITE_ADD_TEST(suite, TestCheckIfScreenExistsFalse);
  SUITE_ADD_TEST(suite, TestLsOutput);
  //SUITE_ADD_TEST(suite, TestGetTagOptionChar);
  return suite;
}
