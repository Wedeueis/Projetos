#include "ColorDetector.hpp"
#include "plotter.hpp"
#include <iostream>

int main() {
	cv::VideoCapture cap("rtsp://admin:1@10.10.144.137:554/ISAPI/streaming/channels/102?auth=YWRtaW46MQ==");
	if(!cap.isOpened())
		return -1;

	cv::Mat frame, mask;
	cv::namedWindow("Frame",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Masks",cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Result",cv::WINDOW_AUTOSIZE);
	
	while(true){
		cap >> frame;
		cv::imshow("Frame",frame);
		std::vector<cv::Mat> masks = multColorDetection(frame);
		std::vector<cv::Mat> tgts;

		for(int i = 0; i<4; i++) {
			cv::Mat tgt = maskBitwiseAND(frame, masks[i]);
			tgts.push_back(tgt);
		}

		cv::Mat displayMasks, resultMask;
		const char* title = "Masks";
		displayMasks = showManyImages(title,tgts,400);
		createRangeTrackBars("Masks");
		createMorphTrackBars("Result");
		cv::imshow("Masks",displayMasks);

		resultMask= masks[0].clone();
		for(int i = 1; i<masks.size(); i++) {
			resultMask += masks[i];
		}
		cv::Mat result = maskBitwiseAND(frame, resultMask);
		cv::imshow("Result",result);
		
		int k = cv::waitKey(30) & 0xFF;
		if(k == 27 || k == 'q'){;
			break;
		}
		else if(k == 'c')
			actionConfigureColors(cap);
		else if( k >= 49 && k <= 53) {
			g_selectedColor = k - 49;
		}
	}
}
