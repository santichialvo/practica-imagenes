#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

void ejercicio3(char** argv)
{
	Mat *imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
//	Punto 1
	
	Mat laplacekern3 = (Mat_<float>(3,3) << -1,-1,-1,
											-1, 8,-1,
											-1,-1,-1);
	
	Mat promkern3 = create_prom_kernel(3);
	
	filter2D(imgs[0], imgs[1], imgs[0].depth(), promkern3);
	
	imgs[2] = arithmetic_operations(1,imgs[0],imgs[1]);
	
	imgs[0] = arithmetic_operations(0,imgs[0],imgs[2]);
	
	ShowMultipleImages(imgs,3,3,400,400,10);
}
