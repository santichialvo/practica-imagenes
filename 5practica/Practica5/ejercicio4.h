#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

int homomorphic_slider,gammalow,gammahigh;
Mat *imgs;
Mat *filters;

void homomorphic_filter(int, void*)
{
	//1. aplico logaritmo
	log(imgs[0],imgs[1]);
	//2. pasa altos butt
	filters[0] = (gammalow/10.)*(1-filter_gaussian(imgs[0].rows,imgs[0].cols,homomorphic_slider/10000.)) + (gammahigh/10.);		
	imgs[2] = filter(imgs[1],filters[0]);
	//3. aplico exp
	exp(imgs[2],imgs[3]);
	
	cout<<"Real GammaLow: "<<(gammalow/10.)<<endl;
	cout<<"Real GammaHigh: "<<(gammahigh/10.)<<endl;
	cout<<"Real FreqCut: "<<(homomorphic_slider/10000.)<<endl;
	cout<<endl;
	imshow("Homomophic ",imgs[3]);
}

void ejercicio4(char** argv)
{
	//reunion.tif
	//casilla.tif
	int point = 1;
	
	switch (point)
	{
	case 1:
	{
		imgs = new Mat[4];
		filters = new Mat[1];
		Mat *spectrums = new Mat[4];
		
		imgs[0] = imread(argv[1],0);
		if (imgs[0].empty()) cout << "Error loading the image" << endl;
		imgs[0].convertTo(imgs[0],CV_32F,1./255);
		
		int
			original_rows = imgs[0].rows,
			original_cols = imgs[0].cols;
		
		imgs[0] = optimum_size(imgs[0]);
		
		homomorphic_slider = 0.001;
//		1. aplico logaritmo
		log(imgs[0],imgs[1]);
//		2. pasa altos butt
		filters[0] = (1-filter_butterworth(imgs[0].rows,imgs[0].cols,homomorphic_slider,2));		
		imgs[2] = filter(imgs[1],filters[0]);
//		3. aplico exp
		exp(imgs[2],imgs[3]);
		
		for(int i=0;i<1;i++) { centre(filters[i]); }
		for(int i=0;i<4;i++) { imgs[i]=imgs[i](Range(0,original_rows),Range(0,original_cols)); }
		for(int i=0;i<4;i++) { spectrums[i]=spectrum(imgs[i]); }
		
		/// Create Windows
		namedWindow("Homomophic ", 1);
		int homomorphic_slider_max = 100;
		createTrackbar("HomoTrackbar" ,"Homomophic ", &homomorphic_slider, homomorphic_slider_max, homomorphic_filter);
		createTrackbar("GammaLowTrackbar" ,"Homomophic ", &gammalow, homomorphic_slider_max, homomorphic_filter);
		createTrackbar("GammaHighTrackbar" ,"Homomophic ", &gammahigh, homomorphic_slider_max, homomorphic_filter);
		
		/// Show some stuff
		homomorphic_filter(homomorphic_slider,0);
		waitKey(0);
		
//		ShowMultipleImages(imgs,4,4,400,400,30,"imagenes");
//		ShowMultipleImages(filters,1,1,400,400,30,"filtros");
//		ShowMultipleImages(spectrums,4,4,400,400,30,"espectros");
		break;
	}
	}
	waitKey(0);
}

