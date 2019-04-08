#include "ColorDetector.hpp"


int main() {
	cv::VideoCapture cap(0);
	if(!cap.isOpened())
		return -1;
	
	cv::Mat frame, mask;
	cv::namedWindow("Frame",cv::WINDOW_AUTOSIZE);
	
	while(true){
		cap >> frame;
		cv::imshow("Frame",frame);
		colorDetection(frame, mask);
		maskBitwiseAND(frame, mask);
		int k = cv::waitKey(30) & 0xFF;
		if(k == 27 || k == 'q')
			break;
		else if(k == 'c')
			actionConfigureColors(cap);
		else if( k >= 49 && k <= 53) {
			g_selectedColor = k - 49;
		}
	}
}
