#include "Camera.hpp"

using namespace cv;
using namespace std;

int main(){
	Camera cam(0);
	cam.setExposureThreshold(128);
	
	while(true){
		Mat frame;
		cam >> frame;
		imshow("Frame",frame);
		int k = waitKey(1)&0xFF;
		if(k==27 || k=='q')
			break;
		else if(k=='f'){
			if(cam.showFps)
				cam.showFps = false;
			else
				cam.showFps = true;
		}
	}
	

}