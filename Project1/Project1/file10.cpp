#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace cv;
using namespace std;

void erosion(Mat image);
void dilation(Mat image);
void growing(Mat image);

int main() {
	Mat image;
	image = imread("pigs.jpg", IMREAD_GRAYSCALE);
	//erosion(image);
	//dilation(image);
	growing(image);
}


void erosion(Mat image) {
	Mat crossMask(3,3,CV_8U);
	crossMask = (Mat_<uchar>(3, 3) << 0, 255, 0, 255, 255, 255, 0, 255, 0);
	Mat newImage(image.rows, image.cols, CV_8U);
	Mat erodedImage(image.rows, image.cols, CV_8U, Scalar(0));

	

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) < 128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = 255;
			}
		}
	}

	for (int x = 1; x < image.rows - 1; x++) {
		for (int y = 1; y < image.cols - 1; y++) {
			int cont = 0;
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					if (newImage.at<uchar>(x + l, y + k) == 255 && crossMask.at<uchar>(1 + k, 1 + l) == 255) cont++;
				}
			}
			if (cont == 5) erodedImage.at<uchar>(x, y) = 255;
		}
	}

	namedWindow("Binary", WINDOW_NORMAL);
	imshow("Binary", newImage);
	namedWindow("Eroded image", WINDOW_AUTOSIZE);
	imshow("Eroded image", erodedImage);

	waitKey(0);
}

void dilation(Mat image) {
	Mat crossMask(3, 3, CV_8U);
	crossMask = (Mat_<uchar>(3, 3) << 0, 255, 0, 255, 255, 255, 0, 255, 0);
	Mat newImage(image.rows, image.cols, CV_8U);
	Mat dilatedImage(image.rows, image.cols, CV_8U, Scalar(0));



	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) < 128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = 255;
			}
		}
	}

	for (int x = 1; x < image.rows - 1; x++) {
		for (int y = 1; y < image.cols - 1; y++) {
			int cont = 0;
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					if (newImage.at<uchar>(x + l, y + k) == 255 && crossMask.at<uchar>(1 + k, 1 + l) == 255) cont++;
				}
			}
			if (cont > 0) dilatedImage.at<uchar>(x, y) = 255;
		}
	}

	namedWindow("Binary", WINDOW_NORMAL);
	imshow("Binary", newImage);
	namedWindow("Dilated image", WINDOW_AUTOSIZE);
	imshow("Dilated image", dilatedImage);

	waitKey(0);
}

void growing(Mat image) {
	queue<Point> pixels;
	Mat newImage(image.rows, image.cols, CV_8U);
	Mat checkMatrix(image.rows, image.cols, CV_8U, Scalar(0));
	Point2d pt1;
	int cont = 100;
	


	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) < 128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = 255;
			}
		}
	}

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (newImage.at<uchar>(j, i) == 255) 
			{
			  if(checkMatrix.at<uchar>(j, i) == 0){
				checkMatrix.at<uchar>(j,i) = cont;
				for (int k = -1; k <= 1; k++) { //i
					for (int l = -1; l <= 1; l++) { //j
						if((j+l) >= 0 && (j + l) < image.rows && (i+k) >= 0 && (i + k) < image.cols){
						if (newImage.at<uchar>(j + l, i + k) == 255) pixels.push(Point(j+l, i+k));
						}
					}
				}
				while (!pixels.empty()) {
					pt1 = pixels.front();
					pixels.pop();
					if (newImage.at<uchar>(pt1.x, pt1.y) == 255 && checkMatrix.at<uchar>(pt1.x, pt1.y) == 0) {
						checkMatrix.at<uchar>(pt1.x, pt1.y) = cont;
						for (int k = -1; k <= 1; k++) { //i
							for (int l = -1; l <= 1; l++) { //j
								if ((pt1.x + l) >= 0 && (pt1.x + l) < image.rows && (pt1.y + k) >= 0 && (pt1.y + k) < image.cols) {
									if (newImage.at<uchar>(pt1.x + l, pt1.y + k) == 255 && checkMatrix.at<uchar>(pt1.x + l, pt1.y + k) == 0)
										pixels.push(Point(pt1.x + l, pt1.y + k));
								}
							}
						}
					}
				}
			  }
			}
			cont++;
		}
	}

	namedWindow("Binary", WINDOW_NORMAL);
	imshow("Binary", newImage);
	namedWindow("Regioned image", WINDOW_AUTOSIZE);
	imshow("Regioned image", checkMatrix);
	waitKey(0);
}
