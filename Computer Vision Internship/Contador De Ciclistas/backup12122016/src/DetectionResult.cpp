#include "DetectionResult.hpp"

void DetectionResult::AddObject(std::shared_ptr<TrackedObject> obj) {
        this->trackedObjects.push_back(obj);
}

std::vector<std::shared_ptr<TrackedObject>> DetectionResult::GetObjects() {
        return this->trackedObjects;
}
