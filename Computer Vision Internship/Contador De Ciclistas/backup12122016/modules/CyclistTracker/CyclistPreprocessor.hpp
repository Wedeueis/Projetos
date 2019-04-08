#ifndef CYCLISTPROCESSOR_HPP
#define CYCLISTPROCESSOR_HPP

#include "Preprocessor.hpp"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Winline"
#include <opencv2/opencv.hpp>
#include "LBMixtureOfGaussians.h"
#pragma GCC diagnostic pop

//#define ENABLE_GLARE_MINIMIZATION
#define GLARE_FG_PERCENT_CHANGE 40

class CyclistPreprocessor: public Preprocessor {
private:
	
#ifdef OPENCV3
#ifdef LB_MOG
	IBGS *bg;
	cv::Mat bkgmodel;
#else
	cv::Ptr<cv::BackgroundSubtractor> bg;
#endif
#ifdef ENABLE_GLARE_MINIMIZATION
	cv::Ptr<cv::BackgroundSubtractor> bgSunGlareMinimize;
#endif
#else
	cv::BackgroundSubtractorMOG2 bg;
#endif
#ifdef ENABLE_CAM_CALIBRATION
	cv::Mat CAMERA_MAT, DIST_COEF, map1, map2;
#endif
	cv::Mat lambda; //used to get changes in perspective
	cv::Mat inverseLambda;
public:
    CyclistPreprocessor(int, Conf &);
	~CyclistPreprocessor();	
    cv::Mat Preprocess(cv::Mat &);
	cv::Mat AcquireForeground(cv::Mat &frame);	
	void PrintText(cv::Mat &frame, std::string text, cv::Point position);
	void InsertInterestArea(cv::Mat &frame,  cv::Rect interestArea);
	void PrepareFrame(cv::Mat &frame,
					  cv::Point2f p0, 
					  cv::Point2f p1, 
					  cv::Point2f p2, 
					  cv::Point2f p3);
	  
	void RotateImage(cv::Mat &frame);
	cv::Mat GetLambda(void);
	cv::Mat GetInverseLambda(void);

protected:
#ifdef ENABLE_GLARE_MINIMIZATION
    void GlareMinimize(cv::Mat &frame, cv::Mat &fore);
#endif
	void PerspectiveTransform(cv::Mat &frame, 
							  cv::Point2f p0, 
							  cv::Point2f p1, 
							  cv::Point2f p2, 
							  cv::Point2f p3);
	
	void CropImage(cv::Mat &frame, cv::Rect cropArea);
};

#endif
