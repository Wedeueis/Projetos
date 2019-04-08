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

#MOG1
mog.o: MOG/bgfg_gaussmix.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -IMOG

#LBMOG
BGModel.o: package_bgs/lb/BGModel.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

BGModelMog.o: package_bgs/lb/BGModelMog.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

lbmog.o: package_bgs/lb/LBMixtureOfGaussians.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

#Plotter
plotter.o: plotter.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11

testAll: testAll.cpp WrenGA.o DPWrenGABGS.o  Image.o AdaptiveBackgroundLearning.o FrameDifferenceBGS.o mog.o BGModel.o BGModelMog.o lbmog.o plotter.o 
	g++ $< -o $@ -DENABLE_EQUALIZE Image.o WrenGA.o DPWrenGABGS.o AdaptiveBackgroundLearning.o FrameDifferenceBGS.o mog.o BGModel.o BGModelMog.o lbmog.o plotter.o $(LIBS) $(FLAGS)
