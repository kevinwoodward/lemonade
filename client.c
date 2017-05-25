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
  char* name = "hello";
  char* arr[] = {"apple", "banana", "clementine", "durian", ""};

  if(argc <= 1) {
    printf("No option specified! Currently:\n-s for start, followed by a filepath to an mp3\n-p for play/pause\n-k for kill\n-e to enter screen\n-l to do the test ls function\n");
  }

  //Backend: ---------------------------------------------------------

  int argCase;
  createScreen(1);
  //handles flag options (for backend testing)
  while((argCase = getopt(argc, argv, "ps:kelxd")) != -1) {
    switch (argCase) {
      case 'p':
        playPause();
        return 0;
        break;
      case 's':
        //filePath = optarg;
        startSingleSong(optarg);
        break;
      case 'k':
        system("killall screen");
        return 0;
        break;
      case 'e':
        system("screen -r");
        break;
      case 'l':
        startPlaylist("testpl");
        break;
      case 'x':
        createPlaylistFile(name, arr);
        break;
      case 'd':
        createPlaylistFromDir("/home/kevin/Music/Kendrick Lamar - DAMN", "testpl");
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
	freeWinfo(&activeInfo);
	
	//	clearAndClean exits program, but 
	//	this is here to make the compiler happy.
	return 0;

}
