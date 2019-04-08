#ifndef POINT_TRACKER_HPP
#define POINT_TRACKER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Winline"
#include <opencv2/opencv.hpp>
#pragma GCC diagnostic pop
#include "CyclistTrackedObject.hpp"

class PointTracker {
private:
	PointTracker *reference;
	static unsigned int absolutePointNumber;
	unsigned int point_id;
	unsigned int maximum_threshold;
	bool hasReference;
	
	int DistanceInThreshold(cv::Point &a, cv::Point &b);
	
public:
	std::map<int, CyclistTrackedObject> points;
	
	PointTracker(unsigned int threshold = 10);	
	PointTracker(unsigned int threshold, PointTracker *reference);	
	void AddPoint(cv::Point &point, cv::Rect &rectangle);
	void ZeroAbsolutePointNumber(void);
};

class RectangleTracker : public PointTracker {
private:
	cv::Point GetRectangleCenter(cv::Rect &rec);

public:		
	RectangleTracker(unsigned int threshold);
	RectangleTracker(unsigned int threshold, PointTracker *reference);

	void AddRectangle(cv::Rect &rectangle);
};

#endif
