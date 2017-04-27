//screens.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef SCREENS_H
#define SCREENS_H

#include <ncurses.h>

WINDOW* cWelcwin(WINDOW* mainwin);

WINDOW* cSelectwin(WINDOW* mainwin);

WINDOW* cBrowsewin(WINDOW* mainwin);

WINDOW* cAboutwin(WINDOW* mainwin);

void remWin(WINDOW* childwin);




#endif