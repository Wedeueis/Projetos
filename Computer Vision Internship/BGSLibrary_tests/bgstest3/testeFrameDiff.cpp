#include "FrameDifferenceBGS.h"

using namespace cv;
using namespace std;

int main(){
	VideoCapture cap(0);
	if(!cap.isOpened()){
		return -1;
	}

	IBGS *bg = new FrameDifferenceBGS();
	Mat frame, foreground, background;
	namedWindow("Teste Frame Difference");
	namedWindow("Foreground");
	namedWindow("Background");

	while(true){
		cap >> frame;
		bg->process(frame, foreground, background);

		if( (frame.rows > 0)  && !(frame.empty() ) )
			imshow("Frame", frame);
		if( (foreground.rows > 0)  && !(foreground.empty()) )
			imshow("Foreground", foreground);
		if( (background.rows > 0)  && !(background.empty()) )
			imshow("Background", background);
		int k = waitKey(30)&0xFF;
		if(k == 27 || k=='q')
			break;
	}


}