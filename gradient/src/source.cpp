#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;

void PourWithGradient(Mat& img, int step, int color_step=1) {
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

void CorrectGammaByPixels(Mat& img, double gamma, double A=1.0) {
  for (int i = 0; i < img.cols; i++) {
    auto color = img.at<unsigned char>(0, i);
    auto normColor = color / 255.0;
    auto newColor = 255.0 * pow(normColor, gamma) * A;
    img.col(i).setTo(newColor);
  }
}

Mat CorrectGammaByMatrix(Mat& givenMat, double gamma, double A=1.0) {
  Mat convertedGivenMat;
  givenMat.convertTo(convertedGivenMat, CV_32F);
  convertedGivenMat /= 255.0;

  Mat poweredMat;
  pow(convertedGivenMat, gamma, poweredMat);
  poweredMat *= 255.0;

  return A*poweredMat;
}

int main() {
  Mat image(285, 778, CV_8U, Scalar(0));

  int wid = 768;
  int hei = 60;

  Rect roiLongGradient(5, 5, wid, hei);
  Mat matLongGradient = image(roiLongGradient);
  PourWithGradient(matLongGradient, 3);

  Rect roiGamma(5, 65, wid, hei);
  Mat matGamma = image(roiGamma);
  matLongGradient.copyTo(matGamma);
  CorrectGammaByMatrix(matGamma, 2).convertTo(matGamma, image.type());

  Rect roiStepGradient(5, 160, wid, hei);
  Mat matStepGradient = image(roiStepGradient);
  PourWithGradient(matStepGradient, 30, 10);
  for (int i = matStepGradient.cols-1; i > matStepGradient.cols-20; i--)
    matStepGradient.col(i).setTo(255);

  Rect roiStepGamma(5, 220, wid, hei);
  Mat matStepGamma = image(roiStepGamma);
  matStepGradient.copyTo(matStepGamma);
  for (int i = matStepGamma.cols - 1; i > matStepGamma.cols - 20; i--)
    matStepGamma.col(i).setTo(255);
  CorrectGammaByMatrix(matStepGamma, 2.4).convertTo(matStepGamma, image.type());

  namedWindow("Gradient", CV_WINDOW_NORMAL);
  imshow("Gradient", image);
  waitKey(0);
}

