//frontend.c
//CMPS 115 Spring 2017
//Lemonade music player

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <menu.h>

#include "frontend.h"
#include "helpers.c"

#define WIDTH 70
#define HEIGHT 10
#define ROWS 25
#define COLS 80

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
	sleep(1.5);
	wclear(mainwin);
	refresh();
}

//cWelcwin()
//Print out welcome window
WINDOW* cWelcwin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
    int rows  = ROWS, cols   = COLS;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 1, "Welcome to the Lemonade");
    mvwaddstr(childwin, 2, 7, "music player!");
    mvwaddstr(childwin, 3, 1, "Please select an action:");
	
	//Init choices
	char* choices[] = {"Select a song","Browse files","About","Quit"};
	ITEM** items = (ITEM **)calloc(5, sizeof(ITEM *));
	for(int i = 0; i < 5; ++i)
	        items[i] = new_item(choices[i], choices[i]);
	items[4] = (ITEM *)NULL;
	
	//Init Menu
	MENU* menu = new_menu((ITEM **)items);
	set_menu_win(menu, childwin);
	set_menu_sub(menu, derwin(childwin, 4, 15, 5, 1));
	post_menu(menu);
	
	wrefresh(childwin);
	return childwin;
}

//cSelectwin()
//Print out select song window
WINDOW* cSelectwin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
  int rows  = ROWS, cols   = COLS;
  int x = (cols - width)  / 2;
  int y = (rows - height) / 2;
	int lsCount = 1;
	childwin = subwin(mainwin, height, width, y, x);
  box(childwin, 0, 0);
	FILE *ls = popen("ls *.mp3", "r");
	char buf[512];
	while (fgets(buf, sizeof(buf), ls) != 0) {
		trimwhitespace(buf);
		mvwaddstr(childwin, lsCount, 1, buf);
		lsCount++;
	}
	pclose(ls);
	wrefresh(childwin);
	return childwin;
}

//cBrowsewin()
//Print out File browser window
WINDOW* cBrowsewin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
    int rows  = ROWS, cols   = COLS;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 1, "This is where the user");
    mvwaddstr(childwin, 2, 1, "will browse songs");
	wrefresh(childwin);
	return childwin;
}

//cAboutwin()
//Print out about window
WINDOW* cAboutwin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
  int rows  = ROWS, cols   = COLS;
  int x = (cols - width)  / 2;
  int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
  box(childwin, 0, 0);
  mvwaddstr(childwin, 1, 1, "This is where the user");
  mvwaddstr(childwin, 2, 1, "will read about things");
	wrefresh(childwin);
	return childwin;
}

//remWin()
//Clears and removes active window.
void remWin(WINDOW* childwin){
	wclear(childwin);
	delwin(childwin);
	return;
}
