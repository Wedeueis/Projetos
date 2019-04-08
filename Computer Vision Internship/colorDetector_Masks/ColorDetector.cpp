#include "ColorDetector.hpp"

cv::Point g_mouse(400,200);
cv::Scalar g_meanColor(128,128,128);
cv::Mat g_frame;
int g_range_upperH = 0, g_range_upperS = 95, g_range_upperV = 95;
int g_range_lowerH = 43, g_range_lowerS = 0, g_range_lowerV = 64;
cv::Scalar g_colorsHSV[4];
int g_selectedColor = 0;
int G_BLUR_SIZE=5;
int G_MORPH_CLOSE_SIZE=21;
int G_MORPH_OPEN_SIZE=11;
int G_OFFSET=5;

void on_morph_trackbar(int){	
	if( (G_BLUR_SIZE%2) == 0)
		G_BLUR_SIZE++;
	if( (G_MORPH_OPEN_SIZE%2) == 0)
		G_MORPH_OPEN_SIZE++;
	if( (G_MORPH_CLOSE_SIZE%2) == 0)
		G_MORPH_CLOSE_SIZE++;
}
void on_color_trackbar(int){}

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
		cv::Mat mask_pickcolor(G_OFFSET*2,G_OFFSET*2,CV_8UC1,cv::Scalar(1,1,1));
		cv::circle(mask_pickcolor, cv::Point(G_OFFSET, G_OFFSET), G_OFFSET,
			   cv::Scalar(255,255,255), -1, 8 , 0 );
		//Find Mean of colors (Excluding outer areas)
		cv::GaussianBlur(image_roi, image_roi, cv::Size(3, 3),0,0);
		g_meanColor = cv::mean(image_roi,mask_pickcolor);
		resize(image_roi, image_roi, cv::Size(), 8, 8, cv::INTER_CUBIC);
		cv::namedWindow("roi");		
		cv::imshow("roi", image_roi);
	}
}

void createRangeTrackBars(const char* windowName){
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cvCreateTrackbar("RANGE_UPPER_H", windowName, &g_range_upperH, 128, on_color_trackbar);
	cvCreateTrackbar("RANGE_UPPER_S", windowName, &g_range_upperS, 128, on_color_trackbar);
	cvCreateTrackbar("RANGE_UPPER_V", windowName, &g_range_upperV, 128, on_color_trackbar);
	cvCreateTrackbar("RANGE_LOWER_H", windowName, &g_range_lowerH, 128, on_color_trackbar);
	cvCreateTrackbar("RANGE_LOWER_S", windowName, &g_range_lowerS, 128, on_color_trackbar);
	cvCreateTrackbar("RANGE_LOWER_V", windowName, &g_range_lowerV, 128, on_color_trackbar);
}

void createMorphTrackBars(const char* windowName){
	cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
	cvCreateTrackbar("BLUR_SIZE", windowName, &G_BLUR_SIZE, 21, on_morph_trackbar);
	cvCreateTrackbar("MORPH_CLOSE_SIZE", windowName, &G_MORPH_CLOSE_SIZE, 21, on_morph_trackbar);
	cvCreateTrackbar("MORPH_OPEN_SIZE", windowName, &G_MORPH_OPEN_SIZE, 21, on_morph_trackbar);
	cvCreateTrackbar("OFFSET", windowName, &G_OFFSET, 21, on_morph_trackbar);
}

//Function to create a color mask and "cut" the ball in the source image
void colorDetection(cv::Mat src, cv::Mat &mask){
	cv::Mat hsv;
	//3-channel binary mask
	cv::GaussianBlur(src, src, cv::Size(G_BLUR_SIZE, G_BLUR_SIZE) ,0,0);
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
	cv::inRange(hsv, cv::Scalar(g_colorsHSV[g_selectedColor][0] - g_range_lowerH, g_colorsHSV[g_selectedColor][1] - g_range_lowerS, g_colorsHSV[g_selectedColor][2] - g_range_lowerV), cv::Scalar(g_colorsHSV[g_selectedColor][0]  + g_range_upperH + 1 , g_colorsHSV[g_selectedColor][1]  + g_range_upperS + 1, g_colorsHSV[g_selectedColor][2]  + g_range_upperV + 1), mask);
	//image morphology transformation
	cv::Mat element = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( G_MORPH_CLOSE_SIZE,G_MORPH_CLOSE_SIZE ),cv::Point( -1, -1 ) );
  	cv::Mat element2 = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( G_MORPH_OPEN_SIZE,G_MORPH_OPEN_SIZE ),cv::Point( -1, -1 ) );
  	cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, element);
	cv::morphologyEx( mask, mask, cv::MORPH_OPEN, element2);
}

std::vector<cv::Mat> multColorDetection(cv::Mat src){
	std::vector<cv::Mat> masks;	
	cv::Mat hsv;
	cv::GaussianBlur(src, src, cv::Size(G_BLUR_SIZE, G_BLUR_SIZE),0,0);
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
	cv::Mat element = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( G_MORPH_CLOSE_SIZE,G_MORPH_CLOSE_SIZE ),cv::Point( -1, -1 ) );
	cv::Mat element2 = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( G_MORPH_OPEN_SIZE,G_MORPH_OPEN_SIZE ),cv::Point( -1, -1 ) );
	//3-channel binary mask
	for(int i = 0; i<4; i++){
		cv::Mat mask;
		cv::inRange(hsv, cv::Scalar(g_colorsHSV[i][0] - g_range_lowerH, g_colorsHSV[i][1] - g_range_lowerS, g_colorsHSV[i][2] - g_range_lowerV), cv::Scalar(g_colorsHSV[i][0]  + g_range_upperH + 1 , g_colorsHSV[i][1]  + g_range_upperS + 1, g_colorsHSV[i][2]  + g_range_upperV + 1), mask);
		//image morphology transformation
	  	cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, element);
		cv::morphologyEx( mask, mask, cv::MORPH_OPEN, element2);
		masks.push_back(mask);
	}
	return masks;
}

cv::Mat maskBitwiseAND(cv::Mat frame, cv::Mat mask){
	cv::Mat tgt, thrs;
	//mask aplication
	cv::Mat mask3[] = { mask,mask,mask };
	cv::merge(mask3, 3, thrs);
	cv::bitwise_and(thrs, frame, tgt);
	return tgt;
}

cv::Rect drawRect(cv::Mat &frame){
	cv::Point p1, p2;
	if(g_mouse.x - G_OFFSET >= 0)
		if (g_mouse.x + G_OFFSET <= frame.cols ) p1.x = g_mouse.x - G_OFFSET;
		else p1.x = frame.cols - G_OFFSET*2;
	else p1.x = 0;
	if(g_mouse.y-G_OFFSET>=0)
		if (g_mouse.y + G_OFFSET <= frame.rows ) p1.y = g_mouse.y - G_OFFSET;
		else p1.y = frame.rows - G_OFFSET*2;
	else p1.y = 0;

	p2.x = p1.x + G_OFFSET*2;
	p2.y = p1.y + G_OFFSET*2;
 	
	cv::	Rect rect(p1, p2);
	rectangle(frame, rect, cv::Scalar(255,0,0), 1, 8, 0);
	return rect;
}


void actionConfigureColors(cv::VideoCapture &cap) {
  cv::namedWindow("pickColors");
  cv::namedWindow("reference");
  cv::setMouseCallback("pickColors", colorCallBack);

  while(true) {
	cap >> g_frame;
	cv::Mat reference = g_frame.clone();
	cv::cvtColor(reference,reference, cv::COLOR_BGR2HSV, 0);
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

	cv::circle(g_frame,cv::Point(g_mouse.x,g_mouse.y),G_OFFSET,g_meanColor,-1);

	cv::imshow("pickColors", g_frame);
	cv::imshow("reference", reference);

	int k = cv::waitKey(30) & 0xFF;
	if( k==27 || k == 'q') {
		break;
	}else if( k >= 49 && k <= 53) {
		g_selectedColor = k - 49;
	}
	}
	cv::destroyWindow("pickColors");
	cv::destroyWindow("mask");
	cv::destroyWindow("roi");
	cv::destroyWindow("reference");
}
