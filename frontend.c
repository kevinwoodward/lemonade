//frontend.c
//UCSC cmps 115 Spring 2017

#include <ncurses.h>
#include "util.h"
#include "screens.h"

int main(int argc, char* argv[]){	
	
	//mainwin is background window, activewin is 
	//	window currently being viewed by the user
	WINDOW * mainwin, * activewin;	
	int ch;
	
	//Init main window
	if((mainwin = initscr()) == NULL){
		fprintf(stderr, "ERROR: Failed to init main window.\n");
	}
	
	noecho();
	
	//Print out splash screen on startup
	splash(mainwin);
	
	//Print out welcome window:
	activewin = cWelcwin(mainwin);
	
	//Primary program loop
	while( (ch = getch()) != 'q'){
		
		switch(ch){
			case '1':
				remWin(activewin);
				activewin = cSelectwin(mainwin);
				break;
			
			case '2':
				remWin(activewin);
				activewin = cBrowsewin(mainwin);
				break;
				
			case '3':
				remWin(activewin);
				activewin = cAboutwin(mainwin);
				break;
			
			case '\e':
				remWin(activewin);
				activewin = cWelcwin(mainwin);
				break;
		}//End of switch
		
	}//End of input while
	
	
	//End of excecution
	remWin(activewin);
    delwin(mainwin);
    endwin();
    //refresh();
	return 0;
}

