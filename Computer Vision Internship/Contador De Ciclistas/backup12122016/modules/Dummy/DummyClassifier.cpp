#include "DummyClassifier.hpp"

DummyClassifier::DummyClassifier(int processorId, Conf &cfg): Classifier(processorId, cfg) {}

ClassificationResult *DummyClassifier::Classify(DetectionResult *) {
        ClassificationResult *retval = nullptr;
        std::cout << "Classifier activated\n";
        return retval;
}

void DummyClassifier::PlotResults(cv::Mat frame) {
	 std::cout << "Plotting classification result\n";
}
