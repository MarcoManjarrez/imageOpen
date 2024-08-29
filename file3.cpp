#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

using namespace std;

void binaryFilter(Mat image);
void binaryInvFilter(Mat image);
void trunc(Mat image);
void toZero(Mat image);
void toZeroInv(Mat image);

int main() {
	Mat image;
	image = imread("thacoolest.png", IMREAD_GRAYSCALE);
	//Mat image(255, 255, CV_8U);

	/*for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			uchar value = (uchar)((i * 255) / image.cols);
			image.at<uchar>(j, i) = value;
		}
	}*/


	binaryFilter(image);
	binaryInvFilter(image);
	trunc(image);
	toZero(image);
	toZeroInv(image);
	



}



void binaryFilter(Mat image) {

	Mat newImage(image.rows, image.cols, CV_8U);

	namedWindow("Binary", WINDOW_NORMAL);

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

	imshow("Binary", newImage);

	waitKey(0);
}

void binaryInvFilter(Mat image) {

	Mat newImage(image.rows, image.cols, CV_8U);


	namedWindow("Binary inverted", WINDOW_NORMAL);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) > 128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = 255;
			}
		}
	}

	imshow("Binary inverted", newImage);
	waitKey(0);
}

void trunc(Mat image) {

	Mat newImage(image.rows, image.cols, CV_8U);


	namedWindow("Trunc", WINDOW_NORMAL);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) > 128) {
				newImage.at<uchar>(j, i) = 128;
			}
			else {
				newImage.at<uchar>(j, i) = image.at<uchar>(j,i);
			}
		}
	}

	imshow("Trunc", newImage);
	waitKey(0);
}

void toZero(Mat image) {

	Mat newImage(image.rows, image.cols, CV_8U);


	namedWindow("To zero", WINDOW_NORMAL);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) <=  128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = image.at<uchar>(j, i);
			}
		}
	}

	imshow("To zero", newImage);
	waitKey(0);
}

void toZeroInv(Mat image) {
	Mat newImage(image.rows, image.cols, CV_8U);


	namedWindow("To zero inverted", WINDOW_NORMAL);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) > 128) {
				newImage.at<uchar>(j, i) = 0;
			}
			else {
				newImage.at<uchar>(j, i) = image.at<uchar>(j, i);
			}
		}
	}

	imshow("To zero inverted", newImage);
	waitKey(0);
}

