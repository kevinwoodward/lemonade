//winInfo.h
//CMPS 115 Spring 2017
//Lemonade music player

//	This is a simple organizer class used to simplify
//	the way window creation and destruction is handled.


//	Fields:
//
//	Main window: background ncurses window
//	Active window: subwindow currently being viewed
//	Menu: currently  active ncurses menu
//	Item: two dimensional array composed of ncurses Menu items
//	numItems: number of items in menu
//  state: state variable that determines correct inputs to check for

#ifndef WININFO_H
#define WININFO_H

#include <ncurses.h>
#include <menu.h>


typedef struct WinfoObj* Winfo;


//newWinfo()
//Constructor for Winfo object
Winfo newWinfo();

//freeWinfo()
//Destructor for Winfo object
void freeWinfo(Winfo* pWinfo);

//Get/Setters for main WINDOW* field
WINDOW* getMainWin(Winfo aWinfo);
void setMainWin(Winfo aWinfo, WINDOW* newWin);

//Getter for instruction window field
WINDOW* getInsnWin(Winfo aWinfo);

//Get/Setters for state field
int getState(Winfo aWinfo);
void setState(Winfo aWinfo, int newState);
	
//Get/Setters for WINDOW* field
WINDOW* getWin(Winfo aWinfo);
void setWin(Winfo aWinfo, WINDOW* newWin);

//Get/Setters for MENU* field
MENU* getMenu(Winfo aWinfo);
void setMenu(Winfo aWinfo, MENU* newMenu);

//Get/Setters for ITEM** field
ITEM** getItems(Winfo aWinfo);
void setItems(Winfo aWinfo, ITEM** newItems);

//Get/Setters for numItems field
int getNumItems(Winfo aWinfo);
void setNumItems(Winfo aWinfo, int newNumItems);


#endif