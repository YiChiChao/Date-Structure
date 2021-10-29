CC = gcc
CFLAGS = -g -Wall
OBJECTS = shorty

all: $(OBJECTS)

shorty: shorty.c
	$(CC) $(CFLAGS) $^ -o $@

do:
	./shorty<testcase;

clean:
	rm $(OBJECTS)