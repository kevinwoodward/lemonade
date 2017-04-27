# Makefile
# Makefile for use with CMPS 115 lemonade frontend

CC = gcc
FLAGS = -c -std=c99 -Wall
OBJECTS = frontend.o hello.o screens.o
EXEBIN = frontend

all : frontend

frontend : frontend.o util.o screens.o
	$(CC) -o $(EXEBIN) frontend.o util.o screens.o -lncurses
	
hello : hello.o
	$(CC) -o hello hello.o -lncurses

frontend.o :	frontend.c
	$(CC) -c $(FLAGS) frontend.c
	
util.o : util.h util.c
	$(CC) -c $(FLAGS) util.c
	
screens.o : screens.h screens.c
	$(CC) -c $(FLAGS) screens.c
	
hello.o : hello.c
	$(CC) -c $(FLAGS) hello.c

clean :
	rm -f $(EXEBIN) $(OBJECTS) hello