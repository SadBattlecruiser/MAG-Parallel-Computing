CC=g++
CFLAGS=-c -Wall -std=c++11 -fopenmp
LFLAGS=-fopenmp
HEADERSPATH= -I .\\headers

all: point_o matrix_o frame_o mesh_o main_o
	$(CC) -o out\\main.exe out\\*.o $(LFLAGS)

point_o:
	$(CC)  -o out\\point.o $(CFLAGS) $(HEADERSPATH) src\\point.cpp

matrix_o:
	$(CC) -o out\\matrix.o $(CFLAGS) $(HEADERSPATH) src\\matrix.cpp

frame_o:
	$(CC) -o out\\frame.o $(CFLAGS) $(HEADERSPATH) src\\frame.cpp

mesh_o:
	$(CC) -o out\\mesh.o $(CFLAGS) $(HEADERSPATH) src\\mesh.cpp

main_o:
	$(CC) -o out\\main.o $(CFLAGS) $(HEADERSPATH) src\\main.cpp

clean:
	rm -f out\\*.o
