//frontend.c
//CMPS 115 Spring 2017
//Lemonade music player

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "frontend.h"

#include "backend.h"
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

//cInsnwin()
//Prints out window navigation instruction
WINDOW* cInsnwin(WINDOW* mainWin){
	WINDOW* childWin = subwin(mainWin, 5, 60, 0, 0);
	//box(childWin, 0, 0);

	mvwaddstr(childWin, 0, 1, "Use the number keys to navigate to the different menus");
	mvwaddstr(childWin, 1, 1, "[1]: Main Menu     [3]: File Browser");
	mvwaddstr(childWin, 2, 1, "[2]: Song Selector [4]: About");

	wrefresh(childWin);

	return childWin;
}


//Private helper functions: -----------------------------------------------


//createWin()
//Creates childWindow with designated size
void createWin(Winfo activeInfo){
	WINDOW* childWin;
	int width = WIDTH, height = HEIGHT;
    int rows  = ROWS, cols   = COLS;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childWin = subwin(getMainWin(activeInfo), height, width, y, x);
    box(childWin, 0, 0);

	setWin(activeInfo, childWin);
}

//createItems()
//Returns items from string array
void createItems(Winfo activeInfo, int numItems, char** choices){
	ITEM** items = (ITEM **)calloc(numItems+1, sizeof(ITEM *));

	for(int i = 0; i < numItems; ++i){
		items[i] = new_item(choices[i], choices[i]);
	}
	items[numItems] = (ITEM *)NULL;

	setNumItems(activeInfo, numItems);
	setItems(activeInfo, items);
}

//createMenu()
//Creates a new menu with given items
void createMenu(Winfo activeInfo){

						//(ITEM **)
	MENU* menu = new_menu(getItems(activeInfo));
	WINDOW* win = getWin(activeInfo);
	set_menu_win(menu, win);
	set_menu_sub(menu, derwin(win, 4, 15, 4, 1));
	post_menu(menu);

	setMenu(activeInfo, menu);
}


//Window creation: --------------------------------------------------------


//cWelcwin()
//Print out welcome window
void cWelcwin(Winfo activeInfo){
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

    mvwaddstr(childWin, 1, 1, "Welcome to the Lemonade music player!");
    mvwaddstr(childWin, 2, 1, "Please select an action:");

	//Create selection menu
	char* choices[] = {"Select a song","Browse files","About","Quit"};
	createItems(activeInfo, 4, choices);
	createMenu(activeInfo);

	wrefresh(childWin);
}

//cSelectwin()
//Print out select song window
void cSelectwin(Winfo activeInfo){
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

	int numItems = countLines();
	char** choices = calloc(numItems, sizeof(char*));
	for(int i=0; i<numItems; i++){
		choices[i] = calloc(30, sizeof(char));
	}
	lsOutput(choices);
	createItems(activeInfo, numItems, choices);
	createMenu(activeInfo);
	wrefresh(childWin);
}

//cBrowsewin()
//Print out File browser window
void cBrowsewin(Winfo activeInfo){
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

    mvwaddstr(childWin, 1, 1, "This is where the user");
    mvwaddstr(childWin, 2, 1, "will browse songs");

	wrefresh(childWin);
}

//cAboutwin()
//Print out about window
void cAboutwin(Winfo activeInfo){
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

	mvwaddstr(childWin, 1, 1, "Lemonade Music player");
	mvwaddstr(childWin, 2, 1, "CMPS 115 Spring 2017");
	mvwaddstr(childWin, 4, 1, "Kevin Woodward");
	mvwaddstr(childWin, 5, 1, "Ryan Schouweiler");
	mvwaddstr(childWin, 6, 1, "Amit Khatri");
	mvwaddstr(childWin, 7, 1, "Akhshaya Baskar");
	mvwaddstr(childWin, 8, 1, "Tarik Zeid");

	wrefresh(childWin);
}


//Memory cleaning functions: ----------------------------------------------


//remWin()
//Clears and removes active window.
void remWin(Winfo activeInfo){
	WINDOW* window = getWin(activeInfo);
	wclear(window);
	delwin(window);
	setWin(activeInfo, NULL);
}

//remMenu()
//Frees memory associated with a menu
void remMenu(Winfo activeInfo){
	MENU* menu = getMenu(activeInfo);
	//unpost_menu(menu);

	//Free menu items
	ITEM** items = getItems(activeInfo);
	int numItems = getNumItems(activeInfo);
	for(int i = 0; i < numItems; ++i){
		free_item(items[i]);
	}
	free(items);

	free_menu(menu);

	setItems(activeInfo, NULL);
	setMenu(activeInfo, NULL);
	setNumItems(activeInfo, 0);
}

//clearAndClean()
//Removes active windows and menus, cleans memory before exiting
void clearAndClean(Winfo activeInfo){
	WINDOW* mainWin = getMainWin(activeInfo);
	WINDOW* insnWin = getInsnWin(activeInfo);

	if(getMenu(activeInfo) != NULL){
		remWin(activeInfo);
	}
	remMenu(activeInfo);
	wclear(mainWin);
    delwin(mainWin);
	wclear(insnWin);
	delwin(insnWin);
    endwin();

	freeWinfo(&activeInfo);

	exit(0);
}
