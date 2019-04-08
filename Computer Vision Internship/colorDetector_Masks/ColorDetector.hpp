#ifndef COLOR_DETECTOR_H
#define COLOR_DETECTOR_H

#include "opencv2/opencv.hpp"
#include <string>
#include <vector>

extern cv::Mat g_frame;
extern int g_range_upperH, g_range_upperS, g_range_upperV;
extern int g_range_lowerH, g_range_lowerS, g_range_lowerV;
extern cv::Scalar g_colorsHSV[4];
extern int g_selectedColor;
extern int G_BLUR_SIZE;
extern int G_MORPH_CLOSE_SIZE;
extern int G_MORPH_OPEN_SIZE;
extern int G_OFFSET;

void createRangeTrackBars(const char* windowName);
void createMorphTrackBars(const char* windowName);
void colorDetection(cv::Mat src, cv::Mat &mask);
std::vector<cv::Mat> multColorDetection(cv::Mat src);
cv::Mat maskBitwiseAND(cv::Mat frame, cv::Mat mask);
void actionConfigureColors(cv::VideoCapture &cap);
cv::Rect drawRect(cv::Mat &frame);

#endif
