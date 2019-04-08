all: test_FD test_ABL test_LBAS test_GABSGS test_MogOpenCV test_LBMOG

INCLUDE = package_bgs
LIBS = `pkg-config opencv --libs`
FLAGS = --std=c++11 -I$(INCLUDE)

clean:
	rm -f test_FD
	rm -f test_ABL
	rm -f test_LBAS
	rm -f test_GABSGS 
	rm -f test_MogOpenCV
	rm -f *.o

#Frame Difference
FrameDifferenceBGS.o: package_bgs/FrameDifferenceBGS.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

test_FD: frameDifference_test.cpp FrameDifferenceBGS.o
	g++ $< -o $@ FrameDifferenceBGS.o $(LIBS) $(FLAGS)

#Adaptive Background
AdaptiveBackgroundLearning.o: package_bgs/AdaptiveBackgroundLearning.cpp
	g++ $< -o $@ -c $(FLAGS) $(LIBS)

test_ABL: AdaptiveBackgroundLearning_test.cpp AdaptiveBackgroundLearning.o
	g++ $< -o $@ AdaptiveBackgroundLearning.o $(LIBS) $(FLAGS)

#LBAdaptiveSOM
BGModel.o: package_bgs/lb/BGModel.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

BGModelSom.o: package_bgs/lb/BGModelSom.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

LBAdaptiveSOM.o: package_bgs/lb/LBAdaptiveSOM.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

test_LBAS: LBAdaptiveSOM_test.cpp LBAdaptiveSOM.o BGModelSom.o BGModel.o
	g++ $< -o $@ LBAdaptiveSOM.o BGModelSom.o BGModel.o $(LIBS) $(FLAGS)

#LBMog
BGModelMog.o: package_bgs/lb/BGModelMog.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

lbmog.o: package_bgs/lb/LBMixtureOfGaussians.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/lb

test_LBMOG: LBMog_test.cpp lbmog.o BGModelMog.o BGModel.o
	g++ $< -o $@ lbmog.o BGModelMog.o BGModel.o $(LIBS) $(FLAGS)

#GABGS
Image.o: package_bgs/dp/Image.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

WrenGA.o: package_bgs/dp/WrenGA.cpp 
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

DPWrenGABGS.o: package_bgs/dp/DPWrenGABGS.cpp
	g++ $< -o $@ -c $(LIBS) --std=c++11 -I$(INCLUDE)/dp

test_GABSGS: GABGS_test.cpp WrenGA.o DPWrenGABGS.o  Image.o
	g++ $< -o $@ Image.o WrenGA.o DPWrenGABGS.o $(LIBS) $(FLAGS)

#Mog OpenCV
test_MogOpenCV: test_MogOpenCV.cpp
	g++ $< -o $@ $(LIBS) $(FLAGS)