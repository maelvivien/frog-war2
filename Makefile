# Makefile
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer

all: main

main : main.o window.o sprite.o
	$(CC) main.o window.o sprite.o -o main $(LIBS)

sprite.o : entity.hpp sprite.hpp sprite.cpp
	$(CC) -c sprite.cpp entity.hpp

window.o : window.cpp sprite.hpp
	$(CC) -c window.cpp sprite.hpp



clean:
	rm -f *.o mainOBJ = main.o window.o sprite.o
