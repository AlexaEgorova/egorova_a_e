#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;

void gradient(Mat& img, int step) {
  for (int i=0; i + step < img.cols; i+=step) {

    int color_step = 255 / img.cols;

    if (img.cols < 255) {
      img.col(i).setTo(i);
    }

    if (img.cols == 255) {
      for (int j = i; j < i + step; j++) {
        img.col(j).setTo(i);
      }
    }

    if (img.cols > 255) {
      img.col(i).setTo(i);
    }
  }
  int remainder = img.cols % step;
  for (int i = img.cols - remainder; i < img.cols; i ++)
    img.col(i).setTo(255);
}

int main()
{
  Mat image(1500, 1500, CV_8U, Scalar(1));

  int x1 = 0;
  int y1 = 0;

  int x2 = 0;
  int y2 = 300;

  int wid1 = 255;
  int hei1 = 255;

  int step = wid1 / 255;

  cv::Rect roi(x1, y1, wid1, hei1);
  cv::Mat roiMat = image(roi);

  cv::Rect roi10(x2, y2, wid1, hei1);
  cv::Mat roi10Mat = image(roi10);

  int cols1 = 255 * 2;

  //for (int r = 0; r < cols1; r+=step) {
  //  roiMat.col(r).setTo(r);
  //  roi10Mat.col(r).setTo((r / 5) * 5);
  //}

  gradient(roiMat, 1);
  gradient(roi10Mat, 20);

  namedWindow("Linear Gradient", CV_WINDOW_NORMAL);
  imshow("Linear Gradient", image);
  waitKey(0);

}