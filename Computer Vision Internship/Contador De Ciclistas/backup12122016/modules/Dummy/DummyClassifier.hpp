#ifndef DUMMYCLASSIFIER_HPP
#define DUMMYCLASSIFIER_HPP

#include "Classifier.hpp"

/**
 * @brief Example Classifier class. Extends Classifier class and
 * implements basic methods
 */
class DummyClassifier: public Classifier {
public:
     DummyClassifier(int, Conf &);
     ClassificationResult *Classify(DetectionResult *);
     void PlotResults(cv::Mat frame);
};

#endif
