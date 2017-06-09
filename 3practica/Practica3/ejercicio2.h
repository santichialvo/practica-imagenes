#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
using namespace std;

void ejercicio2(char** argv)
{
	Mat * imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
//	mascaras de promediado
	
	Mat pkern3 = (Mat_<float>(3,3) <<  	1,1,1,
										1,1,1,
										1,1,1);
	
	pkern3*=1.0/9.0;
	
	Mat pkern4 = (Mat_<float>(4,4) <<  	1,1,1,1,
										1,1,1,1,
										1,1,1,1,
										1,1,1,1);
	
	pkern4*=1.0/16.0;
	
	Mat pknern7 = create_prom_kernel(7.0);
	
//	mascaras gaussianas
	
	Mat gkern3 = getGaussianKernel(3,1,CV_64F);
	
//	aplicacion de las mascaras
	
	filter2D(imgs[0], imgs[1], imgs[0].depth(), pknern7);
	
//	umbral binario
	threshold(imgs[1],imgs[1], 128.0, 255.0, THRESH_BINARY);
	
//	multiplico por la mascara
	
	imgs[2] = arithmetic_operations(2,imgs[0],imgs[1]);
	
	ShowMultipleImages(imgs,3,3,400,400,10);
}
