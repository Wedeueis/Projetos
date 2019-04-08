#ifndef DETECTIONRESULT_HPP
#define DETECTIONRESULT_HPP

#include "TrackedObject.hpp"
#include <vector>
#include <memory>

/**
 * @brief Data abstraction for detection process result. Encapsulates 
 * all the detected elements
 */
class DetectionResult {
private:
    std::vector<std::shared_ptr<TrackedObject>> trackedObjects;
public:
    /**
     * @brief Adds detected object to result vector
     */
    void AddObject(std::shared_ptr<TrackedObject>);
    
    /**
     * @brief Retrieves vector of detected objects
     */
    std::vector<std::shared_ptr<TrackedObject>> GetObjects();
};

#endif
