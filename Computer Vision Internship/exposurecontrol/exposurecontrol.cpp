#include "opencv2/opencv.hpp"
#include "Camera.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

int exposure= 0;
int expMax = 100;
int camId=0;
Camera cam(0);

void on_trackbar( int, void* )
{
	cam.setCameraProp("exposure_absolute",exposure);
}


int main(int argc, char** argv){
	//namedWindow("Frame",1);
	//createTrackbar("exposure_absolute", "Frame", &exposure, expMax, on_trackbar);
	int count = 0;
	Scalar meanBrightLevel[20];
	Scalar tempMean = 0;
	Mat frame;
	while(true){
		cam >> frame;
		meanBrightLevel[count] = mean(frame);
		count++;
		//imshow("Frame",frame);
		waitKey(30);
		if(count>=20){
			count = 0;
			for(int i = 0; i<20; i++)
				tempMean += meanBrightLevel[i];
			tempMean /= 20;
			ofstream myfile;
		    myfile.open ("meanbrightlevel.csv", ios::app);
		    myfile << tempMean[0] << "," << tempMean[1] << "," << tempMean[2] << std::endl;
		    myfile.close();
		    tempMean = 0;
		    exposure+=1;		
		    cout << exposure << endl;
		    cam.setCameraProp("exposure_absolute",exposure);
		}
		if(exposure > expMax)
			break;
	}

	return 0;
}