#ifndef DUMMYPROCESSOR_HPP
#define DUMMYPROCESSOR_HPP

#include "Preprocessor.hpp"

/**
 * @brief Example Preprocessor class. Extends Preprocessor class and
 * implements basic methods
 */
class DummyPreprocessor: public Preprocessor {
public:
    DummyPreprocessor(int, Conf &);
    cv::Mat Preprocess(cv::Mat &);
};

#endif
