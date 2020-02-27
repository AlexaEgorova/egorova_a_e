#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;

void PourWithGradient(Mat& img, int step)
{
  int color = 0;
  for (int i = 0; i + step < img.cols; i += step)
  {
    if (img.cols < 255) {
      img.col(i).setTo(i);
    }
    if (img.cols == 255) {
      for (int j = i; j < i + step; j++) {
        img.col(j).setTo(i);
      }
      int remainder = img.cols % step;
      for (int i = img.cols - remainder; i < img.cols; i++)
        img.col(i).setTo(255);
    }
    if (img.cols > 255) {
      int recounted_step = img.cols / 255;
      for (int j = i; j < i + step; j++) {
        img.col(j).setTo(color);
      }
    }
    color++;
  }
}

void CorrectGamma(Mat& img, double gamma, double A=1.0) {
  for (int i = 0; i < img.cols; i++) {
    auto color = img.at<unsigned char>(0, i);
    auto normColor = color / 255.0;
    auto newColor = 255.0 * pow(normColor, gamma) * A;
    img.col(i).setTo(newColor);
  }
}

int main()
{
  Mat image(800, 800, CV_8U, Scalar(50));

  int wid1 = 255;
  int hei1 = 255;

  int wid2 = 760;
  int hei2 = 60;

  cv::Rect roiSoftGradient(0, 0, wid1, hei1);
  cv::Mat matSoftGradient = image(roiSoftGradient);

  cv::Rect roiStepGradient(0, 300, wid1, hei1);
  cv::Mat matStepGradient = image(roiStepGradient);

  cv::Rect roiLongGradient(0, 600, wid2, hei2);
  cv::Mat matLongGradient = image(roiLongGradient);

  cv::Rect roiGamma(0, 705, wid2, hei2);
  cv::Mat matGamma = image(roiGamma);

  PourWithGradient(matSoftGradient, 1);
  PourWithGradient(matStepGradient, 20);
  PourWithGradient(matLongGradient, 3);
  PourWithGradient(matGamma, 3);

  CorrectGamma(matGamma, 2);

  namedWindow("Gradient", CV_WINDOW_NORMAL);
  imshow("Gradient", image);
  waitKey(0);

}

