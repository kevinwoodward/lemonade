#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void createScreen() {
  system("screen -d -m -S lemonade");
}

void sendScreenCommand(char* command) {
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
  system("screen -S lemonade -X stuff ' ^M'");
  return;
}

int main(int argc, char **argv) {

  if(argc <= 1) {
    printf("No option specified! Currently: -s for start, -p for play/pause, -k for kill.\n");
  }

  int argCase;
  char* filePath = NULL;


  while((argCase = getopt(argc, argv, "ps:k")) != -1) {
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
      default:
        printf("no\n");
    }
  }

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
