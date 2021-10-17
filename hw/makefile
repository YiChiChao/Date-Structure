CC = gcc
CFLAGS = -g -Wall
card: card.c
	$(CC) $(CFLAGS) $^ -o $@

do:
	./card < test

clean:
	rm card