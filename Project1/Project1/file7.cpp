#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void imageNegative(int cols, int rows, Mat image);


int main() {
    VideoCapture cap(0); // abre la cámara de default
  

    if (!cap.isOpened())  // revisa si se abrió correctamente
        return -1;
    while (true)
    {
        Mat frame, grayFrame;
        cap >> frame; // obtiene un nuevo cuadro de la cámara     
        cvtColor(frame, grayFrame, cv::COLOR_RGB2GRAY);
        imshow("frame", frame);
        imshow("Gray frame", grayFrame);
		imageNegative(grayFrame.cols, grayFrame.rows, grayFrame);
      
        imshow("Negative frame", grayFrame);

            if (waitKey(30) >= 0)
                break;     //rompe si el usuario oprime una tecla
    }
    return 0;
}

void imageNegative(int cols, int rows, Mat image) {
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			int pixelValue = (float)255 - image.at<uchar>(j, i);
			if (pixelValue < 0) {
				image.at<uchar>(j, i) = (uchar)0;
			}
			else {
				image.at<uchar>(j, i) = (uchar)pixelValue;
			}

		}
	}

}