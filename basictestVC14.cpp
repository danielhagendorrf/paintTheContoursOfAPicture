// basictestVC14.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/* load an image from a specific path (IplImage)
transfer the image to a Mat type and return the image */

Mat loadImage(char* path)
{
	// uploading the image
	IplImage *img = cvLoadImage(path);

	// transfering the IplImage image to a Mat type
	Mat image(img);

	return image;

}

/* gets an image (Mat)
shows the image */

void showImage(Mat img)
{
	// create a new window to show the image in
	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);

	// show the image in the created window
	imshow("MyWindow", img);

	waitKey(0);

}

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void*);

/** @function main */
int main(int argc, char** argv)
{
	/// Load source image and convert it to gray
	Mat src = loadImage("c:\\WeizmanProjectPictures\\Daniel\\p2.jpg");
	showImage(src);
	/// Convert image to gray and blur it
	cvtColor(src, src_gray, CV_BGR2GRAY);
	//showImage(src_gray);
	blur(src_gray, src_gray, Size(3, 3));
	//showImage(src_gray);
	threshold(src_gray, src_gray, 25, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	showImage(src_gray);
	/// Create Window
	char* source_window = "Source";
	namedWindow(source_window, CV_WINDOW_AUTOSIZE);
	imshow(source_window, src);

	createTrackbar(" Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
	thresh_callback(0, 0);

	waitKey(0);
	return(0);
}

/** @function thresh_callback */
void thresh_callback(int, void*)
{
	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	/// Detect edges using canny
	Canny(src_gray, canny_output, thresh, thresh * 2, 3);
	showImage(canny_output);
	/// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
}