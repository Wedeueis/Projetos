#include "CyclistTrackedObject.hpp"

CyclistTrackedObject::CyclistTrackedObject() {
	this->ltr = 0;
	this->framesAlive = 0;
}

CyclistTrackedObject::CyclistTrackedObject(cv::Point pt, cv::Rect rectangle, unsigned int id,
						 	 bool left2right) {
	this->pt = pt;
	this->pt0 = pt;
	this->rect = rectangle;
	this->id = id;
	this->ltr = left2right;
	this->framesAlive = 0;
}

void CyclistTrackedObject::Plot(cv::Mat &frame) {
	cv::rectangle(frame, this->rect, cv::Scalar(0, 0, 255), 1);
}

int CyclistTrackedObject::GetId() {
	return this->id;
}
