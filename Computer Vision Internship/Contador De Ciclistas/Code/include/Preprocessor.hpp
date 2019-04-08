#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include "ConfigReader.hpp"
#include <opencv2/opencv.hpp>


/**
 * @brief Interface for frame preprocessor
 */
class Preprocessor : public ConfigReader{
public:
    Preprocessor(int, Conf &);
    
    /**
     * @brief Preprocess receives captured frame and outputs 
     * preprocessed frame
     */
    virtual cv::Mat Preprocess(cv::Mat &) = 0;
};

#endif
