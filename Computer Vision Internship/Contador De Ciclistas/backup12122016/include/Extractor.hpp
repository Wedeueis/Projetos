#ifndef EXTRACTOR_HPP
#define EXTRACTOR_HPP

#include "Config.hpp"
#include "ClassificationResult.hpp"
#include "Preprocessor.hpp"
#include "Detector.hpp"
#include "Classifier.hpp"
#include "Factory.hpp"
#include "Counters.hpp"

/**
 * @brief Instantiates and coordinates the interfacing between 
 * plugabble combonents
 */
class Extractor {
    Preprocessor *preprocessor;
    Detector *detector;
    Classifier *classifier;
#ifdef DEBUG
    cv::VideoWriter video;
#endif
    
public:
    Extractor(Factory&); 
    ~Extractor();  
    void Extract(cv::Mat &frame, Counters &); 
};

#endif
