#include <opencv2/core/core.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

using namespace std;

int main()

{

    Mat image, image2, image3;

    image = imread("THACOOLEST.png", IMREAD_GRAYSCALE);
    image2 = imread("anegg.jpg", IMREAD_COLOR);
    image3 = imread("pigs.jpg", IMREAD_COLOR);// Read the file

    if (!image.data || !image2.data || !image3.data)                              // Check for invalid input

    {

        cout << "Could not open or find the image" << std::endl;

        return -1;

    }

    namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
    namedWindow("Display window 2", WINDOW_NORMAL);
    namedWindow("Display window 3", WINDOW_AUTOSIZE);
    
    imshow("Display window", image);   
    imshow("Display window 2", image2); 
    imshow("Display window 3", image3); // Show our image inside it.

    waitKey(0);                                          // Wait for a keystroke in the window

    return 0;

}

