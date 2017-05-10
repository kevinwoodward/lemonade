//frontend.c
//CMPS 115 Spring 2017
//Lemonade music player

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <menu.h>

#include "frontend.h"
#include "helpers.h"

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

//createWin()
//Creates childwindow with designated size
WINDOW* createWin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
    int rows  = ROWS, cols   = COLS;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
	return childwin;
}

//createMenu()
//Returns pointer to menu with given options
MENU* createMenu(WINDOW* win, int numChoices, char** choices){
	
	ITEM** items = (ITEM **)calloc(5, sizeof(ITEM *));
	
	for(int i = 0; i < numChoices; ++i){
		items[i] = new_item(choices[i], choices[i]);
	}
	items[4] = (ITEM *)NULL;
	
	//Init Menu
	MENU* menu = new_menu((ITEM **)items);
	set_menu_win(menu, win);
	set_menu_sub(menu, derwin(win, 4, 15, 5, 1));
	post_menu(menu);
	
	return menu;
}

//cWelcwin()
//Print out welcome window
void cWelcwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu){
	WINDOW* childwin = createWin(mainwin);
	
    mvwaddstr(childwin, 1, 1, "Welcome to the Lemonade");
    mvwaddstr(childwin, 2, 7, "music player!");
    mvwaddstr(childwin, 3, 1, "Please select an action:");
	
	//Create selection menu
	char* choices[] = {"Select a song","Browse files","About","Quit"};
	MENU* menu = createMenu(childwin, 4, choices);
	
	wrefresh(childwin);
	
	*pchildwin = childwin;
	*pmenu = menu;
}

//cSelectwin()
//Print out select song window
void cSelectwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu){
	WINDOW* childwin = createWin(mainwin);
	
	int lsCount = 1;
	FILE *ls = popen("ls *.mp3", "r");
	char buf[512];
	attron(A_BOLD);
	while (fgets(buf, sizeof(buf), ls) != 0) {
		trimwhitespace(buf);
		mvwaddstr(childwin, lsCount, 1, buf);
		lsCount++;
	}
	attroff(A_BOLD);
	ls = popen("ls *.mp3", "r");
	//char buf[512];
	while (fgets(buf, sizeof(buf), ls) != 0) {
		trimwhitespace(buf);
		mvwaddstr(childwin, lsCount, 1, buf);
		lsCount++;
	}
	pclose(ls);
	wrefresh(childwin);
	
	*pchildwin = childwin;
	*pmenu = NULL;
}

//cBrowsewin()
//Print out File browser window
void cBrowsewin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu){
	WINDOW* childwin = createWin(mainwin);
	
    mvwaddstr(childwin, 1, 1, "This is where the user");
    mvwaddstr(childwin, 2, 1, "will browse songs");
	wrefresh(childwin);
	
	*pchildwin = childwin;
	*pmenu = NULL;}

//cAboutwin()
//Print out about window
void cAboutwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu){
	WINDOW* childwin = createWin(mainwin);
	
	mvwaddstr(childwin, 1, 1, "This is where the user");
	mvwaddstr(childwin, 2, 1, "will read about things");
	wrefresh(childwin);
	
	*pchildwin = childwin;
	*pmenu = NULL;
}

//remWin()
//Clears and removes active window.
void remWin(WINDOW** pchildwin){
	wclear(*pchildwin);
	delwin(*pchildwin);
	*pchildwin = NULL;
	return;
}

//remMenu()
//Frees memory associated with a menu
void remMenu(MENU** pactiveMenu){
	unpost_menu(*pactiveMenu);
	
	// for(i = 0; i < n_choices; ++i)
		// free_item(my_items[i]);
	free_menu(*pactiveMenu);
}

