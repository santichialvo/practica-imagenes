#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <opencv2/legacy/blobtrack.hpp>
#include <random>

using namespace cv;
using namespace std;

mt19937 mt_rand(time(0));

void ejercicio1(char** argv)
{
//	punto 1
	Mat * imgs = new Mat[6];
	Mat * histograms = new Mat[6];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	cvtColor(imgs[0],imgs[0],CV_BGR2GRAY);

	//ruido impulsivo
	imgs[1] = impulsiveNoise(&imgs[0]);
	//ruido uniforme
	imgs[2] = uniformNoise(&imgs[0],-15,15,mt_rand);
	//ruido gaussiano
	imgs[3] = gaussianNoise(&imgs[0],0,.05,mt_rand);
	//ruido gamma
	imgs[4] = gammaNoise(&imgs[0],1,.05,mt_rand);
	//ruido exponencial
	imgs[5] = expNoise(&imgs[0],10.,mt_rand);
	
	ShowMultipleImages(imgs,6,6,300,300,20,"Imagenes con ruido");
	show_histogram(imgs,6,6,"Histogramas");
	waitKey(0);
}
