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
		Mat * imgs = new Mat[5];
		Mat * fourierspectres = new Mat[5];
		for(int i=0;i<5;i++) {  imgs[i] = Mat(300,300,CV_32FC1,0.); }
		
//		linea horizontal
		for(int i=0;i<imgs[0].rows;i++) { 
			for(int j=0;j<imgs[0].cols;j++) { 
				if (i==150) imgs[0].at<float>(i,j)=1.;
			}
		}
//		linea vertical
		for(int i=0;i<imgs[1].rows;i++) { 
			for(int j=0;j<imgs[1].cols;j++) { 
				if (j==150) imgs[1].at<float>(i,j)=1.;
			}
		}
//		cuadrado centrado (?)
		for(int i=0;i<imgs[2].rows;i++) { 
			for(int j=0;j<imgs[2].cols;j++) { 
				if (j<150 && j>100 && i>100 && i<150) imgs[2].at<float>(i,j)=1.;
			}
		}
//		rectangulo centrado (?)
		for(int i=0;i<imgs[3].rows;i++) { 
			for(int j=0;j<imgs[3].cols;j++) { 
				if (j<150 && j>50 && i>100 && i<150) imgs[3].at<float>(i,j)=1.;
			}
		}
//		circulo centrado
		for(int i=0;i<imgs[4].rows;i++) { 
			for(int j=0;j<imgs[4].cols;j++) { 
				if (sqrt((i-150)*(i-150) + (j-150)*(j-150)) < 30) 
					imgs[4].at<float>(i,j)=1.;
			}
		}
		
		for(int i=0;i<5;i++) { fourierspectres[i]=spectrum(imgs[i]); }
		
		ShowMultipleImages(imgs,5,5,300,300,30,"imagenes");
		ShowMultipleImages(fourierspectres,5,5,300,300,30,"espectros");
		break;
	}
	case 2:
	{
		Mat * imgs = new Mat[3];
		Mat * fourierspectres = new Mat[3];
		for(int i=0;i<2;i++) {  imgs[i] = Mat(512,512,CV_32FC1,0.); }
		
		for(int i=0;i<imgs[0].rows;i++) { 
			for(int j=0;j<imgs[0].cols;j++) { 
				if (j==256) imgs[0].at<float>(i,j)=1.;
			}
		}
		
		imgs[1] = rotate(imgs[0],-20.);
		imgs[2] = Mat(imgs[1],Rect(100,120,256,256));
		
		for(int i=0;i<3;i++) { fourierspectres[i]=spectrum(imgs[i]); }
		
		ShowMultipleImages(imgs,3,3,300,300,30,"imagenes");
		ShowMultipleImages(fourierspectres,3,3,300,300,30,"espectros");
		break;
	}
	}
	
	waitKey(0);
}
