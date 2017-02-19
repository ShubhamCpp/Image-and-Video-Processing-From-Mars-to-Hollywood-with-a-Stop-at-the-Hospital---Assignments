#include <stdio.h>
#include <opencv2\highgui.hpp>
#include <opencv2\core.hpp>
#include <opencv2\opencv.hpp>

#include <iostream>

using namespace std;
using namespace cv;  

/*Just for Printing Image Values if required for debugging purposes*/
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

void HistogramEqualization(Mat& I)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	// Arrays for Histogram and Cumulative Histogram
	vector<int> Histogram(256, 0);
	vector<int> Cum_Histogram(256, 0);

	// Channels ( 3 = RGB , 1 = GrayScale )
	int channels = I.channels(); // Here it's 1 (Grayscale)

	int size_Image = I.rows * I.cols;

	for (int i = 0; i < I.rows; i++){
		uchar *p = I.ptr<uchar>(i);
		for (int j = 0; j < I.cols; j++){
			int value = (int)p[j];
			Histogram[value]++;
		}
	}
	Cum_Histogram[0] = Histogram[0];

	for (int i = 1; i < 256; i++){
		Cum_Histogram[i] = Histogram[i] + Cum_Histogram[i - 1];
		//cout << "Histogram[" << i << "] = " << Histogram[i] << " ";
		//cout << "Cum_Histogram[" << i << "] = " << Cum_Histogram[i] << endl;
	}
	
	for (int i = 0; i < I.rows; i++){
		uchar *p = I.ptr<uchar>(i);
		for (int j = 0; j < I.cols; j++){
			uchar value = (uchar)p[j];
			p[j] = (uchar)((Cum_Histogram[value] * 255) / size_Image);
		}
	}

}


int main(int argc, char** argv)
{
	Mat image, I, gray, hist_image;
	image = imread("apple2.jpg", 1);

	// For taking it via Command Line
	// image = imread(argv[1], 1); 

	// Converting to Gray Scale : If Required
	cvtColor(image, I, cv::COLOR_BGR2GRAY);
	gray = I.clone();

	HistogramEqualization(I);

	equalizeHist(gray, hist_image); // OpenCV's Inbuilt Function

	// Display Images
	cvNamedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", gray);

	cvNamedWindow("Histogram Equalised Image", CV_WINDOW_AUTOSIZE);
	imshow("Histogram Equalised Image", I);

	cvNamedWindow("Histogram Equalised Image using Inbuilt function", CV_WINDOW_AUTOSIZE);
	imshow("Histogram Equalised Image using Inbuilt function", hist_image);

	cv::waitKey(0);
	return 0;
}