//backend.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef BACKEND_H
#define BACKEND_H

//Creates the background screen for file playback (requires screen dependency)
void createScreen(int killPrev);

//Shoves passed text into screen in background and simulates enter key
//char* command: the string to be passed and entered into the screen
void sendScreenCommand(char* command);

//Sends a play/pause command to screen
void playPause();

//Sends a end playback command to screen
void endPlayback();

//plays a single specified song
void startSingleSong(char* filePath);

//starts playback from a playlist file
//Assumes file is located in /usr/share/lemonade
void startPlaylist(char* fileName);

//Creates playlist file of absolute song paths, in the directory the program is run. Returns 0 on success, 1 on failure (file already exists).
//char* fileName: the name of the playlist file. Should always begin with a period, as playlists should be internal to the program.
//char* songFilePaths[]: an array of strings, each an absolute path to an mp3 file. LAST ARRAY ELEMENT MUST BE AN EMPTY STRING.
int createPlaylistFile(char* fileName, char* songFilePaths[]);

//Creates playlist of mp3s within a specified directory. To use, do a popen pwd command and pass result as parameter
void createPlaylistFromDir(char* dirPath, char* fileName);

//ON HOLD
//Creates a playlist file based of the current playlist
//int currentPlaylistToFile(char* playlistName);

int countLines();

//Creates a 2d char array that holds songs and folders in current directory
void lsOutput(char** choices);

#endif
