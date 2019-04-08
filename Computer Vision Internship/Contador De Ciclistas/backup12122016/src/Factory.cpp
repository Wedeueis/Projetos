/* THIS FILE IS AUTOMATICALLY GENERATED. DO NOT MODIFY */

#include "Factory.hpp"

/* Modules */
#include "modules/CyclistTracker.hpp"
#include "modules/Dummy.hpp"

Factory::Factory(int processorId, Conf &cfg) {
        this->processorId = processorId;
        this->configuration = &cfg;
        
        std::string sProcessorType = this->configuration->processorProcessorType(this->processorId);
        this->processorType = this->getProcessorType(sProcessorType);
}

ProcessorType Factory::getProcessorType(std::string module) {
	if (module == "CyclistTracker") {
		 return CYCLIST_TRACKER;
	}
	if (module == "Dummy") {
		 return DUMMY;
	}
}

Preprocessor *Factory::createPreprocessor() {
        Preprocessor *preprocessor;
        switch(this->processorType) {
			case CYCLIST_TRACKER:
				preprocessor = dynamic_cast<Preprocessor *>(new CyclistPreprocessor(this->processorId, *this->configuration));
				break;
			case DUMMY:
				preprocessor = dynamic_cast<Preprocessor *>(new DummyPreprocessor(this->processorId, *this->configuration));
				break;
		}
        return preprocessor;
}

Detector *Factory::createDetector() {
        Detector *detector;
        switch(this->processorType) {
			case CYCLIST_TRACKER:
				detector = dynamic_cast<Detector *>(new CyclistDetector(this->processorId, *this->configuration));
				break;
			case DUMMY:
				detector = dynamic_cast<Detector *>(new DummyDetector(this->processorId, *this->configuration));
				break;
		}
        return detector;
}

Classifier *Factory::createClassifier() {
        Classifier *classifier;
        switch(this->processorType) {
			case CYCLIST_TRACKER:
				classifier = dynamic_cast<Classifier *>(new CyclistClassifier(this->processorId, *this->configuration));
				break;
			case DUMMY:
				classifier = dynamic_cast<Classifier *>(new DummyClassifier(this->processorId, *this->configuration));
				break;
		}
        return classifier;
}
        