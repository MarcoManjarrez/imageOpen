#include <iostream>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

using namespace std;

int main() {
	Mat image;
	image = imread("THACOOLEST.png", IMREAD_GRAYSCALE);
	Mat image2(image.rows, image.cols, CV_8U);

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			if (image.at<uchar>(j, i) > 180) {
				image2.at<uchar>(j, i) = 255;
			}
			else {
				image2.at<uchar>(j, i) = 0;
			}
		}
	}

	namedWindow("Original image", WINDOW_NORMAL);
	namedWindow("Threshold filtered image", WINDOW_NORMAL);

	imshow("Original image", image);
	imshow("Threshold filtered image", image2);
	
	waitKey(0);
}
