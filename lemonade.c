#include <ncurses.h>

int main()
{
  initscr();                        //Start ncurses mode
  printw("                                     .@@#+,                                    \n");
  printw("                                    :@@++#@@@`                                 \n");
  printw("                                   #@.@:::::+@+                                \n");
  printw("                                 :#@,,@:;::::,@'                               \n");
  printw("                                '@,,,,#@:::::::@                               \n");
  printw("                               .@.,,,,,@,:;::::#@                              \n");
  printw("                               @:,,,,,,#@::::::,@                              \n");
  printw("                              :@,,,,,,::@@::::::@;                             \n");
  printw("                              @:,,:,,,,,:@@'::::'@                             \n");
  printw("                              @,:,,:,,,,,:;@@@@@@@                             \n");
  printw("                             `@:,,,,,,,,,,::::;@.                              \n");
  printw("                             ,@:,,,,,,,,,,,,,,,@                               \n");
  printw("                             :@,:,,:,:,,,,,,,,,@                               \n");
  printw("                             .@:,::,:,,,,,,,,,,@                               \n");
  printw("                              @,,:,:,,,,,,,,,,,@                               \n");
  printw("                              @,,::,,,,,,,,,,,+@                               \n");
  printw("                              ##,,,,,,,,,,,,,,@`                               \n");
  printw("                               @,,,,,,,,,,,,:'@                                \n");
  printw("                               +@,,,,,,,,,,,,@`                                \n");
  printw("                                @@:,,,,,,,,,@'                                 \n");
  printw("                                 @@,,,:,:,;@'                                  \n");
  printw("                                  ;@@,,,'@@`                                   \n");
  printw("                                    #@,,@,`                                    \n");
  printw("                                     @@@'                                      \n");
  refresh();                        //Write buffer to screen
  getch();                          //Wait for user input
  endwin();                         //End curses mode
}
