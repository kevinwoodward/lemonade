//screens.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "screens.h"

#define WIDTH 26
#define HEIGHT 10
#define ROWS 25
#define COLS 80


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
    mvwaddstr(childwin, 5, 1, "[1]: Select a song");
    mvwaddstr(childwin, 6, 1, "[2]: Browse Files");
    mvwaddstr(childwin, 7, 1, "[3]: About");
    mvwaddstr(childwin, 8, 1, "[q]: Quit");
	wrefresh(childwin);
	return childwin;
}



WINDOW* cSelectwin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = WIDTH, height = HEIGHT;
    int rows  = ROWS, cols   = COLS;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 1, "This is where the user");
    mvwaddstr(childwin, 2, 1, "will select songs");
	wrefresh(childwin);
	return childwin;
}


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



void remWin(WINDOW* childwin){
	wclear(childwin);
	delwin(childwin);
	return;
}

