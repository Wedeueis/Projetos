all: detectorTest

FLAGS = -g
LIBS = `pkg-config --libs opencv`
CPPVERSION = --std=c++11

clean:
	rm -f detectorTest
	rm -f *.o

ColorDetector.o: ColorDetector.cpp
	g++ $< -o $@ -c $(CPPVERSION) $(LIBS)

plotter.o: plotter.cpp
	g++ $< -o $@ -c $(CPPVERSION) $(LIBS)

detectorTest: detectorTest.cpp ColorDetector.o plotter.o
	g++ $< -o $@ ColorDetector.o plotter.o $(CPPVERSION) $(FLAGS) $(LIBS)

