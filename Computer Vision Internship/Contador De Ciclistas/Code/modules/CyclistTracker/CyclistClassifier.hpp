#ifndef CYCLISTCLASSIFIER_HPP
#define CYCLISTCLASSIFIER_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Winline"
#include <opencv2/opencv.hpp>
#pragma GCC diagnostic pop

#include "Classifier.hpp"
#include "TrackedObject.hpp"
#include <memory>
#include <string>

class CyclistClassifier: public Classifier {
private:
	int minWidth;
	int maxWidth;
	int minHeight;
	int maxHeight;
	int minX;
	int maxX;
	int minY;
	int maxY;
	int traveledDistance;
	int framesAlive;

	unsigned int countedPoint[100];
	unsigned short int pos;
	unsigned int totalLeftCount;
	unsigned int totalRightCount;
	cv::Rect referenceBox;
	
public:
    CyclistClassifier(int, Conf &);
    ClassificationResult *Classify(DetectionResult *);
    void PlotResults(cv::Mat frame);
protected:
    void AccountPoint(std::shared_ptr<TrackedObject>, ClassificationResult &);
};

#endif
