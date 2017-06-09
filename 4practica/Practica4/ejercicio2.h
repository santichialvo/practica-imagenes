#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
using namespace std;

void ejercicio2(char** argv)
{
//	rio.jpg
	Mat * imgorig = new Mat[2];
	imgorig[0] = imread(argv[1],0);
	if (imgorig[0].empty()) cout << "Error loading the image" << endl;
	
	Mat histo = histogram(imgorig[0],256);
	Mat graphhistogram = draw_graph(histo);
	
	cvtColor(imgorig[0],imgorig[1],CV_GRAY2RGB);
	
	for(int i=0;i<imgorig[0].rows;i++) { 
		for(int j=0;j<imgorig[0].cols;j++) { 
			if (imgorig[0].at<uchar>(i,j) < 45)
			{
				imgorig[1].at<Vec3b>(i,j)[0] = 0;
				imgorig[1].at<Vec3b>(i,j)[1] = 255;
				imgorig[1].at<Vec3b>(i,j)[2] = 255;
			}
		}
	}
	
//	imshow("histograma",graphhistogram);
	ShowMultipleImages(imgorig,2,2,400,400,20);
	waitKey(0);
	
}
