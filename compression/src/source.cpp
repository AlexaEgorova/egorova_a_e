#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

Mat ReadSmallMat(const string& path) {
  Mat img = imread(path);
  if (img.empty())
    cout << "Cannot read img " << path << endl;
  resize(img, img, Size(300, img.rows * 300 / img.cols));
  return img;
}

string CompressImageToJpg(const Mat& src, const string& srcName, int compression) {
  std::vector<int> params;
  params.push_back(CV_IMWRITE_JPEG_QUALITY);
  params.push_back(compression);
  string name = srcName + to_string(compression) + ".jpg";
  imwrite(name, src, params);
  cout << "Saved " << name << endl;
  return name;
}

void GetBlue(const Mat& src, Mat dst) {
  Mat empty_image = Mat::zeros(src.rows, src.cols, CV_8UC1);
  Mat result(src.rows, src.cols, CV_8UC3);
  Mat in1[] = { empty_image, empty_image, dst };
}

int main() {
  Mat background(700, 1300, CV_8UC3, Scalar(0));

  string path = "flowers.png";
  Mat img, img95, img65;
  ReadSmallMat(path).copyTo(img);

  string name = CompressImageToJpg(img, "flowers", 95);
  ReadSmallMat(name).copyTo(img95);
  name = CompressImageToJpg(img, "flowers", 65);
  ReadSmallMat(name).copyTo(img65);

  vector<Mat> channels(3);
  int rowsNumber = 3;
  int columnsNumber = 3;
  int height = img.size[0];
  int width = img.size[1];

  Mat matsPerRow[] = { img, img95, img65 };
  for (int row = 0; row < rowsNumber; ++row) {
    split(matsPerRow[row], channels);
    Mat empty_image = Mat::zeros(channels[0].rows, channels[0].cols, CV_8UC1);
    Mat mv[3] = { empty_image, empty_image, empty_image };

    for (int column = 0; column < columnsNumber; ++column) {
      Mat result;
      mv[column] = channels[column];
      merge(mv, 3, result);

      if (row > 0) {
        Mat prevMat = background(Rect(column*width, 0, width, height));
        subtract(result, prevMat, result);
      }

      Mat matRoi = background(Rect(column*width, row*height, width, height));
      result.copyTo(matRoi);

      mv[column] = empty_image;
    }
  }

  for (int row = 0; row < rowsNumber; ++row) {
    Mat pic = matsPerRow[row];
    Mat grayPic;
    cvtColor(pic, grayPic, CV_RGB2GRAY);
    Mat mv[3] = { grayPic, grayPic, grayPic };
    merge(mv, 3, grayPic);


    if (row > 0) {
      Mat prevMat = background(Rect(columnsNumber*width, 0, width, height));
      subtract(grayPic, prevMat, grayPic);
    }

    Mat matRoi = background(Rect(columnsNumber*width, row*height, width, height));
    grayPic.copyTo(matRoi);
  }

  imshow("Compression&Channels", background);

  waitKey();
}

