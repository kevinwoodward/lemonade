#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void playpause();
void startProcess();
void loadSongFile();
char* getPidString();

int main(int argc, char **argv)
{

  /*int pflag = 0;
  int fileflag = 0;
  char *cvalue = NULL;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "pf:")) != -1) {
    switch (c)
      {
      case 'p':
        playpause();
        printf("%s\n", "here we want to play/pause currently playing song");
        break;
      case 'f':
        cvalue = optarg;
        printf("%s\n", "here we want to take a filename as a param and play it");
        break;
      case '?':
        if (optopt == 'f')
          fprintf (stdout, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stdout, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stdout,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
    }*/
  startProcess();
  loadSongFile();
  return 0;

}

void playpause() {
  /*system("cat | mpg123 *.mp3");
  int pid = system("pidof mplayer");
  char pidstr[10];
  sprintf(pidstr, "%d", pid);
  char str[150];
  strcpy(str, "echo -n p > /proc/");
  strcat(str, pidstr);
  strcat(str, "/cd/0");
  sprintf(str, "%d", pid);
  system(str);*/
  return;
}

void startProcess() {
  system("cat | mpg123 -R");
}

void loadSongFile() {
  char str[150];
  char* pidStr = getPidString();
  strcpy(str, "echo \"load em.mp3\" > /proc/");
  strcat(str, pidStr);
  strcat(str, "/fd/0");
  system(str);
}

char* getPidString() {
  int procID = system("pidof mpg123");
  static char pidStr[10];
  sprintf(pidStr, "%d", procID);
  return pidStr;
}
