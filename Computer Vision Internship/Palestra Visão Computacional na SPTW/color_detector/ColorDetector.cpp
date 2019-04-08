#include "ColorDetector.hpp"

cv::Point g_mouse(400,200);
cv::Scalar g_meanColor(128,128,128);
cv::Mat g_frame;
int g_rangeH = 25 ,g_rangeS =25, g_rangeV = 60;
cv::Scalar g_colorsHSV[4];
int g_selectedColor = 0;

void on_trackbar(int){};

void colorCallBack(int event, int x, int y, int flags, void* userdata) {
	if (event == cv::EVENT_LBUTTONUP) {
		//Get click x y position to a global variable
		g_mouse.x = x;
		g_mouse.y = y;
	    	//Get Region of Interest
		cv::Rect roi = drawRect(g_frame);
		cv::Mat image_roi = g_frame(roi);
		cv::cvtColor(image_roi,image_roi, cv::COLOR_BGR2HSV, 0);
		//create a round mask
		cv::Mat mask_pickcolor(OFFSET*2,OFFSET*2,CV_8UC1,cv::Scalar(1,1,1));
		cv::circle(mask_pickcolor, cv::Point(OFFSET, OFFSET), OFFSET,
			   cv::Scalar(255,255,255), -1, 8 , 0 );
		//Find Mean of colors (Excluding outer areas)
		cv::GaussianBlur(image_roi, image_roi, cv::Size(3, 3),0,0);
		g_meanColor = cv::mean(image_roi,mask_pickcolor);
	}
}

void createTrackBars(const char* windowName){
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cvCreateTrackbar("RANGE_H", windowName, &g_rangeH, 128, on_trackbar);
	cvCreateTrackbar("RANGE_S", windowName, &g_rangeS, 128, on_trackbar);
	cvCreateTrackbar("RANGE_V", windowName, &g_rangeV, 128, on_trackbar);
}

//Function to create a color mask and "cut" the ball in the source image
void colorDetection(cv::Mat src, cv::Mat &mask){
	cv::Mat hsv;
	//3-channel binary mask
	cv::GaussianBlur(src, src, cv::Size(BLUR_SIZE, BLUR_SIZE),0,0);
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
	cv::inRange(hsv, cv::Scalar(g_colorsHSV[g_selectedColor][0] - g_rangeH, g_colorsHSV[g_selectedColor][1] - g_rangeS, g_colorsHSV[g_selectedColor][2] - g_rangeV), cv::Scalar(g_colorsHSV[g_selectedColor][0]  + g_rangeH + 1 , g_colorsHSV[g_selectedColor][1]  + g_rangeS + 1, g_colorsHSV[g_selectedColor][2]  + g_rangeV + 1), mask);
	//image morphology transformation
	cv::Mat element = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( MORPH_CLOSE_SIZE,MORPH_CLOSE_SIZE ),cv::Point( -1, -1 ) );
  	cv::Mat element2 = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( MORPH_OPEN_SIZE,MORPH_OPEN_SIZE ),cv::Point( -1, -1 ) );
  	cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, element);
	cv::morphologyEx( mask, mask, cv::MORPH_OPEN, element2);
}

void maskBitwiseAND(cv::Mat frame, cv::Mat mask){
	cv::Mat tgt, thrs;
	//mask aplication
	cv::Mat mask3[] = { mask,mask,mask };
	cv::merge(mask3, 3, thrs);
	cv::bitwise_and(thrs, frame, tgt);
	const char* windowName = "Mask";
	cv::imshow(windowName, tgt);
	createTrackBars(windowName);
}

cv::Rect drawRect(cv::Mat &frame){
	cv::Point p1, p2;
	if(g_mouse.x - OFFSET >= 0)
		if (g_mouse.x + OFFSET <= frame.cols ) p1.x = g_mouse.x - OFFSET;
		else p1.x = frame.cols - OFFSET*2;
	else p1.x = 0;
	if(g_mouse.y-OFFSET>=0)
		if (g_mouse.y + OFFSET <= frame.rows ) p1.y = g_mouse.y - OFFSET;
		else p1.y = frame.rows - OFFSET*2;
	else p1.y = 0;

	p2.x = p1.x + OFFSET*2;
	p2.y = p1.y + OFFSET*2;
 	
	cv::	Rect rect(p1, p2);
	rectangle(frame, rect, cv::Scalar(255,0,0), 1, 8, 0);
	return rect;
}


void actionConfigureColors(cv::VideoCapture &cap) {
  
	
  cv::namedWindow("pickColors");
  cv::setMouseCallback("pickColors", colorCallBack);

  while(true) {
	cap >> g_frame;
	std::stringstream frase;
	frase << "Click on the screen to save a color in position " << g_selectedColor + 1 << ".";
	cv::putText(g_frame, frase.str(), cv::Point(10,30), 
		    cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
	//Get HSV Color of Mouse point
	std::stringstream ss1, ss2, ss3;
	g_colorsHSV[g_selectedColor][0] = round(g_meanColor[0]);
	ss1 << g_colorsHSV[g_selectedColor][0];
	g_colorsHSV[g_selectedColor][1] = round(g_meanColor[1]);
	ss2 << g_colorsHSV[g_selectedColor][1];
	g_colorsHSV[g_selectedColor][2] = round(g_meanColor[2]);
	ss3 << g_colorsHSV[g_selectedColor][2];
	std::string color_hsv("["+ ss1.str() +","+ ss2.str() +","+ ss3.str() +"]");

	cv::putText(g_frame, color_hsv, cv::Point(10,60), cv::FONT_HERSHEY_SIMPLEX, 0.8,
		    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);

	cv::circle(g_frame,cv::Point(g_mouse.x,g_mouse.y),OFFSET,g_meanColor,-1);

	cv::imshow("pickColors", g_frame);

	int k = cv::waitKey(30) & 0xFF;
	if( k==27 || k == 'q') {
		break;
	}else if( k >= 49 && k <= 53) {
		g_selectedColor = k - 49;
	}
	}
	cv::destroyWindow("pickColors");
	cv::destroyWindow("mask");
}
