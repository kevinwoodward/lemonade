//winInfo.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "winInfo.h"

#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>

typedef struct WinfoObj{
	WINDOW* activeWin;
	MENU* activeMenu;
	ITEM** activeItems;
	int numItems;
}WinfoObj;

//newWinfo()
//Constructor for Winfo object
Winfo newWinfo(){
	Winfo nWinfo = malloc(sizeof(WinfoObj));
	nWinfo->activeWin = NULL;
	nWinfo->activeMenu = NULL;
	nWinfo->activeItems = NULL;
	nWinfo->numItems = 0;
	return nWinfo;
}

//Get/Setters for WINDOW* field
WINDOW* getWin(Winfo aWinfo){
	return aWinfo->activeWin;
}
void setWin(Winfo aWinfo, WINDOW* newWin){
	aWinfo->activeWin = newWin;
}

//Get/Setters for MENU* field
MENU* getMenu(Winfo aWinfo){
	return aWinfo->activeMenu;
}
void setMenu(Winfo aWinfo, MENU* newMenu){
	aWinfo->activeMenu = newMenu;
}

//Get/Setters for ITEM** field
ITEM** getItems(Winfo aWinfo){
	return aWinfo->activeItems;
}
void setItems(Winfo aWinfo, ITEM** newItems){
	aWinfo->activeItems = newItems;
}

//Get/Setters for numItems field
int getNumItems(Winfo aWinfo){
	return aWinfo->numItems;
}
void setNumItems(Winfo aWinfo, int numItems){
	aWinfo->numItems = this->numItems;
}