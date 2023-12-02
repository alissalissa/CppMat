#Building the matrix library
default: compile

compile: matex.o matrix.o
    g++ -g -o libcppmat.so matex.o matrix.o -fPIC -shared

matex.o:
    g++ -g -c -o matex.o -I../include ../src/matex.cpp -fPIC

matrix.o:
    g++ -g -c -o matrix.o -I../include ../src/matrix.cpp -fPIC

clean:
    rm *.o *.so