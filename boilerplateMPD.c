
#include <stdio.h>
#include <stdlib.h>
int main()
{
  system("cat | mplayer *.mp3");
  int pid = system("pidof mplayer")
  system("echo -n p > /proc/" + pid + "/cd/0");
  return 0;
}
