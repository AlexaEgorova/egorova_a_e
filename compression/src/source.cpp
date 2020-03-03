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

Mat GetBlueChannel(const Mat& src, const Mat& channel) {

  Mat empty_image = Mat::zeros(src.rows, src.cols, CV_8UC1);
  Mat result(src.rows, src.cols, CV_8UC3);
  Mat in1[] = { channel, empty_image, empty_image };
  int from_to1[] = { 0,0, 1,1, 2,2 };
  mixChannels(in1, 3, &result, 1, from_to1, 3);
  return result;
}

Mat GetGreenChannel(const Mat& src, const Mat& channel) {
  Mat empty_image = Mat::zeros(src.rows, src.cols, CV_8UC1);
  Mat result(src.rows, src.cols, CV_8UC3);
  Mat in1[] = { empty_image, channel, empty_image };
  int from_to1[] = { 0,0, 1,1, 2,2 };
  mixChannels(in1, 3, &result, 1, from_to1, 3);
  return result;
}

Mat GetRedChannel(const Mat& src, const Mat& channel) {
  Mat empty_image = Mat::zeros(src.rows, src.cols, CV_8UC1);
  Mat result(src.rows, src.cols, CV_8UC3);
  Mat in1[] = { empty_image, empty_image, channel };
  int from_to1[] = { 0,0, 1,1, 2,2 };
  mixChannels(in1, 3, &result, 1, from_to1, 3);
  return result;
}

int main() {
  Mat background(500, 1000, CV_8U, Scalar(0));

  string path = "flowers.png";
  Mat img, img95, img65;
  ReadSmallMat(path).copyTo(img);

  string name = CompressImageToJpg(img, "flowers", 95);
  ReadSmallMat(name).copyTo(img95);
  name = CompressImageToJpg(img, "flowers", 65);
  ReadSmallMat(name).copyTo(img65);

  vector<Mat> channels(3);
  split(img, channels);

  Mat result;
  GetBlueChannel(img, channels[0]).copyTo(result);
  imshow("CompressionBlue", result);
  GetGreenChannel(img, channels[1]).copyTo(result);
  imshow("CompressionGreen", result);
  GetRedChannel(img, channels[2]).copyTo(result);
  imshow("CompressionRed", result);

  waitKey();
}

