#include "opencv2/opencv.hpp"
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock clk;

using namespace cv;

int main(){

	for(int i=0; i<9; i++){
		std::stringstream fname;
		fname << "imagens/teste" << i << ".ppm";
		Mat image = imread(fname.str(),0);
		Mat labels = image.clone();
		clk::time_point t1 = clk::now();
		connectedComponents(image, labels, 4, CV_32S);
		clk::time_point t2 = clk::now();
		long time_diff = (long)duration_cast<milliseconds>( t2 - t1 ).count();
		std::cout << time_diff << " ";
	}
	std::cout<<std::endl;
	return 0;
}