//inputHandler.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "inputHandler.h"

#include <menu.h>

#include "frontend.h"


//Screen-specific input handling: -------------------------------------------


//handleWelcWin()
//Handles input specific to "welcome" window
void handleWelcWin(Winfo activeInfo){
	
}

//handleBrowseWin()
//Handles input specific to "browser" window
void handleBrowseWin(Winfo activeInfo){
	
}

//handleAboutWin()
//Handles input specific to "about" window
void handleAboutWin(Winfo activeInfo){
	
}


//Input routing: ------------------------------------------------------------


//handleInput()
//Takes state information, and routes input to correct handlers
void handleInput(Winfo activeInfo, char ch){
	
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
	}//End of switch
		
	
	//If not switching screens, handle input based on active window
	int state = getState(activeInfo);
	switch(state){
		case 0:
			handleWelcWin(activeInfo);
			break;
		case 1:
			handleBrowseWin(activeInfo);
			break;
		case 2:
			handleAboutWin(activeInfo);
			break;
	}
}
