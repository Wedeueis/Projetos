#include "CyclistClassifier.hpp"
#include "CyclistClassificationResult.hpp"
#include "CyclistTrackedObject.hpp"

CyclistClassifier::CyclistClassifier(int processorId, Conf &cfg): Classifier(processorId, cfg) {
    this->minWidth = this->GetSpecificConf("minWidth");
    this->maxWidth = this->GetSpecificConf("maxWidth");
    this->minHeight = this->GetSpecificConf("minHeight");
    this->maxHeight = this->GetSpecificConf("maxHeight");
    this->minX = this->GetSpecificConf("minX");
    this->maxX = this->GetSpecificConf("maxX");
    this->minY = this->GetSpecificConf("minY");
    this->maxY = this->GetSpecificConf("maxY");
    this->traveledDistance = this->GetSpecificConf("traveledDistance");
    this->framesAlive = this->GetSpecificConf("framesAlive");
    
    memset(this->countedPoint, -1, sizeof(this->countedPoint));
    
    //Initialize reference box
    int roiId = this->GetRoiId();
    int DTPTs[2][2];
    this->GetConfiguration()->roiGetDTPTs(roiId, DTPTs);
    cv::Rect referenceBox(DTPTs[0][0],
			  DTPTs[0][1],
			  DTPTs[1][0] - DTPTs[0][0],
			  DTPTs[1][1] - DTPTs[0][1]);
    
    this->pos = 0;
    this->totalLeftCount = 0;
    this->totalRightCount = 0;
    this->referenceBox = referenceBox;
}

ClassificationResult *CyclistClassifier::Classify(DetectionResult *dr) {
        CyclistClassificationResult *retval = new CyclistClassificationResult();
        auto objs = dr->GetObjects();
        
        for (std::shared_ptr<TrackedObject> trackedObject: objs) {
            this->AccountPoint(trackedObject, *retval);
        }
        
        return dynamic_cast<ClassificationResult *>(retval);
}

void CyclistClassifier::AccountPoint(std::shared_ptr<TrackedObject> trackedObject, ClassificationResult &classificationResult) {
    CyclistTrackedObject *point = dynamic_cast<CyclistTrackedObject *>(trackedObject.get());
    
	bool newElement = true;
	for (auto it : this->countedPoint) {
	    if (it == point->id) {
		newElement = false;
		break;
	    }
	}
		
	if (newElement && 
	    (this->framesAlive > -1 && point->framesAlive > this->framesAlive || this->framesAlive == -1) && 
	    (this->traveledDistance > -1 && abs(point->pt.x - point->pt0.x) >= this->traveledDistance || this->traveledDistance == -1) &&
	    (this->minWidth > -1 && point->rect.width >= this->minWidth || this->minWidth == -1) &&
	    (this->minHeight > -1 && point->rect.height >= this->minHeight || this->minHeight == -1) &&
	    (this->maxWidth > -1 && point->rect.width <= this->maxWidth || this->maxWidth == -1) &&
	    (this->maxHeight > -1 && point->rect.height <= this->maxHeight || this->maxHeight == -1) &&
	    (this->minX > -1 && point->rect.x >= this->minX || this->minX == -1) &&
	    (this->minY > -1 && point->rect.y >= this->minY || this->minY == -1) &&
	    (this->maxX > -1 && (point->rect.x + point->rect.width) <= this->maxX || this->maxX == -1) &&
	    (this->maxY > -1 && (point->rect.y + point->rect.height) <= this->maxY || this->maxY == -1)) {
		if (point->pt.x > this->referenceBox.tl().x &&
		    point->pt.x < this->referenceBox.br().x &&
		    point->pt.y > this->referenceBox.tl().y &&
		    point->pt.y < this->referenceBox.br().y) {
		    
		    classificationResult << trackedObject;
		    
		    if (point->ltr) {
			this->totalLeftCount++;

		    }
		    else {
			this->totalRightCount++;
		    }
		    
		    this->countedPoint[pos++] = point->id;
		    if (pos >= sizeof(countedPoint)/sizeof(countedPoint[0])) {
			    pos = 0;
		    }
		}
	}
}

void CyclistClassifier::PlotResults(cv::Mat frame) {

	std::stringstream ss;
	ss << " >> " << totalLeftCount << "   ";
	ss << " << " << totalRightCount;
	cv::putText(frame, ss.str(), cv::Point(10,30), 
		    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
}