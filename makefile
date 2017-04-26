# Makefile
# Makefile for use with CMPS 115 lemonade frontend

CC = gcc
FLAGS = -c -std=c99 -Wall
OBJECTS = frontend.o
EXEBIN = frontend

all : frontend

frontend : frontend.o
	$(CC) -o $(EXEBIN) frontend.o

frontend.c :	frontend.c
	$(CC) -c $(FLAGS) frontend.c

clean :
	rm -f $(EXEBIN) $(OBJECTS)