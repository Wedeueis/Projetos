#include "bDetect.hpp"

//global variables

char state = 'd';
cv::Scalar mean_color(0,0,0);
double x_color = 0, y_color = 0;
int colorH = 10, colorS = 229, colorV = 255;
int supLimitH = 10, supLimitS = 30, supLimitV = 81, infLimitH = 10, infLimitS = 30, infLimitV = 81;
double resize = 0.5;
int selectedCorner = 0;
cv::Mat Gframe;
cv::Point2f fieldCorners[4];


void changeCameraProp(std::string key, std::string value, Json::Value root){
	if (system(NULL)) puts ("Ok");
  else exit (EXIT_FAILURE);
  std::string camera = root.get("camera", 1).asString();
  std::string s ="v4l2-ctl -d " + camera + "-c " + key + "=" + value;
  system(s.c_str());
}

void createTrackBars(){
	//create the trackbars
	cv::namedWindow("Control", 1);
	//cvCreateTrackbar("HUE", "TrackBar", &colorH, 255, on_trackbar);
	//cvCreateTrackbar("SATURATION", "TrackBar", &colorS, 255, on_trackbar);
	//cvCreateTrackbar("VALUE", "TrackBar", &colorV, 255, on_trackbar);
	cvCreateTrackbar("INFERIOR_LIMIT_H", "Control", &infLimitH, 128, on_trackbar);
	cvCreateTrackbar("SUPERIOR_LIMIT_H", "Control", &supLimitH, 128, on_trackbar);	
	cvCreateTrackbar("INFERIOR_LIMIT_S", "Control", &infLimitS, 128, on_trackbar);
	cvCreateTrackbar("SUPERIOR_LIMIT_S", "Control", &supLimitS, 128, on_trackbar);
	cvCreateTrackbar("INFERIOR_LIMIT_V", "Control", &infLimitV, 128, on_trackbar);
	cvCreateTrackbar("SUPERIOR_LIMIT_V", "Control", &supLimitV, 128, on_trackbar);
}

//Function to create a color mask and "cut" the ball in the source image
void colorDetection(cv::Mat src, cv::Mat &mask, cv::Scalar colors[], int it){
	cv::Mat hsv, tgt, thrs;
	//3-channel binary mask
	cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
	cv::GaussianBlur(hsv, hsv, cv::Size(3, 3),0,0);
	cv::inRange(hsv, cv::Scalar(colors[2][0] - infLimitH, colors[2][1] - infLimitS, colors[2][2] - infLimitV),
              cv::Scalar(colors[2][0]  + supLimitH + 1 , colors[2][1]  + supLimitS + 1, colors[2][2]  + supLimitV + 1), mask);
  //hsv.release();
	//image erosion
	cv::Mat element = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( 21,21 ),cv::Point( -1, -1 ) );
	cv::Mat element2 = cv::getStructuringElement( cv::MORPH_RECT,cv::Size( 11,11 ),cv::Point( -1, -1 ) );
	cv::morphologyEx( mask, mask, cv::MORPH_CLOSE, element);
	cv::morphologyEx( mask, mask, cv::MORPH_OPEN, element2);

	//mask aplication
	cv::Mat mask3[] = { mask,mask,mask };
	cv::merge(mask3, 3, thrs);
	cv::bitwise_and(thrs, src, tgt);

	//std::vector<cv::Mat> channels;
	//split(hsv, channels);
	cv::imshow("Bola", tgt);
	cv::imshow("HSV", hsv);

}

//Function to find the ball position in the screen
void findPos(cv::Mat &src,cv::Mat &tgt, std::vector<std::vector<cv::Point> > &contours,
              std::vector<cv::Vec4i> &hierarchy, Json::Value &root, float k){
	cv::Mat temp = src.clone();

	if( !temp.empty())
		cv::findContours(temp,contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
		//select best contour
		std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
		std::vector<cv::Point2f> center( contours.size() );
		std::vector<float> radius( contours.size() );

		int realBallRadius = root.get("ball_radius", 0).asInt();
    int bestBallRadiusDif = 0, final_radius, bestBall = 0, ball=0;
		cv::Point ball_center;
		double radiusDif;


		for( int i = 0; i < contours.size(); i++ ){
			//cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );//verificar se eh necessario
			cv::minEnclosingCircle( (cv::Mat)contours[i], center[i], radius[i] );
      radius[i] /= k;
			radiusDif = abs(realBallRadius - radius[i]);
			if(bestBall == 0 || radiusDif < bestBallRadiusDif){
        ball = 1;
				final_radius = (int)radius[i];
				ball_center.x = (int)center[i].x;
				ball_center.y = (int)center[i].y;
				bestBall = i;
				bestBallRadiusDif = radiusDif;
			}
		}

		if(ball != 0){
			cv::circle( tgt, center[bestBall], (int)(radius[bestBall]*k), cv::Scalar(255,0,0), 2, 8, 0 );
      root["ball_x"] = (int)(center[bestBall].x/k);
      root["ball_y"] = (int)(center[bestBall].y/k);
      saveInJson(root);
		}
}

//function to treat the events (mouse click) in the created windows


//function to create the matrix to change the perspective of the image
cv::Mat fieldCornersUpdated(cv::Point2f perspectiveIn[], cv::Size fieldSize){
  cv::Point2f perspectiveOut[] = { cv::Point2f(0.0, 0.0),
                                 cv::Point2f(fieldSize.width , 0.0),
                                 cv::Point2f(fieldSize.width, fieldSize.height),
                                 cv::Point2f( 0.0, fieldSize.height) };
  for(int i = 0; i < 4; i++){
    std::cout << perspectiveIn[i].x << " " << perspectiveIn[i].y << std::endl;
  }

  for(int i = 0; i < 4; i++){
    std::cout << perspectiveOut[i].x << " " << perspectiveOut[i].y << std::endl;
  }

  return cv::getPerspectiveTransform(perspectiveIn, perspectiveOut);
}

//function to choose the appropriate corner points to the field
void actionPickCorners(cv::VideoCapture &cap, Json::Value &root) {
  cv::namedWindow("pickCorners");
  cv::setMouseCallback("pickCorners", CallBackFunc);
  for(;;) {
        int k = cv::waitKey(30);
        if (k == 27 || k == 'q'){
          state = 'd';
          break;
        }else if(k == 's') {
          saveInJson(root);
        }else if(k >= 49 and k <= 52)  //Change the selected corner on press 1-4 key
          selectedCorner = k - 49;
        else if(k >= 73 and k <= 76) { //Move 1px when
          switch(k){
            case 73:
              fieldCorners[selectedCorner].y += -1;
              std::cout << fieldCorners[selectedCorner].y << std::endl;
              break;
            case 74:
              fieldCorners[selectedCorner].x += -1;
              break;
            case 75:
              fieldCorners[selectedCorner].y += 1;
              break;
            case 76:
              fieldCorners[selectedCorner].x += 1;
              break;
          }
        }

        cv::Mat frame;
        cap >> frame;

        //Resize Frame
        cv::resize(frame, frame, cv::Size((int)(frame.cols*resize),(int)(frame.rows*resize) ),
                                                 0, 0, cv::INTER_AREA);
        cv::resizeWindow("pickCorners", frame.cols, frame.rows);

        // Change status text
        std::stringstream ss;
        ss << (selectedCorner + 1);
        std::string status( "Pick corner " + ss.str() );
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);

        //Draw outline and highlight the selected corner
        for(int i = 0; i < 4; i++) {
          cv::Point2f cornerFrom( (int)(fieldCorners[i].x*resize),
                              (int)(fieldCorners[i].y*resize) );

          cv::Point2f cornerTo( (int)(fieldCorners[(i + 1) % 4].x*resize),
                            (int)(fieldCorners[(i + 1) % 4].y*resize) );

          cv::line(frame,
            cornerFrom,
            cornerTo,
            cv::Scalar(0, 0, 255), 1,
            cv::LINE_8, 0 );

          if (i == selectedCorner) {
            cv::circle(
              frame,
              cornerFrom,
              3, cv::Scalar(0, 255, 0), 1,
              cv::LINE_8, 0 );
          }

          cv::imshow("pickCorners", frame);
        }
  }

    cv::destroyWindow("pickCorners");

    for(int i = 0; i<4; i++){
      root["fieldCorners"][i][0] = fieldCorners[i].x;
      root["fieldCorners"][i][1] = fieldCorners[i].y;
    }

}

void actionConfigureColors(cv::VideoCapture &cap, Json::Value &root) {

  int selectedColor = 0;
  std::string Scolor = "blue";
  //Radius of measure Color mean
  int offset = 10;

  cv::namedWindow("pickColors");
  cv::setMouseCallback("pickColors", CallBackFunc);

  for(;;) {
    cv::Mat frame;
    cap >> frame;

    switch(selectedColor) {
      case 0: {
        Scolor = "blue";
        std::string status( "Pick color blue");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
      case 1: {
        Scolor = "green";
        std::string status( "Pick color green");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
      case 2:{
        Scolor = "orange";
        std::string status( "Pick color orange");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
      case 3: {
        Scolor = "purple";
        std::string status( "Pick color purple");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
      case 4: {
        Scolor = "red";
        std::string status( "Pick color red");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
      case 5:{
        Scolor = "yellow";
        std::string status( "Pick color yellow");
        cv::putText(frame, status, cv::Point(10,30), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                    cv::Scalar(255, 0, 0), 2, cv::LINE_8, false);
        break;
      }
    }

    //Get LAB Color of Mouse point
    std::stringstream ss1, ss2, ss3;
    int color_hsv_H = round(mean_color[0]);
    ss1 << color_hsv_H;
    int color_hsv_S = round(mean_color[1]);
    ss2 << color_hsv_S;
    int color_hsv_V = round(mean_color[2]);
    ss3 << color_hsv_V;
    std::string color_hsv("["+ ss1.str() +","+ ss2.str() +","+ ss3.str() +"]");

    cv::putText(frame, color_hsv, cv::Point(10,60), cv::FONT_HERSHEY_SIMPLEX, 0.8,
                cv::Scalar(55, 255, 55), 2, cv::LINE_8, false);

    cv::circle(frame,cv::Point(x_color,y_color),offset,cv::Scalar(255,255,0),1);

    cv::imshow("pickColors", frame);

    int k = cv::waitKey(30);
    if( k==27 || k == 'q') {
      state = 'd';
      break;
    }else if( k >= 49 && k <= 53) {
      selectedColor = k - 49;
    }else if(k == 's') {
      //função de gravar no json
      root["colors"][Scolor][0] = color_hsv_H;
      root["colors"][Scolor][1] = color_hsv_S;
      root["colors"][Scolor][2] = color_hsv_V;
      saveInJson(root);
    }
  }
  cv::destroyWindow("pickColors");

}

void saveInJson(Json::Value root) {
  std::ofstream configs;
  configs.open("../../../inc/configs.json");
  if(configs.is_open()) std::cout<< "saving cofiguration..." << std::endl;
  else std::cout<< "cannot open cofiguration file..." << std::endl;
  Json::StyledWriter styledWriter;
  configs << styledWriter.write(root);
  configs.close();
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata) {
    switch (state) {
      case 'c':
    		if (event == cv::EVENT_LBUTTONUP) {
    			//Get click x y position to a global variable
    			x_color = x;
    			y_color = y;
          int offset = 10;
    			int x1 = int(x - offset), x2 = int(x + offset);
    			int y1 = int(y - offset), y2 = int(y + offset);

    			//Check if it exeeds the boundaries
    			if(x1 < 0 or y1 < 0 or  x2 >= Gframe.cols or y2 >= Gframe.rows) {
           	std::cout << "!!! Exeecds boundaries" << std::endl;
    				return;
          }

    			//Get Region of Interest
    			cv::Rect roi(x1,y1,x2-x1, y2-y1);
          cv::Mat image_roi = Gframe(roi);
    			cv::cvtColor(image_roi,image_roi, cv::COLOR_BGR2HSV, 0);

          //create a round mask
          cv::Mat mask_pickcolor(offset*2,offset*2,CV_8UC1,cv::Scalar(1,1,1));
          cv::circle(mask_pickcolor,
                    //center
                    cv::Point(offset, offset),
                    //radius
                    offset,
                    cv::Scalar(255,255,255), -1, 8 , 0 );

    			//Blur Image
          cv::cvtColor(image_roi,image_roi,cv::COLOR_BGR2HSV);
          cv::GaussianBlur(image_roi, image_roi, cv::Size(3, 3),0,0);

			//Find Mean of colors (Excluding outer areas)
			mean_color = cv::mean(image_roi,mask_pickcolor);
        }
        break;
      case 'f':
         if  ( event == cv::EVENT_LBUTTONDOWN ) {
           fieldCorners[selectedCorner].x = (x / resize);
           fieldCorners[selectedCorner].y = (y / resize);
         }
        break;
    }
}

void on_trackbar(int) {}
