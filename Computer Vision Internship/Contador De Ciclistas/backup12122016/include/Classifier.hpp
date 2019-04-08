#ifndef CLASSIFIER_HPP
#define CLASSIFIER_HPP

#include "ConfigReader.hpp"
#include "ClassificationResult.hpp"
#include "DetectionResult.hpp"
#include <opencv2/opencv.hpp>

/**
 * @brief Interface for object classification
 */
class Classifier : public ConfigReader {
public:
    Classifier(int, Conf &);
    
    /**
    * @brief Receives detection result and generates 
    * classificationResult
    */
    virtual ClassificationResult *Classify(DetectionResult *) = 0;
    virtual void PlotResults(cv::Mat frame) = 0;
};

#endif
