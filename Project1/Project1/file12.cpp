#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <cmath>

using namespace cv;
using namespace std;

void scaling(int cols, int rows, int scalingFactorX, int scalingFactorY, Mat image);

int main() {
    Mat image;
    image = imread("pigs.jpg", IMREAD_GRAYSCALE);

    namedWindow("Original image", WINDOW_NORMAL);
    imshow("Original image", image);

    waitKey(0);

    scaling(image.cols, image.rows, 2, 2, image);

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
            //cout << "U: " << u <<endl;
            //cout << "V: " << v << endl;
            if(u >= 0 && u < cVertical && v >= 0 && v < cHorizontal)
            scaledImage.at<uchar>(i, j) = image.at<uchar>(u, v);
        }
    }
    namedWindow("Horizontal Gradient", WINDOW_AUTOSIZE);
    imshow("Horizontal Gradient", scaledImage);

    waitKey(0);
}
