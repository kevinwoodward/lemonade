//winInfo.h
//CMPS 115 Spring 2017
//Lemonade music player

//	This is a simple organizer class used to simplify
//	the way window creation and destruction is handled.
//	Holds pointers to a WINDOW, MENU, and 2d array of ITEMS
//	as well as a number of items in the menu.


#ifndef WININFO_H
#define WININFO_H

typedef struct WinfoObj* Winfo;


//newWinfo()
//Constructor for Winfo object
Winfo newWinfo();


#endif