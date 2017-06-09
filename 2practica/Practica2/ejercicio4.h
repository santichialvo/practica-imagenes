#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

void ejercicio4(char** argv)
{
	Mat img;
	img = imread(argv[1],1);
	if (img.empty()) cout << "Error loading the image" << endl;
	
//	la transformo a un canal
	cvtColor(img,img,CV_BGR2GRAY);
	
	Mat *bitplanes = new Mat[8];
	float *ecm = new float[8];
	
	Mat imgf(img.rows,img.cols,CV_64F);
	normalize(img, imgf, 0.0, 1.0, CV_MINMAX, CV_64F);
	
	for(int i=0;i<8;i++) { 
		bitplanes[i] = Mat(img.rows,img.cols,0);
		ecm[i] = 0;
		for(int j=0;j<img.rows;j++) { 
			for(int k=0;k<img.cols;k++) {
//				planos de bits
//				bitplanes[i].at<uchar>(j,k) =  (1<<i)&img.at<uchar>(j,k);
//				sucesivos planos subiendo la significancia
				bitplanes[i].at<uchar>(j,k) =  img.at<uchar>(j,k)>>(7-i);
			}
		}
		
		normalize(bitplanes[i], bitplanes[i], 0.0, 1.0, CV_MINMAX, CV_64F);
		ecm[i] = 0;
		
		for(int j=0;j<img.rows;j++)
			for(int k=0;k<img.cols;k++)
				ecm[i] += pow(bitplanes[i].at<double>(j,k)-imgf.at<double>(j,k),2);
		
		ecm[i] /= (img.rows*img.cols);
		printf("ECM de la imagen %d: %f \n",i,ecm[i]);
		
	}

	ShowMultipleImages(bitplanes, 8, 4, img.rows, img.cols, 10);
	waitKey(0);
}
