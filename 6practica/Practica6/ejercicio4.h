#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

void ejercicio4(char** argv)
{
	//punto 1
	Mat * imgs = new Mat[3];
	Mat * fourierspectres = new Mat[3];
	Mat * filters = new Mat[2];
	float * ecms = new float[1];
	imgs[0] = imread(argv[1],0);
	imgs[1] = imread(argv[2],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	
	for(int i=0;i<2;i++) { imgs[i].convertTo(imgs[i],CV_32F,1./255); }
//	filtros para img_degradada.tif
//	filters[0] = 1-notch_filter_ideal(imgs[0].rows,imgs[0].cols,0.15,70,85);
//	filters[1] = 1-notch_filter_ideal(imgs[0].rows,imgs[0].cols,0.1,185,90);
//	filtros para noisy_moon.jpg
//	filters[0] = filter_rejectband(imgs[0].rows,imgs[0].cols,0.2,0.6,0);
//	filtros para head
	filters[0] = filter_rejectband(imgs[0].rows,imgs[0].cols,0.01,0.30,0);
	
	imgs[2] = filter(imgs[0],filters[0]);
//	imgs[2] = filter(imgs[2],filters[1]);
	
	for(int i=0;i<3;i++) { fourierspectres[i]=spectrum(imgs[i]); }
	
	ecms[1] = ECM(imgs[2],imgs[1]);
	ecms[0] = ECM(imgs[1],imgs[0]);
	cout<<"El ECM sin filtro es: "<<ecms[0]<<endl;
	cout<<"El ECM con filtro es: "<<ecms[1]<<endl;
	
	ShowMultipleImages(imgs,3,3,300,300,30,"imagenes");
	ShowMultipleImages(fourierspectres,3,3,300,300,30,"espectros");
//	ShowMultipleImages(filters,1,1,300,300,30,"filtros");
	waitKey(0);
}
