#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

void BuildHist(const Mat& src, Mat& dst, bool needSave=false) {
  int histSize = 256;
  float range[] = { 0, histSize };
  const float* histRange = { range };

  Mat hist;
  calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange);

  int histWidth = 512;
  int histHeight = 300;
  int step = cvRound((double)histWidth / histSize);

  Mat histMat(histHeight, histWidth, CV_8U, Scalar(255));
  normalize(hist, hist, 0, histMat.rows, NORM_MINMAX, -1, Mat());

  for (int i = 1; i < histSize; i++) {
    auto start = Point(step*(i - 1), histHeight - cvRound(hist.at<float>(i - 1)));
    auto rightEnd = Point(step*(i), histHeight - cvRound(hist.at<float>(i)));
    auto bottomEnd = Point(step*(i - 1), histHeight);
    line(histMat, start, rightEnd, Scalar(0));
    line(histMat, start, bottomEnd, Scalar(0), step);
  }
  if (needSave)
    imwrite("hist.png", histMat);
  histMat.copyTo(dst);
}

void ShowGraph(const double& alpha, const int& beta) {
  Mat funcMat(512, 512, CV_8UC1, Scalar(200));
  for (int i = 1; i < 256; i++) {
    auto start = Point(i-1, alpha*(i - 1) + beta);
    auto end = Point(i, alpha*i + beta);
    line(funcMat, start, end, Scalar(0), 2);
    cout << start << "  " << end << endl;
  }
  imshow("Function", funcMat);

}

void CorrectImg(const Mat& src, Mat& dst) {
  srand(time(NULL));
  // 1.0-3.0 & 0 - 100
  double alpha = double(rand() % 20 + 10) / 10;
  int beta = (rand() % 100 + 1) * pow(-1, rand());
  ShowGraph(alpha, beta);

  cout << alpha << "  " << beta << endl;

  Mat correctedImg;
  src.copyTo(correctedImg);
  correctedImg.convertTo(correctedImg, CV_32F);
  correctedImg *= alpha;
  correctedImg += beta;
  correctedImg.convertTo(correctedImg, CV_8U);

  correctedImg.copyTo(dst);
}

int main(int argc, char** argv) {
  Mat background(700, 1300, CV_8UC1, Scalar(60));

  Mat src = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
  if (!src.data) {
    cout << "Error reading " << argv[1] << endl;
    waitKey(0);
    return -1;
  }
  resize(src, src, Size(450, src.rows * 450 / src.cols));
  Mat matRoi = background(Rect(0, 0, src.cols, src.rows));
  src.copyTo(matRoi);

  Mat srcHist;
  BuildHist(src, srcHist, true);
  matRoi = background(Rect(src.cols,
    (src.rows-srcHist.rows)/2,
    srcHist.cols,
    srcHist.rows));
  srcHist.copyTo(matRoi);

  Mat correctedImg;
  CorrectImg(src, correctedImg);
  matRoi = background(Rect(0, src.rows + 2, src.cols, src.rows));
  correctedImg.copyTo(matRoi);

  Mat correctedHist;
  BuildHist(correctedImg, correctedHist);
  matRoi = background(Rect(correctedImg.cols,
    src.rows + (correctedImg.rows + 2 - correctedHist.rows) / 2,
    correctedHist.cols,
    correctedHist.rows));
  correctedHist.copyTo(matRoi);

  imshow("Change Func", background);

  waitKey(0);
  return 0;

}

