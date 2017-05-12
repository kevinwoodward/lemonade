//winInfo.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "winInfo.h"

#include <stdlib.h>


//Struct Definition: -----------------------------------------------------


typedef struct WinfoObj{
	WINDOW* mainWin;
	WINDOW* activeWin;
	MENU* activeMenu;
	ITEM** activeItems;
	int numItems;
}WinfoObj;


//Con/Destructor: -----------------------------------------------------------


//newWinfo()
//Constructor for Winfo object
Winfo newWinfo(WINDOW* mainWin){
	Winfo nWinfo = malloc(sizeof(WinfoObj));
	nWinfo->mainWin = mainWin;
	nWinfo->activeWin = NULL;
	nWinfo->activeMenu = NULL;
	nWinfo->activeItems = NULL;
	nWinfo->numItems = 0;
	return nWinfo;
}

//freeWinfo()
//Destructor for Winfo object
void freeWinfo(Winfo* pWinfo){
	free(*pWinfo);
	*pWinfo = NULL;
}


//Access functions: ------------------------------------------------------


//Getter for main WINDOW* field
WINDOW* getMainWin(Winfo aWinfo){
	return aWinfo->mainWin;
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
void setNumItems(Winfo aWinfo, int newNumItems){
	aWinfo->numItems = newNumItems;
}