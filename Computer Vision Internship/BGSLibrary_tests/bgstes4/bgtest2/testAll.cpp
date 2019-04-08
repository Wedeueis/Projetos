#include <iostream>
#include <chrono>
#include <vector>
#include "opencv2/opencv.hpp"

#include "package_bgs/AdaptiveBackgroundLearning.h"
#include "package_bgs/FrameDifferenceBGS.h"
#include "package_bgs/dp/DPWrenGABGS.h"

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
	
	IBGS *bgs1 = new AdaptiveBackgroundLearning();
	IBGS *bgs2 = new DPWrenGABGS();
	IBGS *bgs3 = new FrameDifferenceBGS();
	
	namedWindow("Frame",1);
	int index=0;
	vector<int> times(100);
	bool test = false;
	
	while(true){
		clk::time_point t1 = clk::now();
		cap >> frame;
		
		imshow("Frame", frame);

		Mat eqFrame;

		/// Convert to grayscale
 	 	cvtColor( frame, frame, CV_BGR2GRAY );

	  	/// Apply Histogram Equalization
	  	equalizeHist( frame, eqFrame );
		//GaussianBlur( eqFrame, eqFrame, Size( 3, 3 ), 0, 0 );
		imshow("EQ_Frame", eqFrame);
		
		Mat mask1, mask2, mask3, bkgmodel1, bkgmodel2, bkgmodel3;
		bgs1->process(eqFrame, mask1, bkgmodel1);
		bgs2->process(eqFrame, mask2, bkgmodel2);
		bgs3->process(eqFrame, mask3, bkgmodel3);
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
		
	delete bgs1;
	delete bgs2;
	delete bgs3;

	return 0;
}  
