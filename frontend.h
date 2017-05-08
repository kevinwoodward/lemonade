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
void cSelectwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu);

//Print out File browser window
void cBrowsewin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu);

//Print out about window
void cAboutwin(WINDOW* mainwin, WINDOW** pchildwin, MENU** pmenu);

//Frees memory associated with a window
void remWin(WINDOW** pchildwin);

//Frees memory associated with a menu
void remMenu(MENU** activeMenu);


#endif