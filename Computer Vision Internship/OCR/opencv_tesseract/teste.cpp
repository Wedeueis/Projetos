#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main(int argc ,char* argv[]) {
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout<<"Cannot open the cam!"<<endl;
		return 1;
	}
	
	namedWindow("Frame",1);

	Mat frame;
	while(true){
		cap >> frame;
		imshow("Frame",frame);
		int k = waitKey(30) & 0xFF;
		if(k  == 'q' || k== 27)
			break;
		else if(k == 'p')
			imwrite("frame.jpg",frame);
		else if(k == 'd'){
			if (system(NULL)) puts ("Ok");
			else exit (EXIT_FAILURE);
			std::string comand = "include/extract_text.py frame.jpg out_frame.jpg";
			std::string s = "python " + comand;
			system(s.c_str());
			s = "tesseract out_frame.jpg texto";
			system(s.c_str());
		}
	}
	return 0;
}

