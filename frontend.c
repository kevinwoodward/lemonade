//frontend.c
//UCSC cmps 115 Spring 2017

#include <ncurses.h>
#include "util.h"
#include "screens.h"

int main(int argc, char* argv[]){	
	
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
				break;
			
			case '2':
				remWin(activewin);
				break;
				
			case '3':
				remWin(activewin);
				break;
				
		}
		
		//Refresh screen
		wrefresh(mainwin);
		
	}
	
	
	//End of excecution
	
    delwin(mainwin);
    endwin();
    refresh();
	return 0;
}

