#include "DummyDetector.hpp"

DummyDetector::DummyDetector(int processorId, Conf &cfg) : Detector(processorId, cfg) {}

DetectionResult *DummyDetector::Detect(cv::Mat &frame) {
    DetectionResult *retval = new DetectionResult;
    std::cout << "Detector activated\n";
    return retval;
}
