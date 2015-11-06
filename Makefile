CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic

all:  
	cd src; $(CC) $(CFLAGS) -o rshell rshell.cpp

rshell:  
	cd src; $(CC) $(CFLAGS) -o rshell rshell.cpp


