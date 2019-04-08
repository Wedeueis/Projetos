#ifndef CLASSIFICATIONRESULT_HPP
#define CLASSIFICATIONRESULT_HPP

#include "Counters.hpp"
#include "TrackedObject.hpp"
#include <vector>
#include <memory>

/**
 * @brief Data abstraction for the classification process
 */
class ClassificationResult {
private:
    std::vector<std::shared_ptr<TrackedObject>>classified;
public:
    /**
     * @brief Adds classified object to instance list
     */
    void operator<<(std::shared_ptr<TrackedObject>);
    
    /**
     * @brief Extracts data from classification results
     */
    virtual void operator>>(Counters &);
    
    /**
     * @brief Retrieves list of classified objects
     */
    std::vector<std::shared_ptr<TrackedObject>>GetClassified();
};

#endif
