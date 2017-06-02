//inputHandler.c
//CMPS 115 Spring 2017
//Lemonade music player

#include "inputHandler.h"

#include <menu.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "frontend.h"
#include "backend.h"
#include "helpers.h"




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
				toDirectory("/home");
				remWin(activeInfo);
				cSelectwin(activeInfo);
				setState(activeInfo, 1);
				break;
			case 1: //Browse
				remWin(activeInfo);
				cPlaylistwin(activeInfo);
				setState(activeInfo, 2);
				break;
			case 2: //About
				remWin(activeInfo);
				cAboutwin(activeInfo);
				setState(activeInfo, 3);
				break;
			case 3: //Quit
				clearAndClean(activeInfo);
				break;
			}//End of ENTER switch
			break;
	}//End of switch
}

//handleSelectWin()
//Handles input specific to "select" window
void handleSelectWin(Winfo activeInfo, int ch){
	MENU* activeMenu = getMenu(activeInfo);
	char* path;

	//Get name of current selection
	const char* selectedItemName = item_name(current_item(activeMenu));

	//Switch on the entered character
	switch(ch){
		case '\n':
			if(str_end(selectedItemName, ".mp3")) {
				//If mp3, start playback
				path = getPath(selectedItemName, 1);
				startSingleSong(path);
				free(path);
				path = NULL;
		  } else if(str_end(selectedItemName, "/")) {
				//If folder, enter it
				downDirectory(selectedItemName);
				remWin(activeInfo);
				cSelectwin(activeInfo);
			}
			break;
		case '.':
			//Up a directory
			upDirectory();
			remMenu(activeInfo);
			cSelectwin(activeInfo);
			break;
		case 'p':
			//If selected on a directory, create and start playback of all mp3s in that directory (non-recursive)
			path = getPath(selectedItemName, 0);
			if(str_end(selectedItemName, "/") != 1) {
				break;
			}
			createPlaylistFromDir(path, selectedItemName);
			startPlaylist(selectedItemName);
			free(path);
				path = NULL;
			break;
		case 'h':
			//Go to /home directory
			toDirectory("/home");
			remMenu(activeInfo);
			cSelectwin(activeInfo);
			break;
		case 't':
			//If pressed on an mp3, invoke the tag editing menu
			if(str_end(selectedItemName, ".mp3") != 1) {
				break;
			}

			remWin(activeInfo);
			cTagEditwin(activeInfo, selectedItemName);
			editTags(selectedItemName);
			remWin(activeInfo);
			cSelectwin(activeInfo);
			break;
		case 'i':
			//Invoke embedded art display
			displayArt(selectedItemName);
			break;
	}
}

//handleBrowseWin()
//Handles input specific to "browser" window
void handlePlaylistWin(Winfo activeInfo, int ch){
	MENU* activeMenu = getMenu(activeInfo);
	const char* selectedItemName = item_name(current_item(activeMenu));
	char nonConstName[256];
	strcpy(nonConstName, selectedItemName);

	switch (ch) {
		case '\n':
			//Start playback of selected playlist
			startPlaylist(nonConstName);
			break;
	}
}

//handleAboutWin()
//Handles input specific to "about" window
void handleAboutWin(Winfo activeInfo, int ch){
	switch (ch) {
		case 'h':
			//Open help page if h is pressed
			system("sensible-browser https://docs.google.com/document/d/1pPvelGZFUB94YW7hT2COPODH8C3Av2oZ9XNly7zuCIk/edit");
	}
}


//Input routing: ------------------------------------------------------------


//handleInput()
//Takes state information, and routes input to correct handlers
void handleInput(Winfo activeInfo, int ch){

	//Handle screen switching by state (set on creation)
	MENU* activeMenu = getMenu(activeInfo);

	//Global key bindings (works on all screens)
	switch(ch){
		case '1':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cWelcwin(activeInfo);
			setState(activeInfo, 0);
			return;

		case '2':
			if(activeMenu != NULL) remMenu(activeInfo);
			toDirectory("/home");
			remWin(activeInfo);
			cSelectwin(activeInfo);
			setState(activeInfo, 1);
			return;

		case '3':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cPlaylistwin(activeInfo);
			setState(activeInfo, 2);
			return;

		case '4':
			if(activeMenu != NULL) remMenu(activeInfo);
			remWin(activeInfo);
			cAboutwin(activeInfo);
			setState(activeInfo, 3);
			return;

		case KEY_UP : //UP arrow key
			//Menu selector up
			menu_driver(getMenu(activeInfo), REQ_UP_ITEM);
			break;
		case KEY_DOWN : //DOWN arrow key
			//Menu selector down
			menu_driver(getMenu(activeInfo), REQ_DOWN_ITEM);
			break;
		case 'k' :
			//Kill background screen
			system("pkill screen");
			break;
		case 'v':
			//Invoke cava visualizer
			startVisualizer();
			break;
		case '[':
			//Previous song
			prevSong();
			break;
		case ']':
			//Next song
			nextSong();
			break;
		case 'o':
			//Restart song
			restartSong();
			break;
		case ' ':
			//Play/pause the current playback
			playPause();
			break;

	}//End of switch


	//If not switching screens, handle input based on active window
	int state = getState(activeInfo);
	switch(state){
		case 0:
			handleWelcWin(activeInfo, ch);
			break;
		case 1:
			handleSelectWin(activeInfo, ch);
			break;
		case 2:
			handlePlaylistWin(activeInfo, ch);
			break;
		case 3:
			handleAboutWin(activeInfo, ch);
			break;
	}
}
