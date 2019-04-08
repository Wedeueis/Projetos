#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>



double compute_skew(const char* filename);
void deskew(const char* filename, double angle);

const char* files[] = { "images/m8.jpg", "images/m20.jpg", "images/p3.jpg", "images/p16.jpg", "images/p24.jpg"};
double skew_angles[] = { 0, 0, 0, 0, 0 };

int main()
{
	unsigned nb_files = sizeof(files) / sizeof(const char*);
	for (unsigned i = 0; i < nb_files; ++i)
		skew_angles[i] = compute_skew(files[i]);

	for (unsigned i = 0; i < nb_files; ++i)
		deskew(files[i], skew_angles[i]);
}



double compute_skew(const char* filename)
{
   // Load in grayscale.
   cv::Mat src = cv::imread(filename, 0);
   cv::Size size = src.size();
   cv::bitwise_not(src, src);
   std::vector<cv::Vec4i> lines;
   cv::HoughLinesP(src, lines, 1, CV_PI/180, 100, size.width / 2.f, 20);
      cv::Mat disp_lines(size, CV_8UC1, cv::Scalar(0, 0, 0));
    double angle = 0.;
    unsigned nb_lines = lines.size();
    for (unsigned i = 0; i < nb_lines; ++i)
    {
        cv::line(disp_lines, cv::Point(lines[i][0], lines[i][1]),
                 cv::Point(lines[i][2], lines[i][3]), cv::Scalar(255, 0 ,0));
        angle += atan2((double)lines[i][3] - lines[i][1],
                       (double)lines[i][2] - lines[i][0]);
    }
    angle /= nb_lines; // mean angle, in radians.
    double d_angle = angle * 180 / CV_PI;
 
    std::cout << "File " << filename << ": " << d_angle << std::endl;
 
    cv::imshow(filename, disp_lines);
    cv::waitKey(0);
    cv::destroyWindow(filename);
    return d_angle;
}

void deskew(const char* filename, double angle)
{
  cv::Mat img = cv::imread(filename, 0);
 
  cv::bitwise_not(img, img);
 
  std::vector<cv::Point> points;
  cv::Mat_<uchar>::iterator it = img.begin<uchar>();
  cv::Mat_<uchar>::iterator end = img.end<uchar>();
  for (; it != end; ++it)
    if (*it)
      points.push_back(it.pos());
 
  cv::RotatedRect box = cv::minAreaRect(cv::Mat(points));
  cv::Mat rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);
  cv::Mat rotated;
  cv::warpAffine(img, rotated, rot_mat, img.size(), cv::INTER_CUBIC);
  cv::Size box_size = box.size;
  if (box.angle < -45.)
    std::swap(box_size.width, box_size.height);
  cv::Mat cropped;
  cv::getRectSubPix(rotated, box_size, box.center, cropped);
  cv::imshow("Original", img);
  cv::imshow("Rotated", rotated);
  cv::imshow("Cropped", cropped);
  cv::waitKey(0);
}