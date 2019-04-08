#include "Factory.hpp"  
#include "Extractor.hpp"
#include "Persistence.hpp"
#include "Config.hpp"
#include "Counters.hpp"
#include "ClassificationResult.hpp"
#include "Camera.hpp"

#include <opencv2/opencv.hpp>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std::chrono;
typedef high_resolution_clock clk;

void EOC() {
    Conf cfg;
    cfg.load();
    
    int processorId = 0;
    Factory factory(processorId, cfg);  
    Extractor extractor(factory);

    Camera cam(0);
    cv::Mat frame;
    Counters cnt;

#ifdef DEBUG  
    vector<cv::Scalar> time(100);
    int index=0;
    cv::Scalar partialTimes;
#endif

    while(true) {

#ifdef DEBUG  	
    	clk::time_point t1 = clk::now();
#endif
        cam >> frame;
        flip(frame, frame, 0);
    	extractor.Extract(frame, cnt);

#ifdef DEBUG 
    	clk::time_point t2 = clk::now();
    	partialTimes[0] = (long)duration_cast<milliseconds>( t2 - t1 ).count();
    	time[index] = partialTimes;
    	index++;
    	if(index>=100) index = 0;
#endif

    	int k = cv::waitKey(30) & 0xFF;
    	if(k==27 || k=='q')
    		break;

    }

#ifdef DEBUG
    cv::Scalar sum(0,0,0) ,mean;
    for(int i = 0; i<100; i++)
		sum+=time[i];
    
    mean[0] = sum[0]/100;

    ofstream myfile;
    myfile.open ("times.csv", ios::app);
    myfile << mean[0] << std::endl;
    myfile.close();
#endif

}

int main() {    
    EOC();
}
