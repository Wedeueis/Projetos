#ifndef OBJECT_LOCATOR_HPP
#define OBJECT_LOCATOR_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Winline"
#include <opencv2/opencv.hpp>
#pragma GCC diagnostic pop

class ObjectLocator {
private:
    double contour_threshold;
    
public:
    ObjectLocator(double contour_threshold);
    std::vector<cv::Rect> DetectObjects(cv::Mat &frame);

protected:    
    std::vector<cv::Rect>
		GetBoundingBoxFromContour(std::vector<std::vector<cv::Point>> contours);
};

#endif
