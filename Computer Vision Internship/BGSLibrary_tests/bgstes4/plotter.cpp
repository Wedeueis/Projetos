#include "plotter.hpp"


cv::Mat showManyImages(const char* title, std::vector<cv::Mat> images, int photoSize){
	int N = images.size();
	
	int size;
	int i;
	int m, n;
	int x, y;
	
	// w - Maximum number of images in a row
	// h - Maximum number of images in a column 
	int w, h;
	
	 // scale - How much we have to resize the image
	float scale;
	int max;
	// Determine the size of the image,
	// and the number of rows/cols
	// from number of arguments

	if(photoSize<200)
		photoSize = 200;
	else if(photoSize>400)
		photoSize = 400;

	if(N <= 0){
		std::cout << "Nothing to show!" << std::endl;
		return cv::Mat();
	}
	else if(N >= 13){
		std::cout << "Too much images!" << std::endl;
		return cv::Mat();
	}
	else if(N == 1){
		w = h = 1;
		size = photoSize;
	}
	else if(N == 2){
		w = 2; h = 1;
		size = photoSize;
	}
	else if(N == 3 || N == 4){
		w = 2; h = 2;
		size = photoSize;
	}
	else if(N == 5 || N == 6){
		w = 3; h = 2;
		size = photoSize -50;
	}
	else if(N == 7 || N == 8){
		w = 4; h = 2;
		size =photoSize-50;
	}
	else {
		w = 4; h = 3;
		size = photoSize-100;
	}

	//the image in which input images are to be copied
	cv::Mat display(80 + size*h, 100 + size*w, CV_8UC3, cv::Scalar(0,0,0));
	std::cout << display.rows << " " << display.cols << std::endl;
	
	// Loop for N number of images
	for (i = 0, m = 20, n = 20; i < N; i++, m += (20 + size)) {
		// img - Used for getting the arguments		
		cv::Mat img = images[i];
		
		if( !(img.rows>0) ) {
			std::cout << "Invalid null input image!" << std::endl;
			cv::Mat error;
			return error;
		}
	
		// Find the width and height of the image
		x = img.cols;
		y = img.rows;
	
		// Find whether height or width is greater in order to resize the image
		max = (x > y)? x: y;
	
		// Find the scaling factor to resize the image
		scale = (float) ( (float) max / size );

		// Used to Align the images
		if( i % w == 0 && m!= 20) {
			m = 20;
			n+= 20 + size;
		}

		// Set the image ROI to display the current image
		cv::Mat roi = display(cv::Rect(m, n, (int)( x/scale ), (int)( y/scale )));
	
		// Resize the input image and copy the it to the Single Big Image
		cv::resize(img, roi, roi.size(), 0, 0, CV_INTER_AREA);

	}
	// Return the big image
	return display;
}
