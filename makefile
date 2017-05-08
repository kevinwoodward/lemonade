# Makefile
# Makefile for use with CMPS 115 lemonade client

CC = gcc
FLAGS = -c -Wall
OBJECTS = client.o frontend.o backend.o helpers.o
EXEBIN = lemonade

all : lemonade

lemonade : $(OBJECTS)
	$(CC) -o $(EXEBIN) $(OBJECTS) -lncurses

helpers.o : helpers.h helpers.c
	$(CC) -c $(FLAGS) helpers.c

backend.o :	backend.h backend.c
	$(CC) -c $(FLAGS) backend.c

frontend.o : frontend.h frontend.c
	$(CC) -c $(FLAGS) frontend.c

client.o : client.c
	$(CC) -c $(FLAGS) client.c

clean :
	rm -f $(EXEBIN) $(OBJECTS)
