#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

void gaussFilter(int cols, int rows, Mat image, int ratio);
void gaussFilter2(int cols, int rows, Mat image, int ratio, int sigma);
void showImage(Mat image);

int main() {
    Mat image;
    image = imread("pigs.jpg", IMREAD_GRAYSCALE);
    showImage(image);
    gaussFilter2(image.rows, image.cols, image, 5, 1);
}

void showImage(Mat image) {
    namedWindow("Original", WINDOW_AUTOSIZE);
    imshow("Original", image);
    waitKey(0);
}

void gaussFilter(int cols, int rows, Mat image, int ratio) {
    Mat mask;
    int divisionFactor, center;
    switch (ratio) {
    case 3:
        mask = (Mat_<float>(3, 3) << 1, 2, 1, 2, 4, 2, 1, 2, 1);
        divisionFactor = 16;
        center = 1;
    break;
    case 5:
        mask = (Mat_<float>(5, 5) << 1,4,7,4,1,4,16,26,16,4,7,26,41,26,7,4,16,26,16,4,1,4,7,4,1);
        divisionFactor = 273;
        center = 2;
    break;
    default:
        mask = (Mat_<float>(5, 5) << 2,4,5,4,2,4,9,12,9,4,5,12,15,12,5,4,9,12,9,4,2,4,5,4,2);
        divisionFactor = 159;
        center = 2;
    break;
    }

    for (int i = (int)ratio / 2; i < (int)cols - (ratio / 2); i++) {
        for (int j = (int)ratio / 2; j < (int)rows - (ratio / 2); j++) {
            int sum = 0;
            float prom = 0;
            for (int k = -(int)(ratio / 2); k <= (int)(ratio / 2); k++) {
                for (int l = -(int)(ratio / 2); l <= (int)(ratio / 2); l++) {
                    sum += (int)(image.at<uchar>(j + k, i + l) * mask.at<float>(center+l, center+k));
                }
            }
            prom = (float)sum / divisionFactor;
            image.at<uchar>(j, i) = (uchar)prom;
        }
    }
    namedWindow("Gaussian filter", WINDOW_AUTOSIZE);
    imshow("Gaussian filter", image);
    waitKey(0);
}

void gaussFilter2(int cols, int rows, Mat image, int ratio, int sigma) {
    int divisionFactor, center, x, y;
    x = (int)(ratio / 2);
    y = (int)(ratio / 2);
    
    Mat mask(ratio, ratio, CV_32F);

    for (int i = 0; i < mask.rows; i++) {
        for (int j = 0; j < mask.cols; j++) {
            int auxX = i - x;
            int auxY = y - j;
            float Texp = (float)((auxX * auxX + auxY * auxY) / (2 * sigma * sigma));
            float tconst = (float)(1 / (sigma * sigma * 2 * 3.141592));
            mask.at<float>(i, j) = tconst * exp(-Texp);
        }
    }

    for (int i = 0; i < mask.rows; i++) {
        for (int j = 0; j < mask.cols; j++) {
            cout << "Valor mask: " << mask.at<float>(i, j) << " en posición " << i << "," << j << endl;
        }
    }

    for (int i = (int)ratio / 2; i < (int)cols - (ratio / 2); i++) {
        for (int j = (int)ratio / 2; j < (int)rows - (ratio / 2); j++) {
            int sum = 0;
            float prom = 0;
            for (int k = -(int)(ratio / 2); k <= (int)(ratio / 2); k++) {
                for (int l = -(int)(ratio / 2); l <= (int)(ratio / 2); l++) {
                    sum += (int)(image.at<uchar>(j + k, i + l) * mask.at<float>(x + l, y + k));
                }
            }
            prom = (float)sum / 273;
            image.at<uchar>(j, i) = (uchar)prom;
        }
    }
    namedWindow("Gaussian filter", WINDOW_AUTOSIZE);
    imshow("Gaussian filter", image);
    waitKey(0);
}