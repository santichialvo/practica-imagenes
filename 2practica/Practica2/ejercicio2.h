#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

void ejercicio2(char** argv)
{
	Mat img;
	img = imread(argv[1],1);
	if (img.empty()) cout << "Error loading the image" << endl;
	
	int *lut = new int[256];
	create_logaritmic_lut(20,0,255,lut);
//	create_pow_lut(.01,2,0,255,lut);
	
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
	ShowMultipleImages(imgs, 3, 3, img.rows, img.cols, 20);
}
