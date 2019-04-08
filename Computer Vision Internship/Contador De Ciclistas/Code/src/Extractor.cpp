#include "Extractor.hpp"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include <syslog.h>

int capture;
void sig_handler(int signo) {
	::capture = 1;
}

Extractor::Extractor(Factory &fct) {
    this->preprocessor = fct.createPreprocessor();
    this->detector = fct.createDetector();
    this->classifier = fct.createClassifier();
#ifdef DEBUG
    video = cv::VideoWriter("debug.avi", CV_FOURCC('M','J','P','G'),20,cv::Size(640,480),true);
#endif
    signal(SIGHUP, sig_handler);
}

Extractor::~Extractor() {
    delete this->preprocessor;
    delete this->detector;
    delete this->classifier;
}

void Extractor::Extract(cv::Mat &frame, Counters &cts) {

#ifdef DEBUG
    cv::Mat debugFrame = frame.clone();
#endif
    auto processedFrame = this->preprocessor->Preprocess(frame);
    auto dresult = this->detector->Detect(processedFrame);
    auto cresult = this->classifier->Classify(dresult);
    
    if (cresult->GetClassified().size() > 0) {
	static int i = 0;
	char name[20];
	sprintf(name, "img%03d.png", i++);
	//imwrite(name, frame);
    }
#ifdef DEBUG    
    for (auto el : dresult->GetObjects()) {
            el->Plot(frame);
    }
    this->classifier->PlotResults(debugFrame);
    imshow("Debug Frame", debugFrame);
    imshow("Frame", frame);
    video.write(debugFrame);
    for (auto el : cresult->GetClassified()) {
            printf("Element: %d detected\n", el->GetId());
    }
    
#endif
    if (::capture) {
	    openlog("EOC", 0, LOG_DAEMON);
	    syslog(LOG_INFO, "Frame captured");
	    closelog();
	    imwrite("out.png", frame);
	    ::capture = 0;
   }		

    *cresult >> cts;

    delete dresult;
    delete cresult;
}

