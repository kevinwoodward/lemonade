//frontend.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <menu.h>

//Prints out splash screen to be used on startup
void splash(WINDOW* mainwin);

//Print out welcome window
void cWelcwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu);

//Print out select song window
WINDOW* cSelectwin(WINDOW* mainwin);

//Print out File browser window
WINDOW* cBrowsewin(WINDOW* mainwin);

//Print out about window
WINDOW* cAboutwin(WINDOW* mainwin);

//Frees memory associated with a window
void remWin(WINDOW** pchildwin);

//Frees memory associated with a menu
void remMenu(MENU** activeMenu);


#endif