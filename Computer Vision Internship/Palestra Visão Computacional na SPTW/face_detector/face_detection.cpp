#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

int main(int argc, char** argv){
	VideoCapture cap(0);
	if(!cap.isOpened()){
		cout << "Não foi possível abrir a camera!" << endl;
		return -1;
	}
	Mat frame;
	namedWindow("Frame",1);

	CascadeClassifier face_cascade;
	face_cascade.load("/home/wedeueis/Documentos/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_alt2.xml");

	
	while(true){
		cap >> frame;
		vector<Rect> faces;
		face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	    for( int i = 0; i < faces.size(); i++ )
	    {
	        //Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
	        rectangle( frame, Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height*1.5 ), Scalar( 255, 0, 0 ), 4, 8, 0 );
	    }

	    imshow("Frame",frame);
	    int k = waitKey(30)&0xFF;
	    if(k==27 || k=='q')
	    	break;	

	}

 

}
