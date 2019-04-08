#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include "ConfigReader.hpp"
#include "DetectionResult.hpp"
#include <opencv2/opencv.hpp>

/**
 * @brief Interface for object detection
 */
class Detector : public ConfigReader {
public:
    Detector(int, Conf &);
        
    /**
    * @brief Receives preprocessed frame and returns a DetectionResult,
    * a vector of TrackedObjects
    */
    virtual DetectionResult *Detect(cv::Mat &) = 0;
};

#endif
