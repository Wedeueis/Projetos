#ifndef CYCLISTCLASSIFICATIONRESULT_HPP
#define CYCLISTCLASSIFICATIONRESULT_HPP

#include "ClassificationResult.hpp"
#define MODULE_NAME "CyclistTracker"

class CyclistClassificationResult: public ClassificationResult {
public:
        void operator>>(Counters &);
};

#endif
