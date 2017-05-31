#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//#include "helpers.h"
#include "backend.h"
#include "frontend.h"
#include "winInfo.h"
#include "inputHandler.h"

int main(int argc, char **argv) {

	//Frontend: --------------------------------------------------
	//Init main window
	WINDOW * mainWin;
	if((mainWin = initscr()) == NULL){
		fprintf(stderr, "ERROR: Failed to init main window.\n");
	}

	noecho();              //Disable echoing to screen
	keypad(stdscr, TRUE);  //Simplifies input handling

	//Print out splash screen on startup
	splash(mainWin);

  //Sets cursor to off
  curs_set(0);

	//Print out welcome and intruction windows:
	WINDOW* insnWin = cInsnwin(mainWin);

	//Init activeInfo for tracking window/menu/items
	Winfo activeInfo = newWinfo(mainWin, insnWin);

	//Print Welcome window
	cWelcwin(activeInfo);

	int ch;

	//Primary program input loop
	while( (ch = getch()) != 'q'){

		//Determine actions based on current screen
		handleInput(activeInfo, ch);

		wrefresh(getWin(activeInfo));

	}//End of input while


	//End of excecution cleanup
	clearAndClean(activeInfo);

	//	"clearAndClean()" exits program, but
	//	this is here to make the compiler happy.
	return 0;

}
