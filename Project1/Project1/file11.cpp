#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

void gradientFilter(int cols, int rows, Mat image);
void laplacian(int cols, int rows, Mat image);

int main() {
    Mat image;
    image = imread("pigs.jpg", IMREAD_GRAYSCALE);
    //gradientFilter(image.cols, image.rows, image);
    laplacian(image.cols, image.rows, image);
}

void gradientFilter(int cols, int rows, Mat image) {
    Mat maskHorizontal(3, 3, CV_8U), maskVertical(3, 3, CV_8U);
    Mat horizontalGradientImage(rows, cols, CV_32F);
    Mat verticalGradientImage(rows, cols, CV_32F);
    Mat horizontalGradientImageUchar(rows, cols, CV_8U);
    Mat verticalGradientImageUchar(rows, cols, CV_8U);

    maskHorizontal = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    maskVertical = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    for (int i = 1; i < cols - 1; i++) {
        for (int j = 1; j < rows - 1; j++) {
            float sum1 = 0, sum2 = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum1 = sum1 + (image.at<uchar>(j + l, i + k) * maskHorizontal.at<float>(1 + l, 1 + k));
                    sum2 = sum2 + (image.at<uchar>(j + l, i + k) * maskVertical.at<float>(1 + l, 1 + k));
                }
            }
            horizontalGradientImage.at<float>(j, i) = (float)sum1;
            verticalGradientImage.at<float>(j, i) = (float)sum2;
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            horizontalGradientImageUchar.at<uchar>(j, i) = (uchar)fabs(horizontalGradientImage.at<float>(j, i));
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            verticalGradientImageUchar.at<uchar>(j, i) = fabs(verticalGradientImage.at<float>(j, i));
        }
    }


    namedWindow("Horizontal Gradient", WINDOW_NORMAL);
    imshow("Horizontal Gradient", horizontalGradientImageUchar);
    namedWindow("Vertical Gradient", WINDOW_AUTOSIZE);
    imshow("Vertical Gradient", verticalGradientImageUchar);
    
    waitKey(0);
}

void laplacian(int cols, int rows, Mat image) {
    Mat laplacianMask(3, 3, CV_8U), maskVertical(3, 3, CV_8U);
    Mat laplacianGradientImage(rows, cols, CV_32F);
    Mat laplacianGradientImageUchar(rows, cols, CV_8U);

    laplacianMask = (Mat_<float>(3, 3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);


    for (int i = 1; i < cols - 1; i++) {
        for (int j = 1; j < rows - 1; j++) {
            float sum = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum = sum + (image.at<uchar>(j + l, i + k) * laplacianMask.at<float>(1 + l, 1 + k));
         
                }
            }
            laplacianGradientImage.at<float>(j, i) = (float)sum;
   
        }
    }

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            laplacianGradientImageUchar.at<uchar>(j, i) = (uchar)fabs(laplacianGradientImage.at<float>(j, i));
        }
    }

    namedWindow("Laplacian Gradient", WINDOW_NORMAL);
    imshow("Laplacian Gradient",laplacianGradientImageUchar);

    waitKey(0);
}
