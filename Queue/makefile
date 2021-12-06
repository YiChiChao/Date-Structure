CC = gcc
CFLAGS = -g -Wall
OBJECTS = basic

all:$(OBJECTS)

basic: queue_base.c
	$(CC) $(CFLAGS) $^ -o $@

do:
	./basic

clean:
	rm $(OBJECTS)