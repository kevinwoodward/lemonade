//frontend.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>
#include <menu.h>

#include "winInfo.h"

//Print out Screens: -----------------------------------------------------

//Prints out splash screen to be used on startup
void splash(WINDOW* mainwin);

//Prints out window navigation instruction
WINDOW* cInsnwin(WINDOW* mainwin);

//Print out welcome window
void cWelcwin(Winfo activeInfo);

//Print out select song window
void cSelectwin(Winfo activeInfo);

//Print out File browser window
void cBrowsewin(Winfo activeInfo);

//Print out about window
void cAboutwin(Winfo activeInfo);

//Remove and clean windows/menus: ----------------------------------------

//Frees memory associated with a window
void remWin(Winfo activeInfo);

//Frees memory associated with a menu
void remMenu(Winfo activeInfo);

//Removes active windows and menus, cleans memory before exiting
void clearAndClean(Winfo activeInfo);



#endif