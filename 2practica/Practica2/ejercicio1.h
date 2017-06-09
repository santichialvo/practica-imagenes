#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "pdi_functions.h"
#include "utils.h"

using namespace cv;
using namespace std;

Point Point1(-1,-1);
Point Point2(-1,-1);
Point Invalid(-1,-1);

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  (event == EVENT_LBUTTONDOWN)
	{
		if (Point1==Invalid)
			Point1=Point(x,y);
		else if (Point2==Invalid)
			Point2=Point(x,y);
	}
}

void ejercicio1(char** argv)
{
	Mat img;
	img = imread(argv[1],1);
	if (img.empty()) cout << "Error loading the image" << endl;
	
	int *lut = new int[256];
//	por tramos
//	create_linear_lut(1,0,0,255,lut);
//	create_linear_lut(-1,255,128,255,lut);
//	negativo
	create_linear_lut(-1,255,0,255,lut);
	
	Mat intgraph(1,256,CV_32F,lut);
	Mat graph = draw_graph(intgraph);
	
	//aplico el lut en la img2
	Mat img2 = img.clone();
	int intensity;
	for(int i=0;i<img2.rows;i++) {
		for(int j=0;j<img2.cols;j++) {
			intensity = img2.at<Vec3b>(i,j)[0]; //agarramos el 0 porque son los 3 canales =
			for(int k=0;k<3;k++) { img2.at<Vec3b>(i,j)[k] = *(lut+intensity); }
		}
	}
	
	//muestro las dos imagenes juntas
	Mat *imgs = new Mat[3];
	imgs[0] = img; imgs[1]=graph; imgs[2] = img2;
//	ShowMultipleImages(imgs, 3, 3, img.rows, img.cols, 20);
	
	
	//Ejercicio 5
	
	Mat ImagenBinaria(256,256,CV_8UC(3));
	
	namedWindow("EJ5", WINDOW_AUTOSIZE);
	setMouseCallback("EJ5",CallBackFunc,NULL);
	imshow("EJ5", ImagenBinaria);
	waitKey(0);
	if (Point1!=Invalid && Point2!=Invalid) {
		cout<<"Correctamente seteados"<<endl;
//		cambio las coordenadas porque la ventana empieza en el margen supizq
		Point1.y = 255-Point1.y;
		Point2.y = 255-Point2.y;
		float a1,a2,a3,c1,c2,c3;
		a1 = float(Point1.y)/float(Point1.x);
		a2 = (float(Point2.y)-float(Point1.y))/(float(Point2.x)-float(Point1.x));
		a3 = (255.0-Point2.y)/(255.0-Point2.x);
		c1 = 0;
		c2 = Point1.y + a2*-Point1.x;
		c3 = Point2.y + a3*-Point2.x;
		
		int *lut = new int[256];
		create_linear_lut(a1,c1,0,Point1.x,lut);
		create_linear_lut(a2,c2,Point1.x,Point2.x,lut);
		create_linear_lut(a3,c3,Point2.x,255,lut);
		
		Mat intgraph(1,256,CV_32F,lut);
		Mat graph = draw_graph(intgraph);
		
		Mat img2 = img.clone();
		int intensity;
		for(int i=0;i<img2.rows;i++) {
			for(int j=0;j<img2.cols;j++) {
				intensity = img2.at<Vec3b>(i,j)[0]; //agarramos el 0 porque son los 3 canales =
				for(int k=0;k<3;k++) { img2.at<Vec3b>(i,j)[k] = *(lut+intensity); }
			}
		}
		
		//muestro las dos imagenes juntas
		Mat *imgs = new Mat[3];
		imgs[0] = img; imgs[1]=graph; imgs[2] = img2;
		ShowMultipleImages(imgs, 3, 3, img.rows, img.cols, 20);
	}
	else
		{ cout<<"Punto 1 o 2 no seteado"; return; }

}
