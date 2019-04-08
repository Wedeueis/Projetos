#include "Camera.hpp"


Camera::Camera(int id) {
	init(id);
	start();
}

Camera::Camera(std::string src) {
	init(src);
	start();
}

Camera::~Camera(){

}

bool Camera::init(int id) {
	this-> deviceId = id;
	this-> cap = cv::VideoCapture(deviceId);
	if(!this->cap.isOpened()) {
		std::cout << "ERROR: Can't open the camera!" << std::endl;
        return false;
	}
	varInit();
	return true;
}

void Camera::operator>>(cv::Mat &frame){
	frame = this->getNextFrame();
}

bool Camera::init(std::string src) {
	this-> deviceId = -1;
	this-> cap = cv::VideoCapture(src);
	if(!this->cap.isOpened()) {
		std::cout << "ERROR: Can't open the camera!" << std::endl;
        return false;
	}
	varInit();
	return true;
}

void Camera::varInit(){
	this-> frame = cv::Mat();
	this-> width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	this-> height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	this-> brightness = -1;
	setCameraProp(std::string("exposure_auto"), 1);
	this-> exposure = 1;
	this-> contrast = -1;
	this-> saturation = -1;
	this-> hue = -1;
	this-> gamma = -1;
	this-> white_balance = -1;
	this-> timeStampPrevFrame = clk::now();
	this-> timeStampCurrFrame = clk::now();
	this-> fps = 0;
	this-> showFps = false;
	this-> frameCounter = -5;
	this-> expCounter = 0;
	this-> meanbrightLevel = 0;
	for(int i=0;i<BRIGHT_LEVEL_ARRAY_SIZE;i++)
		this-> brightLevel[BRIGHT_LEVEL_ARRAY_SIZE] = 0;
	this-> exposureThreshold = 0;
	this-> running = true;
	this-> changed = true;
}

void Camera::start(){
	//to implement: code to wake up the thread and and put it to work
	if(running){
		getNextFrame();
	}else {
		init(this-> deviceId);
		running = true;
	}
}

void Camera::stop(){
	this->cap.release();
	running = false;
}


bool Camera::setCameraProp(std::string key, int value) {
	if ( system(NULL) ){
		int id = this->deviceId;
		std::stringstream ss;
		ss << "v4l2-ctl -d" << id << " -c " << key << "=" << value;
		//<< " 2>/dev/null";
		std::string comand(ss.str());
		system(comand.c_str());
		return true;
	}else
		return false;
}

//to do - isnt working, system don't return the value of the property
// int Camera::getCameraProp(std::string key) {
// 	if ( system(NULL) ){
// 		std::stringstream ss;
// 		ss << this->deviceId;
// 		std::string comand("v4l2-ctl -d" + ss.str() + " -C " + key);
// 		int value = system(comand.c_str() );
// 		return value;
// 	}else
// 		return -1;
// }

cv::Mat Camera::getNextFrame() {
	if(this->running){
		if(changed && this-> cap.isOpened()) {
			timeStampPrevFrame = timeStampCurrFrame;
			this->cap >> this->frame;
			if(showFps) drawFps();
			timeStampCurrFrame = clk::now();
			UpdateExposure();
			long timeDiff = (long)duration_cast<milliseconds>(
								timeStampCurrFrame - timeStampPrevFrame ).count();

			if(frameCounter < 0){
				fps = 2000/timeDiff;

				timesDiff[frameCounter+5] = timeDiff;
				frameCounter++;
				if(frameCounter+5>=4){
					long temp=0;
					for(int i=0;i<5;i++) temp += timesDiff[i];
					temp/=5;
					fps = 2000/temp;
				}	
			}else{
				timesDiff[frameCounter] = timeDiff;
				frameCounter++;
				if(frameCounter>=4){
					long temp=0;
					for(int i=0;i<5;i++) temp += timesDiff[i];
					temp/=5;
					fps = 2000/temp;
					frameCounter = 0;
				}	
			}
			
		}
		return this->frame;
	}else {
		std::cout << "ERROR: The camera isn't running." << std::endl;
		return cv:: Mat();
	}
}

bool Camera::UpdateExposure() {
	int expRange = 100;

	cv::Scalar temp = cv::mean(this->frame);

	if(temp[0]>temp[1]) {
		if(temp[0]>temp[2])
			this-> brightLevel[expCounter] = temp[0];
		else
			this-> brightLevel[expCounter] = temp[2];
	} else {
		if(temp[1]>temp[2])
			this-> brightLevel[expCounter] = temp[1];
		else
			this-> brightLevel[expCounter] = temp[2];
	}

	this->expCounter++;

	if(this->expCounter == 20) {
		this->meanbrightLevel = 0; 
		for(int i=0; i<20; i++){
			this->meanbrightLevel += this->brightLevel[i];
		}
		this->meanbrightLevel/=20;
		expCounter = 0;
	
		if(this->exposure < 5) {
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				std::cout << "teste" << std::endl;
				this->exposure = 1;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			} else if(this->meanbrightLevel-this->exposureThreshold < - expRange) {
				this->exposure = 5;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		} else if(this->exposure >= 5 && this->exposure < 10) {
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				this->exposure = 1;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}else if(this->meanbrightLevel-this->exposureThreshold < - expRange) {
				this->exposure = 10;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		} else if (this->exposure >= 10 && this->exposure < 20){
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				this->exposure = 5;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}else if(this->meanbrightLevel-this->exposureThreshold < - expRange) {
				this->exposure = 25;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		}else if (this->exposure >= 20 && this->exposure < 30){
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				this->exposure = 10;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}else if(this->meanbrightLevel-this->exposureThreshold < - expRange) {
				this->exposure = 50;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		}else if (this->exposure >= 30 && this->exposure < 60){
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				this->exposure = 20;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}else if(this->meanbrightLevel-this->exposureThreshold < - expRange) {
				this->exposure = 100;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		}else{
			if( this->meanbrightLevel-this->exposureThreshold > expRange ) {
				this->exposure = 30;
				setCameraProp(std::string("exposure_absolute"), this->exposure);
			}
		}
	}
}

bool Camera::isChanged() { return changed; }

bool Camera::isRunning() { return running; }

int Camera::getFps() { return fps; }

int Camera::getDeviceId() { return deviceId; }

void Camera::setDeviceId(int value) { this-> deviceId = value; }

int Camera::getWidth() { return width; }

void Camera::setWidth(int value) {
	this-> width = value;
	this->cap.set(CV_CAP_PROP_FRAME_WIDTH, width);
}

int Camera::getHeight() { return height; }

void Camera::setHeight(int value) {
	this-> height = value;
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, height);
}

int Camera::getExposureThreshold() { return exposureThreshold; }

void Camera::setExposureThreshold(int value) { 
	this-> exposureThreshold = value;
}

void Camera::drawFps() {
	std::stringstream ss;
	ss << "FPS: " << this->fps;
	cv::putText(this->frame, ss.str(), cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.7,
									cv::Scalar(0, 0, 0), 2, cv::LINE_8, false);
}