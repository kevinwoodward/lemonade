# Makefile
# Makefile for use with CMPS 115 lemonade client

CC = gcc
FLAGS = -Wall
OBJECTS = client.o frontend.o backend.o helpers.o winInfo.o inputHandler.o
EXEBIN = lemonade

all : lemonade

lemonade : $(OBJECTS)
	$(CC) -o $(EXEBIN) $(OBJECTS) -lmenu -lncurses

helpers.o : helpers.h helpers.c
	$(CC) -c $(FLAGS) helpers.c

backend.o :	backend.h backend.c
	$(CC) -c $(FLAGS) backend.c

frontend.o : frontend.h frontend.c
	$(CC) -c $(FLAGS) frontend.c

winInfo.o : winInfo.h winInfo.c
	$(CC) -c $(FLAGS) winInfo.c

inputHandler.o : inputHandler.h inputHandler.c
	$(CC) -c $(FLAGS) inputHandler.c
	
client.o : client.c
	$(CC) -c $(FLAGS) client.c

clean :
	rm -f $(EXEBIN) $(OBJECTS)
