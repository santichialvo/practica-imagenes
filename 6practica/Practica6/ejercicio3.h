#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

mt19937 mt_rand(time(0));

void ejercicio3(char** argv)
{
	Mat * imgs = new Mat[6];
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
//	imgs[1] = gaussianNoise(&imgs[0],0,.1,mt_rand);
	imgs[1] = impulsiveNoise(&imgs[0],0,1);
	
	medianBlur(imgs[1],imgs[2],3);
	imgs[2] = filter_mid_point(imgs[2],3);
	cout<<"ECM Mediana y Punto Medio: "<<ECM(imgs[0],imgs[2])<<endl;
	imgs[3] = filter_alfa_mid(imgs[1],3,4);
	cout<<"ECM Alfa Media Recortado: "<<ECM(imgs[0],imgs[3])<<endl;
	
	ShowMultipleImages(imgs,4,4,300,300,30,"Imagenes");
	waitKey(0);
}
