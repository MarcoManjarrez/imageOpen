#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

using namespace std;

void showImage(Mat image);
void createMask(int cols, int rows, Mat image, Mat image2);
void addImage(int cols, int rows, Mat image, Mat image2);
void constantImage(Mat image);
void functionImage(Mat image);
void addImagePercentage(int cols, int rows, int percentage, int percentage2,  Mat image, Mat image2);
void substractImage(int cols,int rows, Mat image, Mat image2);
void imageNegative(int cols, int rows, Mat image);
void histogram(int cols, int rows, Mat image);

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
	showImage(image2);
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
}

void addImage(int cols, int rows, Mat image, Mat image2) {
	Mat addedImage(rows, cols, CV_8U);

	namedWindow("Added Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			addedImage.at<uchar>(j, i) = (uchar)((image.at<uchar>(j, i) + image2.at<uchar>(j, i)) / 2);
		}
	}

	imshow("Added Image", addedImage);

	waitKey(0);

}

void constantImage(Mat image) {
	Mat constantImage(image.rows, image.cols, CV_8U);

	namedWindow("Constant added Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < constantImage.cols; i++) {
		for (int j = 0; j < constantImage.rows; j++) {
			int addedValue = (image.at<uchar>(j, i) + 40);
			if (addedValue < 255) {
				constantImage.at<uchar>(j, i) = (uchar)addedValue;
			}
			else {
				constantImage.at<uchar>(j, i) = (uchar)255;
			}
		}
	}
	imshow("Constant added Image", constantImage);

	waitKey(0);
}

void functionImage(Mat image) {
	Mat functionImage(image.rows, image.cols, CV_8U);

	namedWindow("Function Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < functionImage.cols; i++) {
		for (int j = 0; j < functionImage.rows; j++) {
			int factor = (((float)i / functionImage.cols) * 255) + image.at<uchar>(j, i);
			if (factor < 255) {
				functionImage.at<uchar>(j, i) = factor;
			}
			else {
				functionImage.at<uchar>(j, i) = 255;
			}
		}
	}

	imshow("Function Image", functionImage);

	waitKey(0);
}

void addImagePercentage(int cols, int rows, int percentage, int percentage2, Mat image, Mat image2) {
	Mat addedImage(rows, cols, CV_8U);

	namedWindow("Added Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			int pixelValue = (float)i /percentage * (image.at<uchar>(j, i)  + (float)j / percentage2 *  image2.at<uchar>(j, i));
			if (pixelValue < 255) {
				addedImage.at<uchar>(j, i) = (uchar)pixelValue;
			}
			else {
				addedImage.at<uchar>(j, i) = (uchar)255;
			}
			
		}
	}

	imshow("Added Image", addedImage);

	waitKey(0);

}

void substractImage(int cols, int rows, Mat image, Mat image2) {
	Mat addedImage(rows, cols, CV_8U);

	namedWindow("Substracted Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			int pixelValue = (float)image.at<uchar>(j, i) - image2.at<uchar>(j, i);
			if(pixelValue < 0) {
				addedImage.at<uchar>(j, i) = (uchar)0;
			}
			else {
				addedImage.at<uchar>(j, i) = (uchar)pixelValue;
			}

		}
	}

	imshow("Substracted Image", addedImage);

	waitKey(0);
}

void imageNegative(int cols, int rows, Mat image) {
	Mat addedImage(rows, cols, CV_8U);

	namedWindow("Negative Image", WINDOW_AUTOSIZE);

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			int pixelValue = (float) 255 - image.at<uchar>(j, i);
			if (pixelValue < 0) {
				addedImage.at<uchar>(j, i) = (uchar)0;
			}
			else {
				addedImage.at<uchar>(j, i) = (uchar)pixelValue;
			}

		}
	}

	imshow("Negative Image", addedImage);

	waitKey(0);
}

void histogram(int cols, int rows, Mat image) {
	int counter[256] = { 0 };
	Mat addedImage(rows, cols, CV_8U);


	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			counter[(int)image.at<uchar>(j, i)]++;
		}
	}

	for (int i = 0; i < 256; i++) {
		cout << "Pixeles con valor " << i << " es igual a " << counter[i] << endl;
	}

	waitKey(0);
}
