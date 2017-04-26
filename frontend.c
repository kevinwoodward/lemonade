//frontend.c
//UCSC cmps 115 Spring 2017

#include <ncurses.h>
 
int main(int argc, char* argv[]){	
	initscr();
	printw("Hello World !!!");
	refresh();
	getch();
	endwin();
	return 0;
}