//util.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "util.h"

#include <unistd.h>

//splash()
//Prints out splash screen to be used on startup
void splash(WINDOW* mainwin){
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
	refresh();
	sleep(2);
	wclear(mainwin);
	refresh();
}