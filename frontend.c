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
#define HEIGHT 18
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
	mvwaddstr(childWin, 1, 1, "[1]: Main Menu     [3]: Playlist Browser");
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
  int rows = ROWS, cols = COLS;
  int x = (cols - width)  / 2;
  int y = ((rows - height) / 2) + 2;
	childWin = subwin(getMainWin(activeInfo), height, width, y, x);
  box(childWin, 0, 0);

	setWin(activeInfo, childWin);
}

//createItems()
//Returns items from string array
void createItems(Winfo activeInfo, int numItems, char** choices){
	ITEM** items = calloc(numItems+1, sizeof(ITEM *));

	for(int i = 0; i < numItems; ++i){
		items[i] = new_item(choices[i], "");
	}
	items[numItems] = (ITEM *)NULL;

	setNumItems(activeInfo, numItems);
	setItems(activeInfo, items);
}

//createMenu()
//Creates a new menu with given items
void createMenu(Winfo activeInfo, int numLines, int lineLen, int beginY, int beginX){

	MENU* menu = new_menu(getItems(activeInfo));
	WINDOW* win = getWin(activeInfo);
	set_menu_win(menu, win);
	//set_menu_sub(menu, derwin(win, 4, lineLen, 4, 1)); //TODO: change these to be passed in
	set_menu_sub(menu, derwin(win, numLines, lineLen, beginY, beginX)); //TODO: change these to be passed in

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
	char* choices[] = {"Browse files","Browse Playlists","About","Quit"};
	createItems(activeInfo, 4, choices);
	createMenu(activeInfo, 4, 20, 4, 1);

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
	createMenu(activeInfo, numItems, 65, 1, 1);
	wrefresh(childWin);
}

//cBrowsewin()
//Print out File browser window
void cPlaylistwin(Winfo activeInfo){
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

	chdir("/usr/share/lemonade");
	int numItems = countAll();
	char** choices = calloc(numItems, sizeof(char*));
	for(int i=0; i<numItems; i++){
		choices[i] = calloc(30, sizeof(char));
	}
	lsAll(choices);

	createItems(activeInfo, numItems, choices);
	createMenu(activeInfo, numItems, 65, 1, 1);
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
	mvwaddstr(childWin, 10, 1, "Press 'h' for help.");

	wrefresh(childWin);
}

void cTagEditwin(Winfo activeInfo, const char* selected) {
	createWin(activeInfo);
	WINDOW* childWin = getWin(activeInfo);

	mvwaddstr(childWin, 1, 1, "Editing: ");
	mvwaddstr(childWin, 1, 10, selected);
	mvwaddstr(childWin, 3, 1, "- (A)rtist");
	mvwaddstr(childWin, 4, 1, "- A(l)bum");
	mvwaddstr(childWin, 5, 1, "- (S)ong");
	mvwaddstr(childWin, 6, 1, "- (G)enre");
	mvwaddstr(childWin, 7, 1, "- (Y)ear");
	mvwaddstr(childWin, 8, 1, "- (T)rack number");
	mvwaddstr(childWin, 10, 1, "- Escape to exit");

	wrefresh(childWin);

}

//Memory cleaning functions: ----------------------------------------------


//remWin()
//Clears and removes active window. (and associated menu if one exists)
void remWin(Winfo activeInfo){

	//Remove menu if one exists
	if(getMenu(activeInfo) != NULL){
		remMenu(activeInfo);
	}

	WINDOW* window = getWin(activeInfo);
	wclear(window);
	delwin(window);
	setWin(activeInfo, NULL);
}

//remMenu()
//Frees memory associated with a menu
void remMenu(Winfo activeInfo){

	MENU* menu = getMenu(activeInfo);
	unpost_menu(menu);

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
