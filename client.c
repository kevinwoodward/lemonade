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


	//mainWin is background window, activeWin is
	//	window currently being viewed by the user
	WINDOW * mainWin;
	int ch;

	//Init main window
	if((mainWin = initscr()) == NULL){
		fprintf(stderr, "ERROR: Failed to init main window.\n");
	}

	noecho();              //Disable echoing to screen
	keypad(stdscr, TRUE);  //Enable keypad (simplifies input)

	//Print out splash screen on startup
	splash(mainWin);
	
	//Create pointers for active window and menus
	WINDOW * activeWin;
	MENU * activeMenu;

	//Print out welcome window:
	cWelcwin(mainWin, &activeWin, &activeMenu);

	int itemNum;
	
	//Primary program input loop
	while( (ch = getch()) != 'q'){

		switch(ch){
			case '1':
				if(activeMenu != NULL) remMenu(&activeMenu);
				remWin(&activeWin);
				cWelcwin(mainWin, &activeWin, &activeMenu);
				break;

			case '2':
				if(activeMenu != NULL) remMenu(&activeMenu);
				remWin(&activeWin);
				cSelectwin(mainWin, &activeWin, &activeMenu);
				break;

			case '3':
				if(activeMenu != NULL) remMenu(&activeMenu);
				remWin(&activeWin);
				cBrowsewin(mainWin, &activeWin, &activeMenu);
				break;
				
			case '4':
				if(activeMenu != NULL) remMenu(&activeMenu);
				remWin(&activeWin);
				cAboutwin(mainWin, &activeWin, &activeMenu);
				break;

			case KEY_UP : //UP arrow key
				menu_driver(activeMenu, REQ_UP_ITEM);
				break;
			
			case KEY_DOWN : //DOWN arrow key
				menu_driver(activeMenu, REQ_DOWN_ITEM);
				break;
			
			case '\n': //ENTER key
				itemNum = item_index(current_item(activeMenu));
				fprintf(stderr, "%d\n", itemNum);
				switch (itemNum){
					case 0: //Select
					if(activeMenu != NULL) remMenu(&activeMenu);
					remWin(&activeWin);
					cSelectwin(mainWin, &activeWin, &activeMenu);
					break;
				case 1: //Browse
					if(activeMenu != NULL) remMenu(&activeMenu);
					remWin(&activeWin);
					cBrowsewin(mainWin, &activeWin, &activeMenu);
					break;
				case 2: //About
					if(activeMenu != NULL) remMenu(&activeMenu);
					remWin(&activeWin);
					cAboutwin(mainWin, &activeWin, &activeMenu);
					break;
				case 3: //Quit
					if(activeMenu != NULL) remMenu(&activeMenu);
					remWin(&activeWin);
					break;
				}//End of ENTER switch
				break;
 
		}//End of switch
		
		wrefresh(activeWin);
		
	}//End of input while


	//End of excecution
	if(activeMenu != NULL) remWin(&activeWin);
	remMenu(&activeMenu);
    delwin(mainWin);
    endwin();
    //refresh();

	exit(0);
}
