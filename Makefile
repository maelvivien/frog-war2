# Makefile
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer

all: main

main : main.o window.o sprite.o timer.o
	$(CC) main.o window.o sprite.o timer.o -o main $(LIBS)

sprite.o : entity.hpp sprite.hpp sprite.cpp
	$(CC) -c sprite.cpp

window.o : window.cpp sprite.hpp
	$(CC) -c window.cpp

timer.o : timer.cpp
	$(CC) -c timer.cpp


clean:
	rm -f *.o mainOBJ = main.o window.o sprite.o timer.o
