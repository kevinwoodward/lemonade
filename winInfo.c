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