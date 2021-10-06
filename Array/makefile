CC = gcc
CFLAGS = -g -Wall
OBJECTS = trycode multcode

all: $(OBJECTS)

trycode: try.c 
	$(CC) $(CFLAGS) $^ -o $@

multcode:Matrix_Multi.c
	$(CC) $(CFLAGS) $^ -o $@

try: 
	./trycode

mult:
	./multcode

clean:
	rm $(OBJECTS)
