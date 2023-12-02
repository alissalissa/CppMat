#Builds out the unit tests
default: compile

compile:
	g++ -g -o exception_test -I../include -L../build -Wl,-rpath,../build -lcppmat exception_test.cpp

clean:
	rm ./exception_test