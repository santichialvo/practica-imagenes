#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
using namespace std;

void ejercicio5(char** argv)
{
	Mat * imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	imgs[1] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	cvtColor(imgs[0],imgs[0],CV_BGR2HSV);
	
	Mat roi(imgs[0],Rect(160,430,344,272));
	
	Mat pkern3 = create_prom_kernel(12);
	
	filter2D(roi, roi, roi.depth(), pkern3);
	
	Mat* bgr = new Mat[3];
	split(roi,bgr);
	
	Mat histo = histogram(bgr[0],256);
	Mat * hist = new Mat[3];
	hist[0] = draw_graph(histo);
	histo = histogram(bgr[1],256);
	hist[1] = draw_graph(histo);
	histo = histogram(bgr[2],256);
	hist[2] = draw_graph(histo);
	
	for(int j=0;j<roi.rows;j++) {
		for(int k=0;k<roi.cols;k++) {
			if (int(bgr[1].at<uchar>(j,k))<=52.0 && int(bgr[1].at<uchar>(j,k))>=5.0){
				bgr[0].at<uchar>(j,k) = 0;
				bgr[1].at<uchar>(j,k) = 255;
				bgr[2].at<uchar>(j,k) = 0;
			} 
			else {
				bgr[0].at<uchar>(j,k) = 255;
				bgr[1].at<uchar>(j,k) = 0;
				bgr[2].at<uchar>(j,k) = 255;
			}
		}
	}
	
	merge(bgr,3,roi);
	
	cvtColor(imgs[0],imgs[0],CV_HSV2BGR);
	
//	for(int j=0;j<imgs[0].rows;j++)
//		for(int k=0;k<imgs[0].cols*3;k++)
//			if (int(imgs[0].at<uchar>(j,k))!=255.0)
//				imgs[0].at<uchar>(j,k) = 0;
	
	imgs[1] = arithmetic_operations(2,imgs[0],imgs[1]);
	
	imshow("Ejercicio52",imgs[0]);
	imshow("Ejercicio53",imgs[1]);
//	ShowMultipleImages(bgr,3,3,500,500,10);
	waitKey(0);
	
} 
