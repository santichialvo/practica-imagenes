#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include "Hough.h"
#include <math.h>
#include <ctime>
using namespace std;

void ejercicio2(char** argv)
{
	Mat img = imread(argv[1], 0);
//	threshold(img, img, 127, 255, THRESH_BINARY);
//	for(int i=0;i<img.rows;i++) { 
//		for(int j=0;j<img.cols;j++) { 
//			if (img.at<uchar>(i,j)==0)
//				img.at<uchar>(i,j) = 255;
//			else
//				img.at<uchar>(i,j) = 0;
//		}
//	}
	
	Mat skel(img.size(), CV_8UC1, Scalar(0));
	Mat temp(img.size(), CV_8UC1);
	
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
	
	//	At each iteration the image is eroded again and the skeleton is refined by 
	//	computing the union of the current erosion less the opening of this erosion. 
	//	An opening is simply an erosion followed by a dilation.
	
	imshow("Mina",img);
	bool done;
	do
	{
		morphologyEx(img, temp, MORPH_OPEN, element);
		bitwise_not(temp, temp);
		bitwise_and(img, temp, temp);
		bitwise_or(skel, temp, skel);
		erode(img, img, element);
		
		double max;
		minMaxLoc(img, 0, &max);
		done = (max == 0);
	} while (!done);
	
	imshow("Skeleton", skel);
	waitKey(0);
}

1
