#include <iostream>
#include <chrono>
#include <vector>
#include "opencv2/opencv.hpp"

#include "package_bgs/lb/LBMixtureOfGaussians.h"
#include "package_bgs/FrameDifferenceBGS.h"

using namespace std;
using namespace cv;
using namespace std::chrono;
typedef high_resolution_clock clk;

void ShowManyImages(string title, int nArgs, ...);

int main(int argc, char **argv) {
	VideoCapture cap("../peds/video.avi");
	if(!cap.isOpened()){
		cout << "Cannot open video file!" << endl;
		return -1;
	}
	
	IBGS *bgs = new LBMixtureOfGaussians();

	Mat frame, fgMaskMOG2;
	Ptr<BackgroundSubtractor> pMOG2;
	pMOG2 = createBackgroundSubtractorMOG2(500, 16,false);

    IBGS *fd = new FrameDifferenceBGS();

    int frame_count = 0;
	
	while(true){
		cap >> frame;
		frame_count++;

		if(frame.rows <= 0){
			break;
		}else if(frame_count > 170){
            break;
        }

		GaussianBlur(frame, frame, cv::Size(3, 3), 0);

		Mat mask, bkgmodel;
		bgs->process(frame, mask, bkgmodel);

        Mat mask2, bkgmodel2;
		fd->process(frame, mask2, bkgmodel2);

		Mat gray;
		cvtColor( frame, gray, CV_BGR2GRAY );
		pMOG2 -> apply(gray, fgMaskMOG2);

        cvtColor( fgMaskMOG2, fgMaskMOG2, CV_GRAY2BGR );
        cvtColor( mask2, mask2, CV_GRAY2BGR );

		ShowManyImages("Test", 4, frame, fgMaskMOG2, mask, mask2);

		int k = waitKey(80)&0xFF;
		if(k == 'q' || k == 27) {
			break;
		} else if(k =='p') {
			while(true){
				int k2 = waitKey(80)&0xFF;
				if(k2=='p'){
					break;
				}
			}
		} else if(k =='s') {
			std::cout << frame_count << std::endl;
			imwrite("../results/foreground_lbmog.jpg", mask);
            imwrite("../results/foreground_framediff.jpg", mask2);
            imwrite("../results/foreground_opencv.jpg", fgMaskMOG2);
			imwrite("../results/trackers.jpg", frame);
		}

	}

	return 0;
} 


void ShowManyImages(string title, int nArgs, ...) {
    int size;
    int i;
    int m, n;
    int x, y;

    int w, h;

    float scale;
    int max;

    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }else if(nArgs > 14) {
        printf("Number of arguments too large, can only handle maximally 12 images at a time ...\n");
        return;
    }else if (nArgs == 1) {
        w = h = 1;
        size = 300;
    }else if (nArgs == 2) {
        w = 2; h = 1;
        size = 300;
    }else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 300;
    }else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 200;
    }else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 200;
    }else {
        w = 4; h = 3;
        size = 150;
    }

    Mat DispImage = Mat::zeros(Size(100 + size*w, 60 + size*h), CV_8UC3);

    va_list args;
    va_start(args, nArgs);

    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
        Mat img = va_arg(args, Mat);

        if(img.empty()) {
            printf("Invalid arguments");
            return;
        }

        x = img.cols;
        y = img.rows;

        max = (x > y)? x: y;

        scale = (float) ( (float) max / size );

        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        Rect ROI(m, n, (int)( x/scale ), (int)( y/scale ));
        Mat temp; resize(img,temp, Size(ROI.width, ROI.height));
        temp.copyTo(DispImage(ROI));
    }

    namedWindow( title, 1 );
    imshow( title, DispImage);

    va_end(args);
}
