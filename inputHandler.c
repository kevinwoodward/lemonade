//inputHandler.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "inputHandler.h"

#include <menu.h>

#include "frontend.h"


//Screen-specific input handling: -------------------------------------------


//handleWelcWin()
//Handles input specific to "welcome" window
void handleWelcWin(Winfo activeInfo, int ch){
	int itemNum;
	MENU* activeMenu = getMenu(activeInfo);
	switch(ch){
		case '\n': //ENTER key
			itemNum = item_index(current_item(activeMenu));
			switch (itemNum){
				case 0: //Select
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cSelectwin(activeInfo);
				break;
			case 1: //Browse
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cBrowsewin(activeInfo);
				break;
			case 2: //About
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cAboutwin(activeInfo);
				break;
			case 3: //Quit
				clearAndClean(activeInfo);
				break;
			}//End of ENTER switch
			break;
	}//End of switch
}

//handleBrowseWin()
//Handles input specific to "browser" window
void handleBrowseWin(Winfo activeInfo, int ch){
	
}

//handleAboutWin()
//Handles input specific to "about" window
void handleAboutWin(Winfo activeInfo, int ch){
	
}


//Input routing: ------------------------------------------------------------


//handleInput()
//Takes state information, and routes input to correct handlers
void handleInput(Winfo activeInfo, int ch){
	
	//Handle screen switching
	MENU* activeMenu = getMenu(activeInfo);
	switch(ch){
		case '1':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cWelcwin(activeInfo);
			return;

		case '2':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cSelectwin(activeInfo);
			return;

		case '3':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cBrowsewin(activeInfo);
			return;

		case '4':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cAboutwin(activeInfo);
			return;
			
		case KEY_UP : //UP arrow key
			menu_driver(getMenu(activeInfo), REQ_UP_ITEM);
			break;
		
		case KEY_DOWN : //DOWN arrow key
			menu_driver(getMenu(activeInfo), REQ_DOWN_ITEM);
			break;
			
	}//End of switch
		
	
	//If not switching screens, handle input based on active window
	int state = getState(activeInfo);
	switch(state){
		case 0:
			handleWelcWin(activeInfo, ch);
			break;
		case 1:
			handleBrowseWin(activeInfo, ch);
			break;
		case 2:
			handleAboutWin(activeInfo, ch);
			break;
	}
}
