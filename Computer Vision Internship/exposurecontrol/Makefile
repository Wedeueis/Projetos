all: exposurecontrol videomean

LIBOPENCV= `pkg-config opencv --libs`
FLAGS = -std=c++11

clean: 
	rm -f exposurecontrol
	rm -f videomean
	rm -f *.o

Camera.o: Camera.cpp Camera.hpp
	g++ $< -o $@ -c $(LIB) $(FLAGS)

exposurecontrol: exposurecontrol.cpp Camera.o
	g++ $< -o $@ Camera.o $(LIBOPENCV) $(FLAGS)

videomean: videomean.cpp
	g++ $< -o $@ $(LIBOPENCV)