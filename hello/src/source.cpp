#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;

void gradient(Mat& img, int step) {

}

int main()
{
  Mat image(Mat::zeros(300, 400, CV_8U));
  //Mat image(1500, 1500, CV_8U, Scalar(1));

  /// HELLO WORLD
  int fontFace(FONT_HERSHEY_PLAIN);
  double font_scale = 2.0;
  int thickness = 3;
  Point text_org(50, 50);
  putText(image, "Hello, world!", text_org, fontFace, font_scale, Scalar(255, 255, 255), thickness);
  imshow("Hello, world!", image);

  //int x1 = 0;
  //int y1 = 0;

  //int x2 = 0;
  //int y2 = 556;

  //int wid1 = 255 * 2;
  //int hei1 = 255 * 2;

  //int step = wid1 / 255;

  //cv::Rect roi(x1, y1, wid1, hei1);
  //cv::Mat roiMat = image(roi);

  //cv::Rect roi10(x2, y2, wid1, hei1);
  //cv::Mat roi10Mat = image(roi10);

  //int cols1 = 255 * 2;

  //for (int r = 0; r < cols1; r+=step) {
  //  roiMat.col(r).setTo(r);
  //  roi10Mat.col(r).setTo((r / 5) * 5);
  //}

  //namedWindow("Linear Gradient", CV_WINDOW_NORMAL);
  //imshow("Linear Gradient", image);
  waitKey(0);

}