#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//#include "helpers.h"
#include "tests/AllTests.h"
#include "backend.h"
#include "frontend.h"
#include "winInfo.h"
#include "inputHandler.h"

int main(int argc, char **argv) {

	//if there are some flags used
	if(argc > 1) {
		if(strcmp(argv[1], "--tests") == 0) {
			//if --tests, run tests
			RunAllTests();
		} else if(strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
			//if --help or -h, open help page
			system("sensible-browser https://docs.google.com/document/d/1pPvelGZFUB94YW7hT2COPODH8C3Av2oZ9XNly7zuCIk/edit"); //open help doc
		} else {
			//else, print flag usage
			printf("\nThe supported flags are:\nRun tests: --tests\nOpen help webpage: --help, -h\n\n");
		}
		//quit
		return 0;
	}

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
