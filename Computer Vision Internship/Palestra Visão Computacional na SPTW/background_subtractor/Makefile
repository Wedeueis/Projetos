all: test_LBMOG

INCLUDE = package_bgs
LIBS = `pkg-config opencv --libs`
FLAGS = --std=c++11 -I$(INCLUDE)

clean:
	rm -f test_LBMOG
	rm -f *.o


#LBMog
BGModel.o: package_bgs/lb/BGModel.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb
	
BGModelMog.o: package_bgs/lb/BGModelMog.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

lbmog.o: package_bgs/lb/LBMixtureOfGaussians.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

test_LBMOG: LBMog_test.cpp lbmog.o BGModelMog.o BGModel.o
	g++ $< -o $@ lbmog.o BGModelMog.o BGModel.o $(LIBS) $(FLAGS)
