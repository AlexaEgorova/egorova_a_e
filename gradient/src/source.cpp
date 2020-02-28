#include <opencv2\opencv.hpp>
#include <iostream>

void PourWithGradient(cv::Mat& img, int step, int color_step=1)
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
      if (step < recounted_step)
        step = recounted_step;
      for (int j = i; j < i + step; j++) {
        img.col(j).setTo(color);
      }
    }
    int remainder = img.cols % step;
    for (int i = img.cols - remainder-5; i < img.cols; i++)
      img.col(i).setTo(255);
    color += color_step;
  }
}

void CorrectGamma(cv::Mat& img, double gamma, double A=1.0) {
  for (int i = 0; i < img.cols; i++) {
    auto color = img.at<unsigned char>(0, i);
    auto normColor = color / 255.0;
    auto newColor = 255.0 * pow(normColor, gamma) * A;
    img.col(i).setTo(newColor);
  }
}

int main()
{
  cv::Mat image(800, 800, CV_8U, cv::Scalar(50));

  int wid = 768;
  int hei = 60;

  cv::Rect roiLongGradient(0, 0, wid, hei);
  cv::Mat matLongGradient = image(roiLongGradient);

  cv::Rect roiGamma(0, 105, wid, hei);
  cv::Mat matGamma = image(roiGamma);

  cv::Rect roiStepGradient(0, 310, wid, hei);
  cv::Mat matStepGradient = image(roiStepGradient);

  cv::Rect roiStepGamma(0, 415, wid, hei);
  cv::Mat matStepGamma = image(roiStepGamma);

  PourWithGradient(matLongGradient, 3);
  PourWithGradient(matGamma, 3);

  PourWithGradient(matStepGradient, 30, 10);
  for (int i = matStepGradient.cols-1; i > matStepGradient.cols-20; i--)
    matStepGradient.col(i).setTo(255);

  PourWithGradient(matStepGamma, 30, 10);
  for (int i = matStepGamma.cols - 1; i > matStepGamma.cols - 20; i--)
    matStepGamma.col(i).setTo(255);

  CorrectGamma(matGamma, 2);
  CorrectGamma(matStepGamma, 2);

  cv::namedWindow("Gradient", CV_WINDOW_NORMAL);
  imshow("Gradient", image);
  cv::waitKey(0);

}

