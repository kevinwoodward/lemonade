#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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

void testList() {
  //in progress for getting ls output and handling accordingly
  FILE *ls = popen("ls --file-type", "r");
  char buf[256];
  while (fgets(buf, sizeof(buf), ls) != 0) {
    //handle the contents of the ls here, including file vs dir, playback, cding, etc
    printf("%s", buf);
  }
  pclose(ls);

}

int main(int argc, char **argv) {

  if(argc <= 1) {
    printf("No option specified! Currently:\n-s for start, followed by a filepath to an mp3\n-p for play/pause\n-k for kill\n-e to enter screen\n-l to do the test ls function\n");
  }

  int argCase;
  char* filePath = NULL;

  //handles flag options
  while((argCase = getopt(argc, argv, "ps:kel")) != -1) {
    switch (argCase) {
      case 'p':
        playpause();
        return 0;
        break;
      case 's':
        filePath = optarg;
        break;
      case 'k':
        system("killall screen");
        return 0;
        break;
      case 'e':
        system("screen -r");
        break;
      case 'l':
        testList();
        break;
      case '?':
        if (optopt == 's') {
          fprintf (stdout, "Option -%c requires an argument.\n", optopt);
          return 1;
        }
        else if (isprint (optopt)) {
          fprintf (stdout, "Unknown option `-%c'.\n", optopt);
          return 1;
        }
        else {
          fprintf (stdout,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
                   return 1;
        }
    }
  }

  //starts process if command is -s with specified song
  if(filePath != NULL) {
    system("killall screen");
    createScreen();
    sendScreenCommand("cd ~/Documents/github/lemonade");
    char fileStr[100];
    strcpy(fileStr, "mpg123 -C ");
    strcat(fileStr, filePath);
    sendScreenCommand(fileStr);
  }

  return 0;
}
