#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

void scaling(int cols, int rows, int scalingFactorX, int scalingFactorY, Mat image);
void smoothScaling(int cols, int rows, float scalingFactorX, float scalingFactorY, Mat image);
void translation(int cols, int rows, int translationX, int translationY, Mat image);
void rotation(int cols, int rows, float angle, Mat image);
void matrixTranslation(int cols, int rows, int translationX, int translationY, Mat image);
void matrixRotation(int cols, int rows, int angle, Mat image);

int main() {
    Mat image;
    image = imread("pigs.jpg", IMREAD_GRAYSCALE);

    namedWindow("Original image", WINDOW_NORMAL);
    imshow("Original image", image);

    waitKey(10);

    //scaling(image.cols, image.rows, 2, 2, image);
    //smoothScaling(image.cols, image.rows, 2, 3, image);
    //translation(image.cols, image.rows, -50, 50, image);
    //rotation(image.cols, image.rows, 30, image);
    //matrixTranslation(image.cols, image.rows, -50, 50, image);
    matrixRotation(image.cols, image.rows, CV_PI/2, image);
}

void scaling(int cols, int rows, int scalingFactorX, int scalingFactorY, Mat image) {
    float cHorizontal = cols * scalingFactorX; //Tamaño de la nueva imagen en x
    float cVertical = rows * scalingFactorY; //Tamaño de la nueva imagen en y
    Mat scaledImage(cVertical, cHorizontal, CV_8U);
    cout << "cHorizontal: " << cHorizontal;
    cout << "cVertical: " << cVertical;

    for (int i = 0; i < cVertical; i++) {
        for (int j = 0; j < cHorizontal; j++) {
            int u = (int) (i / scalingFactorY);
            int v = (int) (j / scalingFactorX);
            
            if(u >= 0 && u < cVertical && v >= 0 && v < cHorizontal)
            scaledImage.at<uchar>(i, j) = image.at<uchar>(u, v);
        }
    }
    namedWindow("Horizontal Gradient", WINDOW_AUTOSIZE);
    imshow("Horizontal Gradient", scaledImage);

    waitKey(0);
}

void smoothScaling(int cols, int rows, float scalingFactorX, float scalingFactorY, Mat image) {
    float cHorizontal = cols * scalingFactorX; //Tamaño de la nueva imagen en x
    float cVertical = rows * scalingFactorY; //Tamaño de la nueva imagen en y
    Mat scaledImage(cVertical, cHorizontal, CV_8U);
    int Q11 = 0, Q21 = 0, Q12 = 0, Q22 = 0, R1 = 0, R2 = 0, P = 0;
    cout << "cHorizontal: " << cHorizontal;
    cout << "cVertical: " << cVertical;

    for (int i = 0; i < cVertical; i++) {
        for (int j = 0; j < cHorizontal; j++) {
           // cout << i << endl;
            float u = (i / scalingFactorY);
            float v = (j / scalingFactorX);
            if (ceil(u) >= 0 && ceil(u) < rows && floor(u) >= 0 && floor(u) < rows && ceil(v) >= 0 && ceil(v) < cols && floor(v) >= 0 && floor(v) < cols) {

                Q11 = image.at<uchar>(floor(u), floor(v));

                Q21 = image.at<uchar>(ceil(u), floor(v));
                Q12 = image.at<uchar>(floor(u), ceil(v));
                Q22 = image.at<uchar>(ceil(u), ceil(v));


                if (floor(u) == u && floor(v) == v) {
                    scaledImage.at<uchar>(i, j) = image.at<uchar>(u, v);
                }
                else if (floor(u) == u && floor(v) != v) {
                    R1 = Q11;
                    R2 = Q12;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    scaledImage.at<uchar>(i, j) = (uchar)P;
                }
                else if (floor(u) != u && floor(v) == v) {
                    R1 = Q11;
                    R2 = Q21;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    scaledImage.at<uchar>(i, j) = (uchar)P;
                }
                else {
                    R1 = ((float)(Q21 - Q11) / ((j + 1) - (j))) * (u - floor(u)) + Q11;
                    R2 = ((float)(Q22 - Q12) / ((j + 1) - (j))) * (u - floor(u)) + Q12;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    scaledImage.at<uchar>(i, j) = (uchar)P;
                }
            }
        }
    }
    namedWindow("Horizontal Gradient", WINDOW_AUTOSIZE);
    imshow("Horizontal Gradient", scaledImage);

    waitKey(0);
}

void translation(int cols, int rows, int translationX, int translationY, Mat image) {
    Mat translatedImage(rows, cols, CV_8U);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            int u = i - translationX;
            int v = j - translationY;
            if (u > 0 && u < cols && v > 0 && v < rows) {
                translatedImage.at<uchar>(j, i) = image.at<uchar>(v, u);
            }
            else {
                translatedImage.at<uchar>(j, i) = (uchar)0;
            }
        }
    }

    namedWindow("Translated image", WINDOW_AUTOSIZE);
    imshow("Translated image", translatedImage);

    waitKey(0);
}

void rotation(int cols, int rows, float angle, Mat image) {
    Mat rotatedImage(rows, cols, CV_8U);
    angle = (angle * 180) / CV_PI;
    int Q11 = 0, Q21 = 0, Q12 = 0, Q22 = 0, R1 = 0, R2 = 0, P = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            float x0 = i - (cols / 2);
            float y0 = (rows / 2) - j;
            float u0 = x0 * cos(angle) + y0 * sin(angle);
            float v0 = -x0 * sin(angle) + y0 * cos(angle);
            float u = u0 + cols / 2;
            float v = (rows / 2) - v0;
            if (ceil(u) >= 0 && ceil(u) < rows && floor(u) >= 0 && floor(u) < rows && ceil(v) >= 0 && ceil(v) < cols && floor(v) >= 0 && floor(v) < cols) {

                Q11 = image.at<uchar>(floor(u), floor(v));

                Q21 = image.at<uchar>(ceil(u), floor(v));
                Q12 = image.at<uchar>(floor(u), ceil(v));
                Q22 = image.at<uchar>(ceil(u), ceil(v));


                if (floor(u) == u && floor(v) == v) {
                    rotatedImage.at<uchar>(i, j) = image.at<uchar>(u, v);
                }
                else if (floor(u) == u && floor(v) != v) {
                    R1 = Q11;
                    R2 = Q12;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    rotatedImage.at<uchar>(i, j) = (uchar)P;
                }
                else if (floor(u) != u && floor(v) == v) {
                    R1 = Q11;
                    R2 = Q21;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    rotatedImage.at<uchar>(i, j) = (uchar)P;
                }
                else {
                    R1 = ((float)(Q21 - Q11) / ((j + 1) - (j))) * (u - floor(u)) + Q11;
                    R2 = ((float)(Q22 - Q12) / ((j + 1) - (j))) * (u - floor(u)) + Q12;
                    P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - floor(v)) + R1;
                    rotatedImage.at<uchar>(i, j) = (uchar)P;
                }
            }
        }
    }

    namedWindow("Rotated image", WINDOW_AUTOSIZE);
    imshow("Rotated image", rotatedImage);

    waitKey(0);
}


void matrixTranslation(int cols, int rows, int translationX, int translationY, Mat image) {
    Mat T = (Mat_<float>(3, 3) << 1, 0, translationX, 0, 1, translationY, 0, 0, 1);
    Mat v(3,1, CV_32F);
    Mat translatedImage(rows, cols, CV_8U);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            v.at<float>(0, 0) = i;
            v.at<float>(1, 0) = j;
            v.at<float>(2, 0) = 1;
            Mat res = T * v;
            float u = res.at<float>(0, 0);
            float v = res.at<float>(1, 0);
            if (u > 0 && u < cols && v > 0 && v < rows) {
                translatedImage.at<uchar>(j, i) = image.at<uchar>(v, u);
            }
            else {
                translatedImage.at<uchar>(j, i) = (uchar)0;
            }
        }
    }
    namedWindow("Translated image", WINDOW_AUTOSIZE);
    imshow("Translated image", translatedImage);

    waitKey(0);
}

void matrixRotation(int cols, int rows, int angle, Mat image) {
    Mat T1 = (Mat_<float>(3, 3) << cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1);
    Mat T2 = (Mat_<float>(3, 3) << 1, 0, (cols/2), 0, 1, (rows/2), 0, 0, 1);
    Mat T3 = (Mat_<float>(3, 3) << 1, 0, -(cols/2), 0, 1, -(rows/2), 0, 0, 1);
    Mat T;
    Mat v(3, 1, CV_32F);
    Mat rotatedImage(rows, cols, CV_8U);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            v.at<float>(0, 0) = i;
            v.at<float>(1, 0) = j;
            v.at<float>(2, 0) = 1;
            T = T2 * T1 * T3;
            Mat res = T * v;
            float u = res.at<float>(0, 0);
            float v = res.at<float>(1, 0);
            if (u > 0 && u < cols && v > 0 && v < rows) {
                rotatedImage.at<uchar>(j, i) = image.at<uchar>(v, u);
            }
            else {
                rotatedImage.at<uchar>(j, i) = (uchar)0;
            }
        }
    }
    namedWindow("Rotated image", WINDOW_AUTOSIZE);
    imshow("Rotated image", rotatedImage);

    waitKey(0);
}
