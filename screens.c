//screens.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "screens.h"

WINDOW* cWelcwin(WINDOW* mainwin){
	WINDOW* childwin;
	int width = 26, height = 10;
    int rows  = 25, cols   = 80;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
	childwin = subwin(mainwin, height, width, y, x);
    box(childwin, 0, 0);
    mvwaddstr(childwin, 1, 1, "Welcome to the Lemonade");
    mvwaddstr(childwin, 2, 5, "music player!");
    mvwaddstr(childwin, 3, 1, "Please select an action:");
    mvwaddstr(childwin, 5, 1, "[1]: Select a song");
    mvwaddstr(childwin, 6, 1, "[2]: Browse Files");
    mvwaddstr(childwin, 7, 1, "[3]: About");
    mvwaddstr(childwin, 8, 1, "[q]: Quit");
	wrefresh(childwin);
	return childwin;
}



WINDOW* cSelwin(WINDOW* mainwin){
	return NULL;
}


WINDOW* cBrowwin(WINDOW* mainwin){
	return NULL;
}
