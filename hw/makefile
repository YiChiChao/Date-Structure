CC = gcc
CXX = g++
CXXFLAGS = -g -Wall -std=c++14
CFLAGS = -g -Wall
CHECKFLAGS = --leak-check=full -s
OBJECTS = bomb card shorty tree bridge test

all: $(OBJECTS)

bomb: bomb.c
	$(CC) $(CFLAGS) $^ -o $@

card: card.c
	$(CC) $(CFLAGS) $^ -o $@

shorty: shorty.c
	$(CC) $(CFLAGS) $^ -o $@

tree: tree_functions.c
	$(CC) $(CFLAGS) $^ -o $@

bridge: bridge.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

test: test.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@


do1:
	./bomb<test

do2:
	./card

do3:
	./shorty<testcase

do4:
	./tree<testcase4

do5:
	./bridge 

do6:
	./test<testcase6



clean:
	rm $(OBJECTS)