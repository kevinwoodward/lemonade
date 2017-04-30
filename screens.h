//screens.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>

//Print out welcome window
WINDOW* cWelcwin(WINDOW* mainwin);

//Print out select song window
WINDOW* cSelectwin(WINDOW* mainwin);

//Print out File browser window
WINDOW* cBrowsewin(WINDOW* mainwin);

//Print out about window
WINDOW* cAboutwin(WINDOW* mainwin);

void remWin(WINDOW* childwin);




#endif