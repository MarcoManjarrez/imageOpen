#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <algorithm>

using namespace cv;
using namespace std;

void meanMask(int cols, int rows, Mat image, int ratio);
void medianMask(int cols, int rows, Mat image, int ratio);
void showImage(Mat image);


int main() {
    Mat image;
    image = imread("stupidNoisyGuy.jpg", IMREAD_GRAYSCALE);
    showImage(image);
    //meanMask(image.cols, image.rows, image, 21);
    medianMask(image.cols, image.rows, image, 3);
}

void showImage(Mat image) {
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);
    waitKey(0);
}

void meanMask(int cols, int rows, Mat image, int ratio) {
    for (int i = (int)ratio/2; i < (int)cols-(ratio/2); i++) {
        for (int j =(int)ratio/2; j < (int)rows-(ratio/2); j++) {
            int sum = 0;
            float prom = 0;
            for (int k = -(int)(ratio/2); k <= (int)(ratio/2); k++) {
                for (int l = -(int)(ratio/2); l <= (int)(ratio/2); l++) {
                    sum += image.at<uchar>(j + k, i + l);
                }
            }
            prom = (float) sum / (ratio*ratio);
            image.at<uchar>(j, i) = (uchar)prom;
        }
    }
    namedWindow("Mean filter", WINDOW_AUTOSIZE);
    imshow("Mean filter", image);
    waitKey(0);
}

void medianMask(int cols, int rows, Mat image, int ratio) {
    int valueArray[9] = { 0 };
    vector<int> vectorized(valueArray, valueArray + 9);
    for (int i = (int)ratio / 2; i < (int)cols - (ratio / 2); i++) {
        for (int j = (int)ratio / 2; j < (int)rows - (ratio / 2); j++) {
            int pos = 0;
            for (int k = -(int)(ratio / 2); k <= (int)(ratio / 2); k++) {
                for (int l = -(int)(ratio / 2); l <= (int)(ratio / 2); l++) {
                    vectorized[pos] = image.at<uchar>(j + k, i + l);
                    pos++;
                }
            }
            sort(vectorized.begin(), vectorized.end());
            image.at<uchar>(j, i) = vectorized[4];
        }
    }
    namedWindow("Median filter", WINDOW_AUTOSIZE);
    imshow("Median filter", image);
    waitKey(0);
}