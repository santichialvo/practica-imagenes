#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "pdi_functions.h"
#include "utils.h"

using namespace cv;
using namespace std;

void ejercicio1(char** argv)
{
//	punto 1
	
//	Mat * imgs = new Mat[4];
//	Mat * hists = new Mat[2];
//	imgs[0] = imread(argv[1],1);
//	if (imgs[0].empty()) cout << "Error loading the image" << endl;
//	
//	cvtColor(imgs[0],imgs[0],CV_BGR2GRAY);
//	
//	equalizeHist(imgs[0],imgs[1]);
//	
//	// Compute the histograms
//	hists[0] = histogram(imgs[0],256);
//	hists[1] = histogram(imgs[1],256);
//	imgs[2] = draw_graph(hists[0]);
//	imgs[3] = draw_graph(hists[1]);
//	
//	ShowMultipleImages(imgs,4,2,imgs[0].rows,imgs[0].cols,10);
	
//	punto 2
	
	Mat * imgs = new Mat[10];
	Mat * hists = new Mat[5];
	imgs[0] = imread("../../imgs/imagenA.tif",1);
	imgs[1] = imread("../../imgs/imagenB.tif",1);
	imgs[2] = imread("../../imgs/imagenC.tif",1);
	imgs[3] = imread("../../imgs/imagenD.tif",1);
	imgs[4] = imread("../../imgs/imagenE.tif",1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	for(int i=0;i<5;i++) {  cvtColor(imgs[i],imgs[i],CV_BGR2GRAY); }
	
	// Compute the histograms
	for(int i=0;i<5;i++) { hists[i] = histogram(imgs[i],256); }
	
	for(int i=5;i<10;i++) { imgs[i] = draw_graph(hists[i-5]); }
	
	ShowMultipleImages(imgs,10,5,200,200,10);

}
