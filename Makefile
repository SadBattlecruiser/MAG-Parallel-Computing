CC=g++
CFLAGS=-Wall
HEADERSPATH= -I . -I .\SFML-2.5.1\include
LIBPATH= -L .\SFML-2.5.1\lib
LIBS=.\\SFML-2.5.1\\lib\\*.a

all:
	$(CC) *.cpp -o main_single.out $(HEADERSPATH)
