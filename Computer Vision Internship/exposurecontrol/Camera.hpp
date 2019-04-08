#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock clk;

#define BRIGHT_LEVEL_ARRAY_SIZE 20

class Camera {
public:
    Camera(int id);
    Camera(std::string src);
    ~Camera();
    void operator>>(cv::Mat &frame);
	//Methods
	bool init(int id);
	bool init(std::string src);
	void varInit();
	bool isChanged();
	bool isRunning();
	int getFps();
	//Run() Pause() - To implement later
	void start();
	void stop();
	int getDeviceId();
	void setDeviceId(int value);
	int getWidth();
	void setWidth(int value);
	int getHeight();
	void setHeight(int value);
	int getExposureThreshold();
	void setExposureThreshold(int value);
	bool setCameraProp(std::string key, int value);
	//int getCameraProp(std::string key); - To implement later
	bool UpdateExposure();
	void drawFps();
	cv::Mat getNextFrame();

private:
	//Properties - current hardware configuration
	int deviceId;
	int width;
	int height;
	int brightness;
	int exposure;
	int contrast;
	int saturation;
	int hue;
	int gamma;
	int white_balance;

	//State - auxiliary control variables
	clk::time_point timeStampPrevFrame;
	clk::time_point timeStampCurrFrame;
	long timesDiff[5];
	long fps;
	int frameCounter;
	int expCounter;
	double meanbrightLevel;
	double brightLevel[BRIGHT_LEVEL_ARRAY_SIZE];
	int exposureThreshold;
	bool running;
	bool changed;
	//Objects - componentes
	cv::VideoCapture cap;
	cv::Mat frame;
	//thread Worker - To implement later
public:
	bool showFps;
};
#endif