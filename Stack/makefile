CC = gcc
CFLAGS = -g -Wall
OBJECTS = infixTOpostfix

all: $(OBJECTS)

infixTOpostfix: infix_to_postfix_stack.c
	$(CC) $(CFLAGS) $^ -o $@

do:
	./infixTOpostfix

clean:
	rm $(OBJECTS)