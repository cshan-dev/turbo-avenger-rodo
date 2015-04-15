#	Steven Skiena
#	March 26, 2002
#	Makefile for all "Programming Challenges" Book Programs
#

# Copyright 2003 by Steven S. Skiena; all rights reserved.
#
# Permission is granted for use in non-commerical applications
# provided this copyright notice remains intact and unchanged.
#
# These programs appear in my book:
#
# "Programming Challenges: The Programming Contest Training Manual"
# by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.
#
# See our website www.programming-challenges.com for additional information.
#
# This book can be ordered from Amazon.com at
#
# http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/


MAKEFILE = Makefile
SOURCES = queue.c graph.c bfs-dfs.c stack.c strong.c
OBJECTS = queue.o graph.o bfs-dfs.o stack.o strong.o
BINARIES = strong
INCLUDES = bool.h queue.h graph.h stack.h


CC = gcc
CFLAGS = -ggdb # -O4 -g -DNDEBUG -pg
LFLAGS = -lm # -g -lm -pg

make:	$(BINARIES)

$(OBJECTS):     $(INCLUDES)

$(OBJECTS):     $(MAKEFILE)

all:	$(BINARIES)



strong:		strong.o bfs-dfs.o queue.o graph.o stack.o
		$(CC) -o $@ strong.o bfs-dfs.o queue.o graph.o stack.o $(LFLAGS)

lint:
	lint -h $(SOURCES)

backup:	$(SOURCES) $(INCLUDES)
	cp $(SOURCES) backup
	cp $(INCLUDES) backup

clean:
	rm -f core *.o a.out $(BINARIES)

tar:
	make clean
	tar cvf /tmp/bookprograms.tar .
