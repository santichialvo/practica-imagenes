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
	imgs[0] = imread(argv[1],0);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	Mat rkern = create_roberts_kernel();
	Mat pkern = create_prewitt_kernel(3);
	Mat skern = create_sobel_kernel(3);
	Mat lkern = create_laplace_kernel(1);
	Mat logkern = create_LoG_kernel();
//	cout<<logkern;
	
	filter2D(imgs[0], imgs[1], imgs[0].depth(), rkern);
	filter2D(imgs[0], imgs[2], imgs[0].depth(), pkern);
	filter2D(imgs[0], imgs[3], imgs[0].depth(), skern);
	filter2D(imgs[0], imgs[4], imgs[0].depth(), lkern);
	filter2D(imgs[0], imgs[5], imgs[0].depth(), logkern);
	
	ShowMultipleImages(imgs,6,6,250,250,20,"Imagen - Roberts - Prewitt - Sobel - Laplace - LoG");
	waitKey(0);
}
