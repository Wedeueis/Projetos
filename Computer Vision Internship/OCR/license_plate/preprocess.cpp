#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc,char* argv[]){
	Mat car, cpcar, sobel;
	stringstream ss;
	int opcao;
	if(argc>1)
		opcao = atoi(argv[1]);
	else
		opcao = 0;
	ss << "carro" << opcao << ".jpg"; 
	car = imread(ss.str());
	namedWindow("Car",1);
	namedWindow("Preprocessed Image",1);
	cpcar = car.clone();
	cvtColor(cpcar,cpcar, COLOR_BGR2GRAY, 0);
	GaussianBlur(cpcar, cpcar, Size(3, 3) ,0,0);
	Sobel(cpcar, sobel, -1, 1, 0);
	threshold(sobel,sobel,127,255,THRESH_BINARY);
  	morphologyEx( sobel, sobel, MORPH_CLOSE, getStructuringElement( MORPH_RECT,cv::Size( 15,15),Point( -1, -1 ) ));
	imshow("Preprocessed Image", sobel);
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
	findContours( sobel, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

	vector<RotatedRect> minRect( contours.size() );	

	for( int i = 0; i < contours.size(); i++ ){
		minRect[i] = minAreaRect( Mat(contours[i]) );
	}

	for( int i = 0; i< contours.size(); i++ ) {
		Point2f rect_points[4]; minRect[i].points( rect_points );
		float ratio = minRect[i].size.width/minRect[i].size.height;
		float area = minRect[i].size.width*minRect[i].size.height;
		// bool horizontal = false;
		// if( (minRect[i].angle>= -20 && minRect[i].angle <= 20) || (minRect[i].angle>= 160 && minRect[i].angle <= 200) )
		// 	horizontal  = true;
		for( int j = 0; j < 4; j++ ){
			if( ( (ratio > 0.2 && ratio < 0.8) || (ratio > 2 && ratio < 4) ) && area > 1000 && area < 10000){
				line( car, rect_points[j], rect_points[(j+1)%4], Scalar(0,255,0), 1, 8 );
			}
			else
				line( car, rect_points[j], rect_points[(j+1)%4], Scalar(0,0,255), 1, 8 );
		}
	}
	imshow("Car", car);

	waitKey();

}