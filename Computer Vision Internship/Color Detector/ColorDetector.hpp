#ifndef COLOR_DETECTOR_H
#define COLOR_DETECTOR_H

#include "opencv2/opencv.hpp"
#include <string>

#define BLUR_SIZE 5	
#define MORPH_CLOSE_SIZE 21
#define MORPH_OPEN_SIZE 11
#define OFFSET 10

extern cv::Mat g_frame;
extern int g_rangeH, g_rangeS, g_rangeV;
extern cv::Scalar g_colorsHSV[4];
extern int g_selectedColor;

void createTrackBars(const char* windowName);
void colorDetection(cv::Mat src, cv::Mat &mask);
void maskBitwiseAND(cv::Mat frame, cv::Mat mask);
void actionConfigureColors(cv::VideoCapture &cap);
cv::Rect drawRect(cv::Mat &frame);

#endif
