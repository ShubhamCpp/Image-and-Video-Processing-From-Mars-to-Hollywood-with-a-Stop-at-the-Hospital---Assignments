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











/*
#include <stdio.h>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;

void PrintImageValues(Mat& I){
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	// Channels ( 3 = RGB , 1 = GrayScale )
	int channels = I.channels();

	// Rows and Columns
	int Rows = I.rows;
	int Cols = I.cols * channels;

	// Initialise a Pointer to the start of the Image Matrix
	uchar *p = I.data;

	for (int i = 0; i < Rows; i++){
		p = I.ptr<uchar>(i);
		for (int j = 0; j < Cols; j++){
			cout << p[j] << " ";
		}
		cout << endl;
	}
}

void ApplyMask(Mat& I, Mat& Res)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	Res.create(I.size(), I.type());

	// Channels ( 3 = RGB , 1 = GrayScale )
	const int channels = I.channels();

	// Rows and Columns
	int Rows = I.rows;
	int Cols = I.cols * channels;

	for (int i = 1; i < Rows - 1; i++){

		const uchar* previous = I.ptr<uchar>(i - 1);
		const uchar* current = I.ptr<uchar>(i);
		const uchar* next = I.ptr<uchar>(i + 1);

		uchar* p = Res.ptr<uchar>(i);
		
		for (int j = channels; j < channels * (Cols - 1); j++){
			*p++ = saturate_cast<uchar>((current[j] + current[j - channels] + current[j + channels] + previous[j] + previous[j - channels] + previous[j + channels] + next[j] + next[j - channels] + next[j + channels]) / 9);
		}
	}
	Res.row(0).setTo(Scalar(0));
	Res.row(Res.rows - 1).setTo(Scalar(0));
	Res.col(0).setTo(Scalar(0));
	Res.col(Res.cols - 1).setTo(Scalar(0));
}

int main(int argc, char** argv)
{
	Mat image, I, gray, Res;
	image = imread("Apple.jpg", 1);

	// For taking it via Command Line
	// image = imread(argv[1], 1); 

	// Converting to Gray Scale : If Required
	cvtColor(image, I, cv::COLOR_BGR2GRAY);

	//I = image.clone();

	ApplyMask(I, Res);

	// Display Images
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", I);

    cvNamedWindow("Smoothed Image", CV_WINDOW_AUTOSIZE);
	imshow("Smoothed Image", Res);

	cv::waitKey(0);
	return 0;
}
*/