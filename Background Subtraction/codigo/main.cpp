#include <iostream>
#include <chrono>
#include <vector>
#include "opencv2/opencv.hpp"

#include "package_bgs/lb/LBMixtureOfGaussians.h"

using namespace std;
using namespace cv;
using namespace std::chrono;
typedef high_resolution_clock clk;

int main(int argc, char **argv) {
	VideoCapture cap("../peds/video.avi");
	if(!cap.isOpened()){
		cout << "Cannot open video file!" << endl;
		return -1;
	}
	
	IBGS *bgs = new LBMixtureOfGaussians();

	Mat frame;
	
	namedWindow("Frame",1);
	int index=0;
	vector<int> times(100);

	int frame_count = 0;
	
	while(true){
		clk::time_point t1 = clk::now();
		cap >> frame;
		frame_count++;

		if(frame.rows <= 0){
			break;
		}else if(frame_count > 170){
            break;
        }

		GaussianBlur(frame, frame, cv::Size(3, 3), 0);

		Mat mask, bkgmodel;
		bgs->process(frame, mask, bkgmodel);

		erode(mask, mask, Mat());
		Mat element = getStructuringElement(cv::MORPH_RECT,
              cv::Size(7, 7),
              cv::Point(3,3) );
		dilate(mask, mask, element);
		erode(mask, mask, Mat());

		cvtColor(mask, mask, CV_BGR2GRAY);
		std::vector<std::vector<cv::Point>> contours;
		findContours(mask,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_SIMPLE);

		for (size_t idx = 0; idx < contours.size(); idx++) {
			cv::Rect rec= cv::boundingRect(contours[idx]);
			if(rec.height>10){
				cv::rectangle(frame, rec, cv::Scalar(0,255,0));
			}
			
		}

		imshow("Frame", frame);

		clk::time_point t2 = clk::now();
		times[index] = (int)duration_cast<milliseconds>( t2 - t1 ).count();	
		index++;

		int k = waitKey(80)&0xFF;
		if(k == 'q' || k == 27) {
			break;
		} else if(k =='s') {
			std::cout << frame_count<< std::endl;
			imwrite("../results/foreground_lbmog.jpg", mask);
			imwrite("../results/trackers.jpg", frame);
		}else if(k =='p') {
			while(true){
				int k2 = waitKey(80)&0xFF;
				if(k2=='p'){
					break;
				}
			}
		}
	}

	int sum=0 ,mean=0;
	for(int i = 0; i<=index; i++)
		sum+=times[i];
	mean = sum/(index+1);
		
	cout << "Tempo médio de processamento: " << mean << endl;

	return 0;
}  
