#include <iostream>
#include <chrono>
#include <vector>
#include "opencv2/opencv.hpp"

#include "package_bgs/AdaptiveBackgroundLearning.h"
#include "package_bgs/FrameDifferenceBGS.h"
#include "package_bgs/dp/DPWrenGABGS.h"
#include "package_bgs/lb/LBMixtureOfGaussians.h"

#include "plotter.hpp"
#include <opencv2/bgsegm.hpp>

using namespace std;
using namespace cv;
using namespace std::chrono;
typedef high_resolution_clock clk;

int main(int argc, char **argv) {
	VideoCapture cap("rtsp://admin:1@10.10.144.137:554/ISAPI/streaming/channels/102?auth=YWRtaW46MQ==");
	//VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "Cannot open the camera!" << endl;
		return -1;
	}

	Mat frame;
	
	IBGS *bgs1 = new AdaptiveBackgroundLearning();
	IBGS *bgs2 = new DPWrenGABGS();
	IBGS *bgs3 = new FrameDifferenceBGS();
	IBGS *bgs4 = new LBMixtureOfGaussians();
	Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2(500,20,true);
	Ptr<bgsegm::BackgroundSubtractorMOG> pMOG1 = bgsegm::createBackgroundSubtractorMOG(500,20);
	bool m0=false,m1=false,m2=false,m3=false,m4=false,m5=false;	
	int index=0;
	vector<int> times(100);
	bool test = false;
	
	
	while(true){
		clk::time_point t1 = clk::now();
		cap >> frame;
		imshow("Frame Orginal", frame);
#ifdef ENABLE_EQUALIZE
		/// Convert to grayscale
		Mat eqFrame;
 	 	cvtColor( frame, eqFrame, CV_BGR2GRAY );
	  	/// Apply Histogram Equalization
	  	equalizeHist( eqFrame, eqFrame);

#endif

		imshow("Frame Eq", eqFrame);
		vector<Mat> images;
		Mat mask0, mask1, mask2, mask3, mask4, mask5, bkgmodel1, bkgmodel2, bkgmodel3, bkgmodel5;
		if( !(frame.empty()) && (frame.rows>0) ) {
			pMOG2 -> apply(frame, mask0);
			bgs1->process(frame, mask1, bkgmodel1);
			bgs2->process(frame, mask2, bkgmodel2);
			bgs3->process(frame, mask3, bkgmodel3);
			bgs4->process(frame, mask5, bkgmodel5);
			pMOG1 -> apply(frame, mask4);
		}
		images.push_back(mask0);
		images.push_back(mask1);
		images.push_back(mask2);
		images.push_back(mask3);
		images.push_back(mask4);
		images.push_back(mask5);

		Mat display = showManyImages("Background Subtraction",images,400);		
		if( !(display.empty()) && (display.rows>0) ) imshow("Background Subtraction",display);
		clk::time_point t2 = clk::now();
		times[index] = (int)duration_cast<milliseconds>( t2 - t1 ).count();	
		index++;
		if(index>=100){
			if(!test)test=true;
			index = 0;
		}
		
		if(m0 && !(mask0.empty()) && (mask0.rows>0) ){
			imshow("Native OpenCV MOG", mask0);
		}
		if(m1 && !(mask1.empty()) && (mask1.rows>0) ){
			imshow("Adaptive Bacground Learning", mask1);
		}
		if(m2 && !(mask2.empty()) && (mask2.rows>0) ){
			imshow("Gaussian Average", mask2);
		}
		if(m3 && !(mask3.empty()) && (mask3.rows>0)){
			imshow("Frame Difference", mask3);
		}
		if(m4 && !(mask4.empty()) && (mask4.rows>0)){
			imshow("OpenCV MOG1", mask4);
		}
		if(m5 && !(mask5.empty()) && (mask5.rows>0)){
			imshow("LB MOG", mask5);
		}
		
		int k = waitKey(30)&0xFF;

		if(k == 'q' || k == 27)
			break;
		else if(k == '1'){
			if(m0==false)
				m0=true;
			else{ 
				destroyWindow("Native OpenCV MOG");
				m0=false;
			}
		} else if(k == '2'){
			if(m1==false)
				m1=true;
			else{ 
				destroyWindow("Adaptive Bacground Learning");
				m1=false;
			}
		} else if(k == '3'){
			if(m2==false)
				m2=true;
			else{ 
				destroyWindow("Gaussian Average");
				m2=false;
			}
		}else if(k == '4'){
			if(m3==false)
				m3=true;
			else{ 
				destroyWindow("Frame Difference");
				m3=false;
			}
		}else if(k == '5'){
			if(m4==false)
				m4=true;
			else{ 
				destroyWindow("OpenCV MOG1");
				m4=false;
			}
		}else if(k == '6'){
			if(m5==false)
				m5=true;
			else{ 
				destroyWindow("LB MOG");
				m5=false;
			}
		}
			
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
