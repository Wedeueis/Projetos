all: testFD

INCLUDE = package_bgs
LIBS = `pkg-config opencv --libs`
FLAGS = --std=c++11 -I$(INCLUDE)

clean:
	rm -f test_FD
	rm -f *.o

#Frame Difference
FrameDifferenceBGS.o: package_bgs/FrameDifferenceBGS.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

testFD: testeFrameDiff.cpp FrameDifferenceBGS.o
	g++ $< -o $@ FrameDifferenceBGS.o $(LIBS) $(FLAGS)
