all: testeCamera

LIB = `pkg-config opencv --libs`
FLAGS = -std=c++11

clean:
	rm -f testeCamera

Camera.o: Camera.cpp Camera.hpp
	g++ $< -o $@ -c $(LIB) $(FLAGS)

testeCamera: testeCamera.cpp Camera.o
	g++ $< -o $@ Camera.o $(LIB) $(FLAGS)