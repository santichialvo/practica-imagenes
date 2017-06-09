#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

void ejercicio3(char** argv)
{
	//	camaleon.tif
	int point = 1;
	
	switch (point)
	{
	case 1:
	{
		Mat *imgs = new Mat[4];
		Mat *filters = new Mat[3];
		Mat *spectrums = new Mat[4];
		
		imgs[0] = imread(argv[1],0);
		if (imgs[0].empty()) cout << "Error loading the image" << endl;
		imgs[0].convertTo(imgs[0],CV_32F,1./255);
		
		int
			original_rows = imgs[0].rows,
			original_cols = imgs[0].cols;
		imgs[0] = optimum_size(imgs[0]);
		
		float 
			A = 2.,
			a = 2.,
			b = 3.;
		
		//	alta potencia con ideal
		filters[0] = (A-1) + (1-filter_ideal(imgs[0].rows,imgs[0].cols,0.01));
		//	alta potencia con butt
		filters[1] = (A-1) + (1-filter_butterworth(imgs[0].rows,imgs[0].cols,0.01,2));
		//	enfasis alta frecuencia con butt
		filters[2] = a + b*(1-filter_butterworth(imgs[0].rows,imgs[0].cols,0.01,2));
		
		imgs[1] = filter(imgs[0],filters[0]);
		imgs[2] = filter(imgs[0],filters[1]);
		imgs[3] = filter(imgs[0],filters[2]);
		
		for(int i=0;i<3;i++) { centre(filters[i]); }
		for(int i=0;i<4;i++) { imgs[i]=imgs[i](Range(0,original_rows),Range(0,original_cols)); }
		for(int i=0;i<4;i++) { spectrums[i]=spectrum(imgs[i]); }
		
		//	imshow("non-filtered",imgs[0]);
		imshow("filtered",imgs[2]);
//		ShowMultipleImages(imgs,4,4,400,400,30,"imagenes");
//		ShowMultipleImages(filters,3,3,400,400,30,"filtros");
//		ShowMultipleImages(spectrums,4,4,400,400,30,"espectros");
	}
	}
	waitKey(0);
}

