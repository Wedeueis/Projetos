#include "CyclistClassificationResult.hpp"
#include "CyclistTrackedObject.hpp"

void CyclistClassificationResult::operator>>(Counters &counts) {
    counts.SetModuleName(MODULE_NAME);
    
    for (auto trackedElement: this->GetClassified()) {
        auto cyclistTrackedElement = dynamic_cast<CyclistTrackedObject *>(trackedElement.get());
        if (cyclistTrackedElement->ltr) {
                counts.Increment("ltr");
        }
        else {
                counts.Increment("rtl");
        }
    }
}
