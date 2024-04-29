#Building the matrix library
default: all

all: matex.o matrix.o matrow.o
	g++ -g -o libcppmat.so matrow.o matex.o matrix.o -fPIC -shared

matex.o:
	g++ -g -c -o matex.o -I../include ../src/matex.cpp -fPIC

matrix.o:
	g++ -g -c -o matrix.o -I../include ../src/matrix.cpp -fPIC

matrow.o:
	g++ -g -c -o matrow.o -I../include ../src/matrow.cpp -fPIC

clean:
	rm *.o *.so