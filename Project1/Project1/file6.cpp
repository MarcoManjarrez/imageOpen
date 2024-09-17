#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

using namespace std;

void showImage(Mat image);

void histogram(int cols, int rows, Mat image);

int main() {
	int columns, rows;
	Mat image, image2, image3;
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
	
	
	/*
	createMask(columns, rows, image2, image);
	addImage(columns, rows, image, image2);
	constantImage(image);
	functionImage(image);
	substractImage(columns, rows, image, image2 );
	addImagePercentage(columns, rows, 60, 40, image, image2);
	imageNegative(columns, rows, image);
	*/
	histogram(columns, rows, image);
}

void showImage(Mat image) {
	namedWindow("Original", WINDOW_AUTOSIZE);
	imshow("Original", image);
	waitKey(0);
}

void histogram(int cols, int rows, Mat image) {
	int counter[256] = { 0 };
	int aux = 0;
	Mat addedImage(512, 512, CV_8U);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			counter[(int)image.at<uchar>(j, i)]++;
		}
	}

	for (int i = 0; i < 256; i++) {
		cout << "Pixeles con valor " << i << " es igual a " << counter[i] << endl;
	}

	for (int i = 0; i < 512; i++) {
		for (int j = 0; j < 512; j++) {
			addedImage.at<uchar>(j, i) = 0;
		}
	}

	for (int i = 0; i < 256; i++) {
		if (counter[i] > aux ) {
			aux = counter[i];
		}
	}

	for (int i = 0; i < 256; i++) {
			int height = counter[i] * 512 / aux;
			int width = 512 - height;
			rectangle(addedImage, Point(i*2, 512), Point(i*2+1, width), Scalar(255, 255, 255), FILLED, LINE_8, 0);
	}

	showImage(addedImage);

	waitKey(0);
}
