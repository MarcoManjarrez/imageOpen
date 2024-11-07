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


int main() {
    Mat image;
    image = imread("pigs.jpg", IMREAD_GRAYSCALE);

    namedWindow("Original image", WINDOW_NORMAL);
    imshow("Original image", image);

    waitKey(0);

    //scaling(image.cols, image.rows, 2, 2, image);
    smoothScaling(image.cols, image.rows, 5, 8, image);
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
    uchar Q11 = 0, Q21 = 0, Q12 = 0, Q22 = 0, R1 = 0, R2 = 0, P = 0;
    cout << "cHorizontal: " << cHorizontal;
    cout << "cVertical: " << cVertical;

    for (int i = 0; i < cVertical; i++) {
        for (int j = 0; j < cHorizontal; j++) {
            float u = (i / scalingFactorY);
            float v = (j / scalingFactorX);
            Q11 = image.at<uchar>(floor(u), floor(v));
            Q21 = image.at<uchar>(ceil(u), floor(v));
            Q12 = image.at<uchar>(floor(u), ceil(v));
            Q22 = image.at<uchar>(ceil(u), ceil(v));

            if (floor(u) == u && floor(v) == v) {
                if (u >= 0 && u < cols && v >= 0 && v < rows)
                    scaledImage.at<uchar>(i, j) = image.at<uchar>(u, v);
            }
            else if (floor(u) == u && floor(v) != v) {
                R1 = Q11;
                R2 = Q12;
                P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - i) + R1;
                scaledImage.at<uchar>(i, j) = P;
            }
            else if (floor(u) != u && floor(v) == v) {
                R1 = Q11;
                R2 = Q21;
                P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - i) + R1;
                scaledImage.at<uchar>(i, j) = P;
            }
            else {
                R1 = ((float)(Q21 - Q11) / ((j + 1) - (j))) * (u - j) + Q11;
                R2 = ((float)(Q22 - Q12) / ((j + 1) - (j))) * (u - j) + Q12;
                P = ((float)(R2 - R1) / ((i + 1) - (i))) * (v - i) + R1;
                scaledImage.at<uchar>(i, j) = P;
            } 
        }
    }
    namedWindow("Horizontal Gradient", WINDOW_AUTOSIZE);
    imshow("Horizontal Gradient", scaledImage);

    waitKey(0);
}

