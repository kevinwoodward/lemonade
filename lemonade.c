#include <ncurses.h>

int main()
{
  initscr();                //Start ncurses mode
  printw("Hello World!");   //'print' hello World
  refresh();                //Write buffer to screen
  getch();                  //Wait for user input
  endwin();                 //End curses mode
}
