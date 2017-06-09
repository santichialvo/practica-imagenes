#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <ctime>
using namespace std;

mt19937 mt_rand(time(0));

void ejercicio2(char** argv)
{
	Mat * imgs = new Mat[6];
	Mat * histograms = new Mat[6];
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	imgs[1] = gaussianNoise(&imgs[0],0,.01,mt_rand);
	imgs[1] = impulsiveNoise(&imgs[1],1,0);
	
	imgs[2] = filter_armonic_median(imgs[1],3);
	cout<<"ECM Media Armonica: "<<ECM(imgs[0],imgs[2])<<endl;
	imgs[3] = filter_geometric_median(imgs[1],3);
	cout<<"ECM Media Geometrica: "<<ECM(imgs[0],imgs[3])<<endl;
	imgs[4] = filter_aritmetic_media(imgs[1],3);
	cout<<"ECM Media Aritmetica: "<<ECM(imgs[0],imgs[4])<<endl;
	//orden negativo para sal, positivo para pimienta
	imgs[5] = filter_contraarmonic_media(imgs[1],3,3.);
	cout<<"ECM Media ContraArmonica: "<<ECM(imgs[0],imgs[5])<<endl;
	
	ShowMultipleImages(imgs,6,3,300,300,30,"Imagenes");
	waitKey(0);
}

