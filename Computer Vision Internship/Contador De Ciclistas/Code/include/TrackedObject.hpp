#ifndef TRACKEDOBJECT_HPP
#define TRACKEDOBJECT_HPP

#include <opencv2/opencv.hpp>

/***
 * @brief Data abstraction for detected elements
 */
class TrackedObject {
public:
    virtual ~TrackedObject();
    virtual void Plot(cv::Mat &);
    virtual int GetId();
};

#endif
