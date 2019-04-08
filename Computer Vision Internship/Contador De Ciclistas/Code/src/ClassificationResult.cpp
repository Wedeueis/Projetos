#include "ClassificationResult.hpp"

void ClassificationResult::operator>>(Counters &counters) {}

/**
 * @brief Copies reference to tracked vector
 */
void ClassificationResult::operator<<(std::shared_ptr<TrackedObject> obj) {
        this->classified.push_back(obj);
}

std::vector<std::shared_ptr<TrackedObject>>ClassificationResult::GetClassified() {
        return this->classified;
}

