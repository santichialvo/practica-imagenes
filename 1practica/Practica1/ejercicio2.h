#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "utils.h"

using namespace std;
using namespace cv;
using namespace pdi;

Point currentPoint;
Mat img;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  (event == EVENT_LBUTTONDOWN)
	{
		currentPoint=Point(x,y);
		cout<<img.at<Vec3b>(currentPoint.y,currentPoint.x)<<endl;	
	}
}

int ejercicio2(int argc, char** argv) {
	// Read image from file 
	img = imread(argv[1],1);
	
	//if fail to read the image
	if (img.empty())
	{ 
		cout << "Error loading the image" << endl;
		return -1; 
	}
	//ejercicio a
	//Create a window
	namedWindow("Ejercicio A", 1);
	//set the callback function for any mouse event
	setMouseCallback("Ejercicio A", CallBackFunc, NULL);
	//show the image
	imshow("Ejercicio A", img);
	// Wait until user press some key
	waitKey(0);
	
	//mostrar perfil de intensidad sobre una columna o fila
	//ejercicio b y c
//	PlotIntensityProfile(img,true,10,0,img.cols);
	
	
	
	return 0;
}
