#include "DummyPreprocessor.hpp"
#include <iostream>

DummyPreprocessor::DummyPreprocessor(int processorId, Conf &cfg) : Preprocessor(processorId, cfg) {}

cv::Mat DummyPreprocessor::Preprocess(cv::Mat &frame) {
    std::cout << "Processor activated\n";
    return frame;     
}
