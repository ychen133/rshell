CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic
BINDIR = bin

all:  
	cd src; $(CC) $(CFLAGS) -o rshell rshell.cpp; mkdir bin; mv rshell bin

rshell:  
	cd src; $(CC) $(CFLAGS) -o rshell rshell.cpp; mkdir bin; mv rshell bin 


