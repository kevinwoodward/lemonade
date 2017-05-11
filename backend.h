//backend.h
//CMPS 115 Spring 2017
//Lemonade music player

#ifndef BACKEND_H
#define BACKEND_H

//Creates the background screen for file playback (requires screen dependency)
void createScreen();

//Shoves passed text into screen in background and simulates enter key
void sendScreenCommand(char* command);

//Sends a play/pause command to screen
void playpause();

//plays a single specified song
void startSingleSong(char* filePath);

#endif
