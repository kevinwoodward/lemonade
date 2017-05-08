#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//#include "helpers.h"
#include "backend.h"
#include "frontend.h"


int main(int argc, char **argv) {

  if(argc <= 1) {
    printf("No option specified! Currently:\n-s for start, followed by a filepath to an mp3\n-p for play/pause\n-k for kill\n-e to enter screen\n-l to do the test ls function\n");
  }

  //Backend: ---------------------------------------------------------

  int argCase;
  char* filePath = NULL;

  //handles flag options
  while((argCase = getopt(argc, argv, "ps:kel")) != -1) {
    switch (argCase) {
      case 'p':
        playpause();
        return 0;
        break;
      case 's':
        filePath = optarg;
        break;
      case 'k':
        system("killall screen");
        return 0;
        break;
      case 'e':
        system("screen -r");
        break;
      case 'l':
        //testList();
        break;
      case '?':
        if (optopt == 's') {
          fprintf (stdout, "Option -%c requires an argument.\n", optopt);
          return 1;
        }
        else if (isprint (optopt)) {
          fprintf (stdout, "Unknown option `-%c'.\n", optopt);
          return 1;
        }
        else {
          fprintf (stdout,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
                   return 1;
        }
    }
  }

  //starts process if command is -s with specified song
  if(filePath != NULL) {
    system("killall screen");
    createScreen();
    sendScreenCommand("cd ~/Documents/github/lemonade");
    char fileStr[100];
    strcpy(fileStr, "mpg123 -C ");
    strcat(fileStr, filePath);
    sendScreenCommand(fileStr);
  }


	//Frontend: --------------------------------------------------


	//mainwin is background window, activewin is
	//	window currently being viewed by the user
	WINDOW * mainwin, * activewin;
	int ch;

	//Init main window
	if((mainwin = initscr()) == NULL){
		fprintf(stderr, "ERROR: Failed to init main window.\n");
	}

	//Disable echoing of typed chars to screen
	noecho();

	//Print out splash screen on startup
	splash(mainwin);

	//Print out welcome window:
	activewin = cWelcwin(mainwin);

	//Primary program input loop
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
			/* case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break; */
		}//End of switch

	}//End of input while


	//End of excecution
	remWin(activewin);
    delwin(mainwin);
    endwin();
    //refresh();

  return 0;
}
