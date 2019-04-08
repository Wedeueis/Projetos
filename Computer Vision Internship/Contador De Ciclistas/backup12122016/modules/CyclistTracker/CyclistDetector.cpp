#include "CyclistDetector.hpp"
#include "PointTracker.hpp"
#include <time.h>

CyclistDetector::CyclistDetector(int processorId, Conf &cfg) : Detector(processorId, cfg) {    
    this->distance_threshold = this->GetSpecificConf("distanceThreshold");

    int contourThreshold = this->GetSpecificConf("contourThreshold");
    this->object_locator = new ObjectLocator(contourThreshold);
}

DetectionResult *CyclistDetector::Detect(cv::Mat &fore) {
    DetectionResult *retval = new DetectionResult;
    
    this->CreateNewTracker();
    this->AddRectanglesToTracker(fore);
    this->AccountNewObjects(retval);
    this->RenewTrackers();
    
    return retval;
}


CyclistDetector::~CyclistDetector() {
	delete this->object_locator;
}

void CyclistDetector::CreateNewTracker() {
	if (this->old_tracker) {
		this->new_tracker = new RectangleTracker(this->distance_threshold,
							(this->old_tracker));
	}
	else {		
		this->new_tracker = new RectangleTracker(this->distance_threshold);
	}			
}

void CyclistDetector::AddRectanglesToTracker(cv::Mat &fore) {
	auto rects_from_countour = this->object_locator->DetectObjects(fore);
	for (auto rec: rects_from_countour) {
		this->new_tracker->AddRectangle(rec);
	}
}

void CyclistDetector::AccountNewObjects(DetectionResult *dr) {
	if (this->old_tracker && this->new_tracker) {
		for(auto trackedRect: this->new_tracker->points) {
			auto trackedObj = trackedRect.second;
			CyclistTrackedObject *newObj = new CyclistTrackedObject(trackedObj);
			auto ptr = std::shared_ptr<TrackedObject> (dynamic_cast<TrackedObject *>(newObj));
			dr->AddObject(ptr);
		}
		delete this->old_tracker;
		this->old_tracker = nullptr;
	}
}

void CyclistDetector::RenewTrackers() {
	if (old_tracker) {
		delete old_tracker;
		old_tracker = nullptr;
	}
	if (new_tracker) {
		this->old_tracker = this->new_tracker;
	}  
}


