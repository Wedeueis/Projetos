#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int main(int argc, char** argv){
	VideoCapture cap("video0.avi");
	if(!cap.isOpened()){
		cout << "Cannot open the camera!" << endl;
		return -1;
	}

	Mat frame;
	while(true){
		cap >> frame;
		if(frame.rows > 0){
			cout << "processing" << endl;
			Scalar mean = cv::mean(frame);
			ofstream myfile;
		    myfile.open ("meanbrightlevel.csv", ios::app);
		    myfile << mean[0] << "," << mean[1] << "," << mean[2] << std::endl;
		    myfile.close();
		}else{
			cout << "stoped" << endl;
			break;
		}

	}	

}