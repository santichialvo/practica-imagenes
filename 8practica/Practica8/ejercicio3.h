#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

Mat * imgs;

Mat create_border_image(Mat &img)
{
	Mat res(img.rows,img.cols,CV_8U);
	for(int i=0;i<res.rows;i++) { 
		for(int j=0;j<res.cols;j++) { 
			if (i==0 || i==res.rows-1 || j==0 || j==res.cols-1)
				res.at<uchar>(i,j) = img.at<uchar>(i,j)?0:255;
			else
				res.at<uchar>(i,j) = 0;
		}
	}
	return res;
}

void ejercicio3(char** argv)
{
	imgs = new Mat[7];
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	imgs[0] = imgs[0](Range(1,imgs[0].rows-1),Range(1,imgs[0].cols-1));
	
//	complemento
	bitwise_not(imgs[0], imgs[1]);
//	imagen F del borde
	imgs[2]=create_border_image(imgs[0]);
//	dilatar con cruz
	Mat element = getStructuringElement(MORPH_CROSS, Size(5, 5));
	dilate(imgs[2], imgs[3], element);
//	interseccion de lo anterior con el complemento
	bitwise_and(imgs[1],imgs[3],imgs[4]);
//	imagen H
	bitwise_not(imgs[4],imgs[5]);
//	iamgen final
	bitwise_and(imgs[5],imgs[0],imgs[6]);
	
	ShowMultipleImages(imgs,7,3,300,300,20);
	waitKey(0);
}
