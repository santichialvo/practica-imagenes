#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

void ejercicio5P3()
{
	Mat imgs[3];
	string name1 = "../../imgs/blister_completo.jpg";
	string name2 = "../../imgs/blister_incompleto.jpg";
	imgs[0] = imread(name1,1);
	imgs[1] = imread(name2,1);
	if (imgs[0].empty()||imgs[1].empty()) cout << "Error loading the image" << endl;
	
	Size size(imgs[0].cols,imgs[0].rows);
	for(int i=0;i<2;i++) { resize(imgs[i],imgs[i],size); }
	
//	resto la imagen con la pastilla faltante contra una de referencia que tenga todas
	imgs[2] = arithmetic_operations(1,imgs[1],imgs[0]);
	
//	tenemos 10 pastillas
	Mat * ROI = new Mat[10];
	int posx=30,posy=35;
	for(int i=0;i<10;i++) {
		i==5? posx=30,posy=80 : i!=0? posx+=50:posx;
		Mat temp(imgs[2],Rect(posx,posy,50,40));
		ROI[i] = temp;
		threshold(ROI[i], ROI[i], 128.0, 255.0, THRESH_BINARY);
		
		float cantpixn=0;
		for(int j=0;j<ROI[i].rows;j++) {
			for(int k=0;k<ROI[i].cols*3;k++) {
				if (int(ROI[i].at<uchar>(j,k))==0)
					cantpixn+=1;
			}
		}
		float p = cantpixn/(ROI[i].rows * 3.0*ROI[i].cols);
//		Si mas o menos hay mas del 5% de pixeles negros ya es pastilla faltante
		printf("Cantidad de pixeles negros en ROI %d: %f % \n",i,p);
	}

	ShowMultipleImages(ROI,10,5,100,100,10);
}
