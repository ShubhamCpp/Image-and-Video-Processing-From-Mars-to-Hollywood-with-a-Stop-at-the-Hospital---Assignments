#include <stdio.h>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat image, I, gray, Res;
	image = imread("apple2.jpg", 1);

	// For taking it via Command Line
	// image = imread(argv[1], 1); 

	// Converting to Gray Scale : If Required
	cvtColor(image, I, cv::COLOR_BGR2GRAY);

	blur(I, Res, Size(20, 20));

	// Display Images
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", I);

	cvNamedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);
	imshow("Smoothed Image", Res);

	cv::waitKey(0);
	return 0;
}