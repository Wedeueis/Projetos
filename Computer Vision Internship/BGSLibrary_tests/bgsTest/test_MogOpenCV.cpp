#include "opencv2/opencv.hpp"

using namespace cv;

int main(int argc, char* argv[]){
	VideoCapture cap("rtsp://admin:1@10.10.144.137:554/ISAPI/streaming/channels/102?auth=YWRtaW46MQ==");
	if(!cap.isOpened())
		return -1;

	Ptr<BackgroundSubtractor> pMOG2;
	Mat frame, fgMaskMOG2, eqFrame;
	namedWindow("testeBsOpenCV");
	namedWindow("foreground");

	pMOG2 = createBackgroundSubtractorMOG2();


	while(true){
		cap >> frame;
		cvtColor( frame, frame, CV_BGR2GRAY );
		equalizeHist( frame, eqFrame );
		pMOG2 -> apply(frame, fgMaskMOG2);
		imshow("testeBsOpenCV",frame);
		imshow("EqFrame",eqFrame );
		imshow("foreground", fgMaskMOG2);
		int k = waitKey(30)&0xFF;
		if(k==27 || k=='q')
			break;
	}
		
	
	return 0;
}
	