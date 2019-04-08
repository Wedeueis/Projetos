#ifndef CYCLIST_TRACKED_OBJECT_HPP
#define CYCLIST_TRACKED_OBJECT_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Winline"
#include <opencv2/opencv.hpp>
#pragma GCC diagnostic pop

#include "TrackedObject.hpp"

class CyclistTrackedObject: public TrackedObject {
public:
	cv::Point pt;
	cv::Point pt0;
	cv::Rect rect;
	unsigned int id;
	unsigned int framesAlive;
	bool ltr; //Left to right direction

	CyclistTrackedObject();	
	CyclistTrackedObject(cv::Point pt, cv::Rect rectangle,unsigned int id,
						 bool left2right);
	void Plot(cv::Mat &);
	int GetId();
};
#endif
