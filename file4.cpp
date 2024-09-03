#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

using namespace std;

void showImage(Mat image);
void createMask(int cols, int rows, Mat image, Mat image2);


int main() {
	int columns, rows;
	Mat image, image2;
	image = imread("therealoppenheimer.jpg", IMREAD_GRAYSCALE);
	image2 = imread("flower.jpg", IMREAD_GRAYSCALE);

	if (image.cols < image2.cols) {
		columns = image.cols;
	}
	else {
		columns = image2.cols;
	}

	if (image.rows < image2.rows) {
		rows = image.rows;
	}
	else {
		rows = image2.rows;
	}
	
	showImage(image);
	createMask(columns, rows, image2, image);
	
}



void showImage(Mat image) {
	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);
	waitKey(0);
}

void createMask(int cols, int rows, Mat image, Mat image2) {
	Mat mask(rows, cols, CV_8U);
	Mat maskedImage(rows,cols, CV_8U);

	namedWindow("Mask", WINDOW_AUTOSIZE);
	namedWindow("Masked Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			if (image.at<uchar>(j, i) > 200) {
				mask.at<uchar>(j, i) = 255;
			}
			else {
				mask.at<uchar>(j, i) = 0;
			}
		}
	}

	imshow("Mask", mask);

	waitKey(0);

	
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			if (mask.at<uchar>(j, i) < 180) {
				maskedImage.at<uchar>(j, i) = image.at<uchar>(j,i);
			}
			else {
				maskedImage.at<uchar>(j, i) = image2.at<uchar>(j, i);
			}
		}
	}


	imshow("Masked Image", maskedImage);

	waitKey(0);
	//applyMask(image, newImage);
}

/*void applyMask(Mat image) {

	Mat newImage(image.rows, image.cols, CV_8U);

	namedWindow("Binary", WINDOW_AUTOSIZE);

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
}*/

