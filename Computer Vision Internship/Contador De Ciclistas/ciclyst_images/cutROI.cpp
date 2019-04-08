#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Point p1(400,200), p2(400,200);
int selectedPoint = 1;
void mouseCallBack(int event, int x, int y, int flags, void* userdata);

int(int argc, int *argv[]){
	
}

void mouseCallBack(int event, int x, int y, int flags, void* userdata){
	if (event == cv::EVENT_LBUTTONUP) {
		//Get click x y position to a global variable
		if(selectedPoint == 1){
			p1.x = x;
			p1.y = y;
		}else if(selectedPoint == 2){
			p2.x = x;
			p2.y = y;
		}
	}
}

Rect drawRect(Mat &frame, Point p){	
	cv::	Rect rect(p1, p2);
	rectangle(frame, rect, cv::Scalar(255,0,0), 1, 8, 0);
	return rect;
}
