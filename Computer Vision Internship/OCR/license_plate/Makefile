all: preprocess

clean:
	rm -f preprocess
	rm -f *.o

preprocess: preprocess.cpp
	g++ $< -o $@ `pkg-config opencv --libs`
