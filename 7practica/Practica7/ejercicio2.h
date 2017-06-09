#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include "Hough.h"
#include <math.h>
#include <ctime>
using namespace std;

void ejercicio2(char** argv)
{
	Mat * imgs = new Mat[6];
	Mat * histograms = new Mat[6];
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	Canny(imgs[0], imgs[1], 100, 150, 3);
	
	Hough_Transform(imgs[1]); 
	vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines = Hough_GetLines(55,0,360);
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >::iterator it;
	imgs[2] = Mat(imgs[0].rows,imgs[0].cols,CV_8UC(3));
	
//	recordar que los angulos van en sentido horario!!
///	hacer para longitudes
	
	vector<Vec4i> linesv;
	imgs[3] = imgs[0].clone();
	HoughLinesP(imgs[0],linesv,1,CV_PI/180,450);
	vector<Vec4i>::iterator it2;  
	for(it2=linesv.begin();it2!=linesv.end();it2++)  
	{
//		cout<<(*it2)[0]<<endl;
		line(imgs[3], cv::Point((*it2)[0],(*it2)[1]), cv::Point((*it2)[2],(*it2)[3]), cv::Scalar(255, 0, 255), 1, 1);
//		cv::circle(imgs[2], cv::Point(it->first.first, it->first.second), 1, cv::Scalar(0, 0, 255), -1);
//		cv::circle(imgs[2], cv::Point(it->second.first, it->second.second), 1, cv::Scalar(0, 0, 255), -1);
	}
	
	for(it=lines.begin();it!=lines.end();it++)  
	{
		cv::line(imgs[2], cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar(255, 0, 255), 1, 1);
		cv::circle(imgs[2], cv::Point(it->first.first, it->first.second), 1, cv::Scalar(0, 0, 255), -1);
		cv::circle(imgs[2], cv::Point(it->second.first, it->second.second), 1, cv::Scalar(0, 0, 255), -1);
	}
	
	cvtColor(imgs[0],imgs[0],CV_GRAY2BGR);
	imgs[0]+=imgs[2];
	
	ShowMultipleImages(imgs,4,4,256,256,10);
	waitKey(0);
}

