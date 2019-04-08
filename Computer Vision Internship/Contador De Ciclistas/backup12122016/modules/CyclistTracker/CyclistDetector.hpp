#ifndef CYCLISTDETECTOR_HPP
#define CYCLISTDETECTOR_HPP

#include "Detector.hpp"
#include "PointTracker.hpp"
#include "ObjectLocator.hpp"

class CyclistDetector: public Detector {
private:
	RectangleTracker *old_tracker = nullptr;
	RectangleTracker *new_tracker = nullptr;
	ObjectLocator *object_locator = nullptr;
	unsigned int distance_threshold;
	unsigned int image_counter = 0;
    
public:
    CyclistDetector(int, Conf &);
    ~CyclistDetector();
    DetectionResult *Detect(cv::Mat &);
    
private:
	void CreateNewTracker();    
	void AddRectanglesToTracker(cv::Mat &fore);
	void AccountNewObjects(DetectionResult *dr);
	void RenewTrackers();
};

#endif
