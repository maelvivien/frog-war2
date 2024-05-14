# Makefile
CC = g++
CFLAGS = -Wall -Wextra -std=c++11
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_mixer

OBJ = main.o window.o entity.o sprite.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o mainOBJ = main.o window.o entity.o sprite.o