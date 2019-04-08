all: testAll

INCLUDE = package_bgs
LIBS = `pkg-config opencv --libs`
FLAGS = --std=c++11 -I$(INCLUDE)

clean:
	rm -f testAll
	rm -f *.o

#Frame Difference
FrameDifferenceBGS.o: package_bgs/FrameDifferenceBGS.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

#Adaptive Background
AdaptiveBackgroundLearning.o: package_bgs/AdaptiveBackgroundLearning.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

#GABGS
Image.o: package_bgs/dp/Image.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

WrenGA.o: package_bgs/dp/WrenGA.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

DPWrenGABGS.o: package_bgs/dp/DPWrenGABGS.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

testAll: testAll.cpp WrenGA.o DPWrenGABGS.o  Image.o AdaptiveBackgroundLearning.o FrameDifferenceBGS.o
	g++ $< -o $@ Image.o WrenGA.o DPWrenGABGS.o AdaptiveBackgroundLearning.o FrameDifferenceBGS.o $(LIBS) $(FLAGS)
