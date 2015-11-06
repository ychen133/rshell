CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic

all: rshell.cpp 
	$(CC) $(CFLAGS) -o a.out rshell.cpp

rshell: rshell.cpp 
	cd src; $(CC) $(CFLAGS) -o a.out rshell.cpp


