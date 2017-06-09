#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "utils.h"
#include <vector>

using namespace cv;
using namespace std;

int ejercicio3(int argc, char** argv) {
	// Read image from file 
	Mat image = imread(argv[1],1);
	
	//if fail to read the image
	if (image.empty())
	{ 
		cout << "Error loading the image" << endl;
		return -1; 
	}
	
//	PlotIntensityProfile(image,true,image.rows/2,0,image.cols);
	
	//pixels de inicio-fin de cada botella
	vector<int> InicioFin;
	
	int intArray[image.cols]; 
	for(int i=0;i<image.cols;i++) {
		Vec3b color = image.at<Vec3b>(image.rows/2,i);
		intArray[i] = color.val[0];
	}
	int i=0;
	while (i<image.cols) {
		while (intArray[i]==0 && i<image.cols) i++;
		InicioFin.push_back(i);
		while (intArray[i]!=0 && i<image.cols) i++;
		InicioFin.push_back(i);
	}
	
	int CantBotellasx2 = InicioFin.size();
	
	//Las imagenes tienen una porcion negra arriba y una blanca minima abajo. Tomo cualquier botella 
	//para averiguar estos rangos
	
	i=0;
	int InicioBotellas,FinBotellas;
	while (i<image.cols) {
		Vec3b color = image.at<Vec3b>(i,(InicioFin[0]+InicioFin[1])/2);
		if (color[0]==0) i++;
		else { InicioBotellas = i; break; }
		
	}
	i=image.rows-1;
	while (i>0) {
		Vec3b color = image.at<Vec3b>(i,(InicioFin[0]+InicioFin[1])/2);
		if (color[0]==255) i--;
		else { FinBotellas = i; break; }
	}
	
	// Pongo una linea en el inicio y otra en el final
	for(int i=0;i<image.cols;i++) {  image.at<Vec3b>(InicioBotellas,i) = 255; image.at<Vec3b>(FinBotellas,i) = 255; }
	
	float AlturaBotellas = FinBotellas-InicioBotellas;
	for(int i=0;i<CantBotellasx2;i+=2) {
		int cant=0;
		for(int j=InicioBotellas;j<FinBotellas;j++) {
			Vec3b color = image.at<Vec3b>(j,(InicioFin[i]+InicioFin[i+1])/2);
			if (color.val[0]>230)
				cant++;
		}
		for(int j=0;j<image.rows;j++) {  image.at<Vec3b>(j,(InicioFin[i]+InicioFin[i+1])/2) = 0; }
		float porcvacio = float(cant)/AlturaBotellas;
//		PlotIntensityProfile(image,false,(InicioFin[i]+InicioFin[i+1])/2,0,image.rows);
		
//		Decimos que no esta llena si el "blanco" (parte no llena) supera el 20%
//		if (porcvacio > 0.2) {
		printf("La botella %d, esta llena en un %f % \n",i/2,1.0-porcvacio);
		for(int j=0;j<image.rows;j++) {  image.at<Vec3b>(j,InicioFin[i]) = 255; image.at<Vec3b>(j,InicioFin[i+1]-1) = 255; }
//		}
	}
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", image);
	waitKey(0);
}
