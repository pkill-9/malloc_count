# Simplistic Makefile for malloc_count example

CC = gcc
CFLAGS = -g -Wextra -Wall -ansi 
LDFLAGS =
LIBS = 
OBJS = test.o memlog.o

all: test

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f *.o test
