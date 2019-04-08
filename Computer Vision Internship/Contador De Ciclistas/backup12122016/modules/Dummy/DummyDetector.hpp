#ifndef DUMMYDETECTOR_HPP
#define DUMMYDETECTOR_HPP

#include "Detector.hpp"

/**
 * @brief Example Detector class. Extends Detector class and
 * implements basic methods
 */
class DummyDetector: public Detector {
public:
    DummyDetector(int, Conf &);
    DetectionResult *Detect(cv::Mat &);
};

#endif
