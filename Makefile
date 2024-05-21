# Makefile
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer

all: main

main : main.o window.o sprite.o timer.o enemy.o player.o attacksprite.o
	$(CC) main.o window.o sprite.o timer.o enemy.o player.o attacksprite.o -o main $(LIBS)

sprite.o : entity.hpp sprite.hpp sprite.cpp
	$(CC) -c sprite.cpp

window.o : window.cpp enemy.hpp player.hpp
	$(CC) -c window.cpp

timer.o : timer.cpp
	$(CC) -c timer.cpp

enemy.o : sprite.hpp enemy.hpp enemy.cpp
	$(CC) -c enemy.cpp

player.o : sprite.hpp player.hpp player.cpp
	$(CC) -c player.cpp

attacksprite.o : sprite.hpp attacksprite.hpp attacksprite.cpp
	$(CC) -c attacksprite.cpp


clean:
	rm -f *.o mainOBJ = main.o window.o sprite.o timer.o enemy.o player.o attacksprite.o test_fonctions.o

test: test_fonctions

test_fonctions: test_fonctions.o window.o sprite.o timer.o enemy.o player.o attacksprite.o 
	$(CC)  test_fonctions.o window.o sprite.o timer.o enemy.o player.o attacksprite.o  -o test $(LIBS)

test_fonctions.o: test_fonctions.cpp window.hpp player.hpp sprite.hpp
	$(CC) -c test_fonctions.cpp
