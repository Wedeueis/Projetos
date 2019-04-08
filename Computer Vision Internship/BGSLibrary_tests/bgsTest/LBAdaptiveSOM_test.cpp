#include <iostream>
#include <chrono>
#include <vector>
#include "opencv2/opencv.hpp"

#include "package_bgs/lb/LBAdaptiveSOM.h"

using namespace std;
using namespace cv;
using namespace std::chrono;
typedef high_resolution_clock clk;

int main(int argc, char **argv) {
	VideoCapture cap("rtsp://admin:1@10.10.144.137:554/ISAPI/streaming/channels/102?auth=YWRtaW46MQ==");
	if(!cap.isOpened()){
		cout << "Cannot open the camera!" << endl;
		return -1;
	}

	Mat frame;
	
	IBGS *bgs = new LBAdaptiveSOM();
	
	namedWindow("Frame",1);
	int index=0;
	vector<int> times(100);
	bool test = false;
	
	while(true){
		clk::time_point t1 = clk::now();
		cap >> frame;
		
		imshow("Frame", frame);
		
		Mat mask, bkgmodel;
		bgs->process(frame, mask, bkgmodel);
		clk::time_point t2 = clk::now();
		times[index] = (int)duration_cast<milliseconds>( t2 - t1 ).count();	
		index++;
		if(index>=100){
			if(!test)test=true;
			index = 0;
		}

		int k = waitKey(30)&0xFF;
		if(k == 'q' || k == 27)
			break;
	}

	int sum=0 ,mean=0;
	if(test){
		for(int i = 0; i<100; i++)
			sum+=times[i];
		mean = sum/100;
	}else {
		for(int i = 0; i<=index; i++)
			sum+=times[i];
		mean = sum/(index+1);
	}
		
	cout << "Tempo médio de processamento: " << mean << endl;
		
	delete bgs;

	return 0;
}  
