#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  system("cat | mplayer *.mp3");
  int pid = system("pidof mplayer");
  char pidstr[10];
  sprintf(pidstr, "%d", pid);
  char str[150];
  strcpy(str, "echo -n p > /proc/");
  strcat(str, pidstr);
  strcat(str, "/cd/0");
  sprintf(str, "%d", pid);
  system(str);
  return 0;
}
