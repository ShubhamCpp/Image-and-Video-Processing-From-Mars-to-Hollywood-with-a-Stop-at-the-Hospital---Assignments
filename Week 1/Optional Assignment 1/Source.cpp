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

void ScanAndReduceImageAndIterate(Mat& I, const uchar* const table)
{
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
			p[j] = table[p[j]];
		}
	}
}

int main(int argc, char** argv)
{
	Mat image, I, gray;
	image = imread("apple2.jpg", 1);

	// For taking it via Command Line
	// image = imread(argv[1], 1); 

	// Converting to Gray Scale : If Required
	//cvtColor(image, I, cv::COLOR_BGR2GRAY);
	I = image.clone();

	int dividewith = 0, levels;
	A: cout << "Enter the required number of Intensity Levels " <<endl;
	cin >> levels;

	if (levels >= 256 || levels < 2){
		cout << "Wrong Input";
		goto A;
	}

	dividewith = 256 / levels;
	uchar table[256];
	for (int i = 0; i < 256; i++){
		table[i] = (uchar)((i / dividewith) * dividewith);
	}

	ScanAndReduceImageAndIterate(I, table);

	// Display Images
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", image);

	cvNamedWindow("Reduced Image", CV_WINDOW_AUTOSIZE);
	imshow("Reduced Image", I);

	cv::waitKey(0);
	return 0;
}