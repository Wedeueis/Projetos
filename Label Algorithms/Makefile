all: test_cuda labelOnePass labelTwoPass labelOpenCV

clean: 
	rm -f test_cuda
	rm -f labelOnePass
	rm -f labelTwoPass
	rm -f labelOpenCV
	rm -f *.o

ppm.o: ppm.cpp
	g++ $< -o $@ -c

labelOnePass: labelOnePass.cpp ppm.o
	g++ $< -o $@ ppm.o -std=c++11

test_cuda: label_test.cu ppm.o
	nvcc $< -o $@ ppm.o -std=c++11

disjointset.o: disjointset.cpp
	g++ $< -o $@ -c -std=c++11

labelTwoPass: labelTwoPass.cpp ppm.o disjointset.o
	g++ $< -o $@ ppm.o disjointset.o -std=c++11

labelOpenCV: labelopencv.cpp
	g++ $< -o $@ -std=c++11 `pkg-config opencv --libs`