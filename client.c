#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

//#include "helpers.h"
#include "backend.h"
#include "frontend.h"
#include "winInfo.h"


int main(int argc, char **argv) {
  char* name = "hello";
  char* arr[] = {"apple", "banana", "clementine", "durian", ""};

  if(argc <= 1) {
    printf("No option specified! Currently:\n-s for start, followed by a filepath to an mp3\n-p for play/pause\n-k for kill\n-e to enter screen\n-l to do the test ls function\n");
  }

  //Backend: ---------------------------------------------------------

  int argCase;
  //char* filePath = NULL;

  //handles flag options
  while((argCase = getopt(argc, argv, "ps:kelx")) != -1) {
    switch (argCase) {
      case 'p':
        playpause();
        return 0;
        break;
      case 's':
        //filePath = optarg;

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
      case 'x':
        createPlaylistFile(name, arr);
        break;
      case '?':
        if (optopt == 's') {
          fprintf (stdout, "Option -%c requires an argument.\n", optopt);
          startSingleSong("em.mp3");
          //return 1;
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
  // if(filePath != NULL) {
  //   system("killall screen");
  //   createScreen();
  //   sendScreenCommand("cd ~/Documents/github/lemonade");
  //   char fileStr[100];
  //   strcpy(fileStr, "mpg123 -C ");
  //   strcat(fileStr, filePath);
  //   sendScreenCommand(fileStr);
  // }


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

	//Init activeInfo for tracking window/menu/items
	Winfo activeInfo = newWinfo(mainWin);

	//Print out welcome window:
	cWelcwin(activeInfo);

	int ch;
	int itemNum;

	//Primary program input loop
	while( (ch = getch()) != 'q'){
		MENU* activeMenu = getMenu(activeInfo);
		switch(ch){
			case '1':
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cWelcwin(activeInfo);
				break;

			case '2':
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cSelectwin(activeInfo);
				break;

			case '3':
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cBrowsewin(activeInfo);
				break;

			case '4':
				if(activeMenu != NULL) remMenu(activeInfo);
				remWin(activeInfo);
				cAboutwin(activeInfo);
				break;

			case KEY_UP : //UP arrow key
				menu_driver(getMenu(activeInfo), REQ_UP_ITEM);
				break;

			case KEY_DOWN : //DOWN arrow key
				menu_driver(getMenu(activeInfo), REQ_DOWN_ITEM);
				break;

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
					if(activeMenu != NULL) remMenu(activeInfo);
					remWin(activeInfo);
					break;
				}//End of ENTER switch
				break;

		}//End of switch

		wrefresh(getWin(activeInfo));

	}//End of input while


	//End of excecution
	if(getMenu(activeInfo) != NULL) remWin(activeInfo);
	remMenu(activeInfo);
	freeWinfo(&activeInfo);
    delwin(mainWin);
    endwin();
    //refresh();

	return 0;
}
