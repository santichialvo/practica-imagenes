#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

void ejercicio3(char** argv)
{
	Mat *imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
//	chairs_oscura.jpg 1
//	flowers_oscura.tif 1
//	camino.tif 2
	int punto = 2;
	
	switch (punto)
	{
	case 1:
	{
		cvtColor(imgs[0],imgs[2],CV_RGB2HSV);
		Mat * hsv = new Mat[3];
		split(imgs[2],hsv);
		Mat * hsveq = new Mat[3];
//		ecualizar solo v
		equalizeHist(hsv[2],hsveq[2]);
		hsveq[0]=hsv[0];
		hsveq[1]=hsv[1];
		merge(hsveq,3,imgs[2]);
		cvtColor(imgs[2],imgs[2],CV_HSV2RGB);
		
//		ecualizar los 3 canales
		Mat * rgb = new Mat[3];
		split(imgs[0],rgb);
		Mat * rgbeq = new Mat[3];
		for(int i=0;i<3;i++) {equalizeHist(rgb[i],rgbeq[i]);}
		merge(rgbeq,3,imgs[1]);
		
		ShowMultipleImages(imgs,3,3,500,500,10,"img orig - rgb eq - hsv eq");
//		ShowMultipleImages(rgbeq,3,3,400,400,10,"rgb-eq");
//		ShowMultipleImages(rgb,3,3,400,400,10,"rgb-prev");
		waitKey(0);
		break;
	}
	case 2:
	{
		cvtColor(imgs[0],imgs[2],CV_RGB2HSV);
		Mat pkern3 = create_highpass_kernel(3);
		
		filter2D(imgs[0], imgs[1], imgs[0].depth(), pkern3);
		filter2D(imgs[2], imgs[2], imgs[1].depth(), pkern3);
		
		cvtColor(imgs[2],imgs[2],CV_HSV2RGB);
		
		ShowMultipleImages(imgs,3,3,500,500,10,"img orig - filtro rgb - filtro hsv");
		waitKey(0);
		break;
	}
	
	}
	
}
