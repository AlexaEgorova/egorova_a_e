#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

int main() {
  Mat background(400, 600, CV_8U, Scalar(0));

  int rowsNumber = 2;
  int columnsNumber = 3;
  int height = 200;
  int width = 200;

  int backsColors[] = { 0, 127, 255 };
  int circlesColors[] = { 0, 127, 255 };

  Rect rec = Rect(0, 0, width, height);
  rectangle(background, rec, Scalar(255), -1, 8, 0);
  circle(background, cv::Point(100, 100), 40, Scalar(0), -1);

  rec = Rect(width, 0, width, height);
  rectangle(background, rec, Scalar(0), -1, 8, 0);
  circle(background, cv::Point(300, 100), 40, Scalar(127), -1);

  rec = Rect(2*width, 0, width, height);
  rectangle(background, rec, Scalar(127), -1, 8, 0);
  circle(background, cv::Point(500, 100), 40, Scalar(255), -1);

  rec = Rect(0, height, width, height);
  rectangle(background, rec, Scalar(127), -1, 8, 0);
  circle(background, cv::Point(100, 300), 40, Scalar(255), -1);

  rec = Rect(width, height, width, height);
  rectangle(background, rec, Scalar(255), -1, 8, 0);
  circle(background, cv::Point(300, 300), 40, Scalar(0), -1);

  rec = Rect(2*width, height, width, height);
  rectangle(background, rec, Scalar(0), -1, 8, 0);
  circle(background, cv::Point(500, 300), 40, Scalar(127), -1);

  Mat filter1 = (Mat_<double>(2, 2) << 1, 0, 0, -1);

  Mat filter1Result;
  background.convertTo(filter1Result, CV_32F);
  filter2D(filter1Result, filter1Result, -1, filter1);

  filter1Result = (filter1Result + 255) / 2;
  filter1Result.convertTo(filter1Result, CV_8U);
  imshow("Filter1", filter1Result);

  Mat filter2 = (Mat_<double>(2, 2) << 0, 1, -1, 0);

  Mat filter2Result;
  background.convertTo(filter2Result, CV_32F);
  filter2D(filter2Result, filter2Result, -1, filter2);
  filter2Result = (filter2Result + 255) / 2;
  filter2Result.convertTo(filter2Result, CV_8U);
  imshow("Filter2", filter2Result);

  waitKey();
}

