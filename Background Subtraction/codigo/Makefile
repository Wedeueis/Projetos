all: main test

INCLUDE = package_bgs
LIBS = `pkg-config opencv --libs`
FLAGS = --std=c++11 -I$(INCLUDE)

clean:
	rm -f main
	rm -f test
	rm -f *.o

#Frame Difference
FrameDifferenceBGS.o: package_bgs/FrameDifferenceBGS.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

#LBMog
BGModel.o: package_bgs/lb/BGModel.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

BGModelMog.o: package_bgs/lb/BGModelMog.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

lbmog.o: package_bgs/lb/LBMixtureOfGaussians.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

#Executaveis
test: test.cpp FrameDifferenceBGS.o lbmog.o BGModelMog.o BGModel.o
	g++ $< -o $@ FrameDifferenceBGS.o lbmog.o BGModelMog.o BGModel.o $(LIBS) $(FLAGS)

main: main.cpp lbmog.o BGModelMog.o BGModel.o
	g++ $< -o $@ lbmog.o BGModelMog.o BGModel.o $(LIBS) $(FLAGS)