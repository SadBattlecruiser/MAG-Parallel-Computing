CC=g++
CFLAGS=-Wall
HEADERSPATH= -I .\\headers -I .\\SFML-2.5.1\\include
LIBPATH= -L .\\SFML-2.5.1\\lib
LIBS=.\\SFML-2.5.1\lib\\*.a

all:
	$(CC) src\\*.cpp -o out\\main_single.out $(HEADERSPATH)
