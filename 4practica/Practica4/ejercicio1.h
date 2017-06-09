#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "pdi_functions.h"
#include "utils.h"

using namespace cv;
using namespace std;

void ejercicio1(char** argv)
{
	int point = 2;
	
	switch (point)
	{
	case 1:
	{
		Mat * imgs = new Mat[1];
		imgs[0] = imread(argv[1],1);
		if (imgs[0].empty()) cout << "Error loading the image" << endl;
		
		Mat * bgrchannels = new Mat[3];
		split(imgs[0],bgrchannels);
		
//		ShowMultipleImages(imgs,1,1,400,400,10,"original-bgr");
//		ShowMultipleImages(bgrchannels,3,3,400,400,10,"channels-bgr");
		
		//		convierto a hsv
		Mat * imghsv = new Mat[1];
		cvtColor(imgs[0],imghsv[0],CV_BGR2HSV);
		
		Mat * hsvchannels = new Mat[3];
		split(imghsv[0],hsvchannels);
		
//		ShowMultipleImages(imghsv,1,1,400,400,10,"original-hsv");
//		ShowMultipleImages(hsvchannels,3,3,400,400,10,"channels-hsv");
		
		//		para dar vuelta la cosa (de azul a rojo) doy vuelta el H
		invert_Mat(hsvchannels[0]);
		
		//		con saturacion y brillo al mango
		for(int i=0;i<hsvchannels[0].rows;i++) { 
			for(int j=0;j<hsvchannels[0].cols;j++) { 
				hsvchannels[1].at<uchar>(i,j) = uchar(255);
				hsvchannels[2].at<uchar>(i,j) = uchar(255);
			}
		}
		
		ShowMultipleImages(hsvchannels,3,3,400,400,10,"channels-hsv-mod");
		merge(hsvchannels,3,imghsv[0]);
		cvtColor(imghsv[0],imgs[0],CV_HSV2BGR);
		ShowMultipleImages(imgs,1,1,400,400,10,"bgr-mod");
		
		waitKey(0);
		
		break;
	}
	case 2:
		Mat * imgs = new Mat[2];
		imgs[0] = imread(argv[1],1);
		if (imgs[0].empty()) cout << "Error loading the image" << endl;
		
		Mat * rgbchannels = new Mat[3];
		split(imgs[0],rgbchannels);
		Mat * imghsv = new Mat[1];
		cvtColor(imgs[0],imghsv[0],CV_BGR2HSV);
		
		Mat * hsvchannels = new Mat[3];
		split(imghsv[0],hsvchannels);
		
//		for(int i=0;i<hsvchannels[2].rows;i++) { 
//			for(int j=0;j<hsvchannels[2].cols;j++) { 
//				hsvchannels[2].at<uchar>(i,j) = (rgbchannels[0].at<uchar>(i,j)+rgbchannels[1].at<uchar>(i,j)+rgbchannels[2].at<uchar>(i,j))/3;
//			}
//		}
		
		int *lutI = new int[255];
		create_linear_lut(-1, 255, 0, 255, lutI);
		Mat intgraphI(1,256,CV_32F,lutI);
		Mat lutIgraph = draw_graph(intgraphI);
		apply_lut(hsvchannels[0],lutI);
		
		apply_lut(rgbchannels[0],lutI);
		apply_lut(rgbchannels[1],lutI);
		apply_lut(rgbchannels[2],lutI);
		
		int *lutH = new int[255];
		create_linear_lut(1,  128, 0, 128, lutH);
		create_linear_lut(1, -128, 129, 255, lutH);
		Mat intgraphH(1,256,CV_32F,lutH);
		Mat lutHgraph = draw_graph(intgraphH);
//		apply_lut(hsvchannels[0],lutH);
		
		merge(hsvchannels,3,imghsv[0]);
		merge(rgbchannels,3,imgs[0]);
		
		cvtColor(imghsv[0],imghsv[0],CV_HSV2BGR);
		
//		ShowMultipleImages(hsvchannels,3,3,400,400,10,"channels-hsv-mod");
//		ShowMultipleImages(imghsv,1,1,400,400,10,"hsv-mod");
		imshow("hsv",imghsv[0]);
		imshow("rgb",imgs[0]);
		waitKey(0);
		
		break;
	}

}
