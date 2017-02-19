#include <stdio.h>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void ApplyMask(Mat& I)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	// Channels ( 3 = RGB , 1 = GrayScale )
	const int channels = I.channels();

	// Rows and Columns
	int Rows = I.rows;
	int Cols = I.cols * channels;

	for (int i = 1; i < Rows - 1; i = i + 3){

		uchar* previous = I.ptr<uchar>(i - 1);
		uchar* current = I.ptr<uchar>(i);
		uchar* next = I.ptr<uchar>(i + 1);

		uchar avg;

		for (int j = channels; j < channels * (Cols - 1); j = j + 3){
			avg = saturate_cast<uchar>((current[j] + current[j - channels] + current[j + channels] + previous[j] + previous[j - channels] + previous[j + channels] + next[j] + next[j - channels] + next[j + channels]) / 9);
			current[j] = avg;
			current[j - channels] = avg;
			current[j + channels] = avg;
			previous[j] = avg;
			previous[j - channels] = avg;
			previous[j + channels] = avg;
			next[j] = avg;
			next[j - channels] = avg;
			next[j + channels] = avg;
		}
	}
}

int main(int argc, char** argv)
{
	Mat image, I, gray, Res;
	image = imread("Apple.jpg", 1);

	// For taking it via Command Line
	// image = imread(argv[1], 1); 

	// Converting to Gray Scale : If Required
	cvtColor(image, image, cv::COLOR_BGR2GRAY);

	I = image.clone();

	ApplyMask(I);

	// Display Images
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", image);

    cvNamedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);
	imshow("Smoothed Image", I);

	cv::waitKey(0);
	return 0;
}