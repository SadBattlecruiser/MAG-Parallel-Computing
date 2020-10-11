CC=g++
CFLAGS=-c -Wall -std=c++11
HEADERSPATH= -I .\\headers

all: point_o matrix_o frame_o mesh_o main_o
	$(CC) -o out\\main_single.exe out\\*.o

point_o:
	$(CC) $(CFLAGS) $(HEADERSPATH) -o out\\point.o src\\point.cpp

matrix_o:
	$(CC) $(CFLAGS) $(HEADERSPATH) -o out\\matrix.o src\\matrix.cpp

frame_o:
	$(CC) $(CFLAGS) $(HEADERSPATH) -o out\\frame.o src\\frame.cpp

mesh_o:
	$(CC) $(CFLAGS) $(HEADERSPATH) -o out\\mesh.o src\\mesh.cpp

main_o:
	$(CC) $(CFLAGS) $(HEADERSPATH) -o out\\main_single.o src\\main_single.cpp

clean:
	rm -f out\\*.o
