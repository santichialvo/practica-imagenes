#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

//bone.tif

Point currentPoint=Point(-1,-1);
Mat * imgs;

void crecimiento_regiones2(Mat &img, int xseed, int yseed)
{
	Mat regiongrow(img.rows,img.cols,CV_8U);
	regiongrow = Scalar(0);
	list<Vec2i> active_front;
	active_front.push_back(Vec2i(xseed,yseed));
	while(!active_front.empty())
	{
		Vec2i curr = active_front.back();
		
		//condicion
//		cout<<active_front.size()<<endl;
		if (img.at<uchar>(curr[0],curr[1]) == 0)
		{
			img.at<uchar>(curr[0],curr[1]) = 0;
		}
		active_front.pop_back();
		regiongrow.at<uchar>(curr[0],curr[1]) = 1;
		
		if (curr[0]!=0 && curr[0]!=img.rows-1 && curr[1]!=0 && curr[1]!=img.cols-1)
		{
//			cout<<curr[0]<<" "<<curr[1]<<endl;
			if (!regiongrow.at<uchar>(curr[0]+1,curr[1])) active_front.push_back(Vec2i(curr[0]+1,curr[1]));
			if (!regiongrow.at<uchar>(curr[0]-1,curr[1])) active_front.push_back(Vec2i(curr[0]-1,curr[1]));
			if (!regiongrow.at<uchar>(curr[0],curr[1]+1)) active_front.push_back(Vec2i(curr[0],curr[1]+1));
			if (!regiongrow.at<uchar>(curr[0],curr[1]-1)) active_front.push_back(Vec2i(curr[0],curr[1]-1));
		}
	}
	cout<<"Done";
}

///arreglar cuando llega a los bordes!!
void crecimiento_regiones(Mat &img, int xseed, int yseed)
{
	if (xseed==0 || xseed==img.cols || yseed==0 || yseed==img.rows) return;
	if 	((img.at<uchar>(xseed,yseed) != 255) || (img.at<uchar>(xseed,yseed) != 255))
	{
		img.at<uchar>(xseed,yseed) = 0;
		crecimiento_regiones(img,xseed,yseed+1);
		crecimiento_regiones(img,xseed,yseed-1);
		crecimiento_regiones(img,xseed+1,yseed);
		crecimiento_regiones(img,xseed-1,yseed);
		crecimiento_regiones(img,xseed+1,yseed+1);
		crecimiento_regiones(img,xseed+1,yseed-1);
		crecimiento_regiones(img,xseed-1,yseed+1);
		crecimiento_regiones(img,xseed-1,yseed-1);
	}
	return;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  (event == EVENT_LBUTTONDOWN)
	{
		currentPoint=Point(x,y);
		cout<<currentPoint<<endl;
		cout<<int(imgs[0].at<uchar>(currentPoint.y,currentPoint.x))<<endl;	
	}
	
	if (currentPoint.x != -1 && currentPoint.y != -1)
	{
//		crecimiento_regiones(imgs[0],currentPoint.y,currentPoint.x);
		crecimiento_regiones2(imgs[0],currentPoint.y,currentPoint.x);
		
		namedWindow("Crecimiento regiones", 1);
		setMouseCallback("Crecimiento regiones", CallBackFunc, NULL);
		imshow("Crecimiento regiones", imgs[0]);
	}
}

void ejercicio3(char** argv)
{
	imgs = new Mat[6];
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	namedWindow("Crecimiento regiones", 1);
	setMouseCallback("Crecimiento regiones", CallBackFunc, NULL);
	imshow("Crecimiento regiones", imgs[0]);
	waitKey(0);
}
