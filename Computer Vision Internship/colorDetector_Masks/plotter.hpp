#ifndef PLOTTER_H
#define PLOTTER_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>
#include <string>

cv::Mat showManyImages(const char* title, std::vector<cv::Mat> images, int photoSize);

#endif
