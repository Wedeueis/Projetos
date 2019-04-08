#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
	int n = 20;
	Mat CAMERA_MAT=(Mat_<double>(3,3) << 2.4125343282050253e+03, 0., 3.5150000000000000e+02, 0. , 
						  2.4125343282050253e+03, 2.3950000000000000e+02, 0., 0., 1.);
	Mat DIST_COEF=(Mat_<double>(1,5) << -6.1258730846785614e+00, 1.7881388280983067e+01, 0., 0., 1.2840250181803588e+03);

	cout << CAMERA_MAT << endl;

	cout << DIST_COEF << endl;
		
	VideoCapture cap("rtsp://admin:1@10.10.144.137:554/ISAPI/streaming/channels/102?auth=YWRtaW46MQ==");
	if(!cap.isOpened()){
		return -1;
	}
	Mat frame, undistFrame, map1, map2;
	cout << map1.size() << " " << map2.size() << endl;
	namedWindow("Frame",1);
	namedWindow("Corrected",1);
	while(true){
		cap >> frame;
		initUndistortRectifyMap(CAMERA_MAT, DIST_COEF, cv::Mat(), CAMERA_MAT, frame.size(), CV_32FC1, map1, map2);
		remap(frame, undistFrame , map1, map2, INTER_CUBIC);	
		imshow("Frame",frame);
		imshow("Corrected", undistFrame);
		int k = waitKey(30) & 0xFF;
		if(k == 27 || k == 'q')
			break;
	}
	return 0;
}
