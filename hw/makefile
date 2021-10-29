CC = gcc
CFLAGS = -g -Wall
OBJECTS = bomb card shorty

all: $(OBJECTS)

bomb: bomb.c
	$(CC) $(CFLAGS) $^ -o $@

card: card.c
	$(CC) $(CFLAGS) $^ -o $@

shorty: shorty.c
	$(CC) $(CFLAGS) $^ -o $@


do1:
	./bomb<test

do2:
	./card

do3:
	./shorty<testcase;


clean:
	rm $(OBJECTS)