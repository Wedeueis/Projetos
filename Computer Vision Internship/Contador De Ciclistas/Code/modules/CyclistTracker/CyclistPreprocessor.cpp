#include "CyclistPreprocessor.hpp"
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winline"
CyclistPreprocessor::CyclistPreprocessor(int processorId, Conf &cfg) : Preprocessor(processorId, cfg) {  
    
#ifdef OPENCV3
	#ifdef LB_MOG
		this->bg = new LBMixtureOfGaussians();
	#else
    	this->bg = cv::createBackgroundSubtractorMOG2(5000,200,false);
    #endif
	#ifdef ENABLE_GLARE_MINIMIZATION
	    this->bgSunGlareMinimize = cv::createBackgroundSubtractorMOG2();
	#endif
#endif
#ifdef ENABLE_CAM_CALIBRATION
    this->CAMERA_MAT=(cv::Mat_<double>(3,3) << 2.4125343282050253e+03, 0., 3.5150000000000000e+02, 0. ,
               				       2.4125343282050253e+03, 2.3950000000000000e+02, 0., 0., 1.);
    this->DIST_COEF=(cv::Mat_<double>(1,5) << -6.1258730846785614e+00, 1.7881388280983067e+01, 0., 0., 1.2840250181803588e+03);
#endif
}
#pragma GCC diagnostic pop

CyclistPreprocessor::~CyclistPreprocessor(){
#ifdef OPENCV3
	delete bg;
#endif
}

cv::Mat CyclistPreprocessor::Preprocess(cv::Mat &frame) {
    int roiId = this->GetRoiId();
    
    //Retrieve perspective limits
    int PTs[4][2];
    this->GetConfiguration()->roiGetPTs(roiId, PTs);
    	
    cv::Point2f p[4];
    for (int i = 0; i < sizeof(p)/sizeof(p[0]); i++) {
	p[i].x = PTs[i][0];
	p[i].y = PTs[i][1];
    }
    
    //Retrieve interest area
    int DTPTs[2][2];
    this->GetConfiguration()->roiGetDTPTs(roiId, DTPTs);
    
    cv::Rect interestArea(DTPTs[0][0],
			  DTPTs[0][1],
			  DTPTs[1][0] - DTPTs[0][0],
			  DTPTs[1][1] - DTPTs[0][1]);

    cv::resize(frame, frame, cv::Size(160,120));
    //cvtColor(frame, frame, CV_BGR2GRAY);
	
#ifdef ENABLE_CAM_CALIBRATION
	//teste
	cv::initUndistortRectifyMap(CAMERA_MAT, DIST_COEF, cv::Mat(), CAMERA_MAT, frame.size(), CV_32FC1, map1, map2);
	cv::remap(frame, frame , map1, map2, cv::INTER_CUBIC);
#endif
    cv::GaussianBlur(frame, frame, cv::Size(3, 3),0,0);		

    this->PrepareFrame(frame, p[0], p[1], p[2], p[3]);
//    cv::flip(frame, frame, 0);
    cv::Mat fore = this->AcquireForeground(frame);
    this->InsertInterestArea(frame, interestArea);
    
#ifdef DEBUG
    imshow("Fore LB_MOG", fore);
#endif
    return fore;
}
	
cv::Mat CyclistPreprocessor::AcquireForeground(cv::Mat &frame) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winline"
	cv::Mat fore, model;

#ifdef OPENCV3
	#ifdef LB_MOG
		this->bg->process(frame, fore, bkgmodel);
		cvtColor(fore, fore, CV_BGR2GRAY);
	#else
		this->bg->apply(frame, fore);
	#endif
#else
		this->bg(frame, fore);
#endif
#ifdef ENABLE_GLARE_MINIMIZATION
	this->GlareMinimize(frame, fore);
#endif
	cv::dilate(fore, fore, cv::getStructuringElement( cv::MORPH_ELLIPSE,cv::Size( 5, 5 ), cv::Point( 0, 0 ) ));
	cv::dilate(fore, fore, cv::getStructuringElement( cv::MORPH_ELLIPSE,cv::Size( 5, 5 ), cv::Point( 0, 0 ) ));
	//cv::morphologyEx(fore, fore, cv::MORPH_CLOSE, cv::getStructuringElement( cv::MORPH_ELLIPSE,cv::Size( 3, 3 ), cv::Point( 0, 0 ) ) );
	return fore;
}

#ifdef ENABLE_GLARE_MINIMIZATION
void CyclistPreprocessor::GlareMinimize(cv::Mat &frame, cv::Mat &fore) {
    cv::Mat frameSunGlareMinimize;
	cv::Mat foreSunGlareMinimize;
    std::vector<cv::Mat> channels(3);

    cvtColor(frame, frameSunGlareMinimize, CV_BGR2HSV);

    cv::split(frameSunGlareMinimize, channels);
    cv::equalizeHist(channels[2], channels[2]);
    cv::merge(channels, frameSunGlareMinimize);

    cvtColor(frameSunGlareMinimize, frameSunGlareMinimize, CV_HSV2BGR);

#ifdef OPENCV3
	this->bgSunGlareMinimize->apply(frameSunGlareMinimize, foreSunGlareMinimize);
#else
	this->bgSunGlareMinimize(frameSunGlareMinimize, foreSunGlareMinimize);
#endif	

    int fgPercent = countNonZero(fore) * 100.0 / (fore.rows * fore.cols);
    if (fgPercent > GLARE_FG_PERCENT_CHANGE) {
        fore = foreSunGlareMinimize; 
    }    
}
#endif

#pragma GCC diagnostic pop
	
void CyclistPreprocessor::PrintText(cv::Mat &frame, std::string text,
							   cv::Point position) {
	cv::putText(frame, text,  position, CV_FONT_HERSHEY_PLAIN, 1,
				cv::Scalar(0, 0, 0));
}
	
void CyclistPreprocessor::InsertInterestArea(cv::Mat &frame,cv::Rect interestArea) {
	cv::rectangle(frame, interestArea, cv::Scalar(0, 0, 0), 1);
}

void CyclistPreprocessor::PrepareFrame(cv::Mat &frame, 
		  cv::Point2f p0, 
		  cv::Point2f p1, 
		  cv::Point2f p2, 
		  cv::Point2f p3) {
	//this->RotateImage(frame);
	this->PerspectiveTransform(frame, p0, p1, p2, p3);
	//this->CropImage(frame, cropArea);
}

void CyclistPreprocessor::RotateImage(cv::Mat &frame) {
	cv::transpose(frame, frame);
	cv::flip(frame, frame, 0);		
	cv::flip(frame, frame, 1);		
}

void CyclistPreprocessor::PerspectiveTransform(cv::Mat &frame, 
			  cv::Point2f p0, 
			  cv::Point2f p1, 
			  cv::Point2f p2, 
			  cv::Point2f p3) {
				  
	cv::Point2f inputQuad[4]; 
	cv::Point2f outputQuad[4];
	
	inputQuad[0] = p0;
	inputQuad[1] = p1;
	inputQuad[2] = p2;
	inputQuad[3] = p3;			
			
	int x0d, x1d, x2d, x3d, y0d, y1d, y2d, y3d;		 
	x0d=0;    y0d=0;
	x1d=p1.x; y1d=0;
	x2d=0;    y2d=std::max(p2.y - p0.y, p3.y - p1.y);
	x3d=p3.x; y3d=std::max(p2.y -p0.y, p3.y - p1.y);
	
	outputQuad[0] = cv::Point2f(x0d, y0d);
	outputQuad[1] = cv::Point2f(x1d, y1d);
	outputQuad[2] = cv::Point2f(x2d, y2d);
	outputQuad[3] = cv::Point2f(x3d, y3d);

	// Get the Perspective Transform Matrix and store in lambda
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winline"
	this->lambda = cv::getPerspectiveTransform(inputQuad, outputQuad);
#pragma GCC diagnostic pop
	
	// Apply the Perspective Transform just found to the src image
	cv::warpPerspective(frame, frame, this->lambda, frame.size());    
	cv::invert(this->lambda, this->inverseLambda, cv::DECOMP_LU);
	
	cv::Rect cropArea(outputQuad[0], outputQuad[3]);
	this->CropImage(frame, cropArea);
}

void CyclistPreprocessor::CropImage(cv::Mat &frame, cv::Rect cropArea) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winline"
		frame = frame(cropArea);
#pragma GCC diagnostic pop
}

cv::Mat CyclistPreprocessor::GetLambda(void) {
	return this->lambda;
}
cv::Mat CyclistPreprocessor::GetInverseLambda(void) {
	return this->inverseLambda;
}
