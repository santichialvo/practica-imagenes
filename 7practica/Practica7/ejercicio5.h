#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <complex>
#include <cmath>
using namespace std;

typedef complex<float> dcomp;

Mat inverse_motion_blur(Size size, double a, double b){
	cv::Mat transformation =
		cv::Mat::zeros(size, CV_32FC(2));
	
	int
		rows = transformation.rows,
		cols = transformation.cols;
	
	const std::complex<float> I{0,1};
	const std::complex<float> R{1,0};
	complex<float> res;
	for(int K=0; K<rows; ++K) {
		for(int L=0; L<cols; ++L){
			double
				u = (L-cols/2)/(double)cols,
				v = (K-rows/2)/(double)rows;
			
			float pi_v = M_PI*(u*a+v*b);
			float mag  = pi_v? 1/sin(pi_v) : 1;
			res = mag*exp(-I*pi_v)*pi_v;
			
			if (sqrt(res.real()*res.real() + res.imag()*res.imag())<1e-2)
				transformation.at< std::complex<float> >(K,L) = 0;
			else
				transformation.at< std::complex<float> >(K,L) = res;
		}
	}
	
	normalize(transformation,transformation, 0.0, 1.0, CV_MINMAX, CV_32F);
	centre(transformation);
	return transformation;
}

Mat calculeH(size_t rows, size_t cols){
	
	float pi = 2 * asin(1);
	dcomp imag = -1;
	imag = sqrt(imag);
	Mat Hinv = Mat::zeros(rows, cols, CV_32F);
	float a=1,b=1;
	float f1,f2;
	double f3;
	dcomp f3c;
	for(float i=0;i<Hinv.rows;i++) { 
		for(float j=0;j<Hinv.cols;j++) { 
			f1 = 1./(M_PI*(a*i + b*j));
			f2 = sin(M_PI*(a*i + b*j));
			f3c = exp(imag * (pi * (a*i + b*j)));
			f3 = sqrt(f3c.real()*f3c.real() + f3c.imag()*f3c.imag());
			Hinv.at<float>(i,j) = f1*f2*f3;
		}
	}
	normalize(Hinv,Hinv, 0.0, 1.0, CV_MINMAX, CV_32F);
//	imshow("H",Hinv);
	
	float tol = 1e-3;
	
	Hinv = 1./Hinv;
	
	for(float i=0;i<Hinv.rows;i++) { 
		for(float j=0;j<Hinv.cols;j++) { 
			if (Hinv.at<float>(i,j) < tol)
				Hinv.at<float>(i,j) = 0.;
		}
	}
	
	normalize(Hinv,Hinv, 0.0, 1.0, CV_MINMAX, CV_32F);
//	imshow("Hinv",Hinv);
	
//	centre(Hinv);
	return Hinv;
}

Mat filter_with_fase_nozero(Mat image, Mat filtro) {
	
	Mat transformada;
	
	dft(image, transformada, cv::DFT_COMPLEX_OUTPUT);
	mulSpectrums(transformada, filtro, transformada, cv::DFT_ROWS);
	
	Mat result;
	idft(transformada, result, DFT_REAL_OUTPUT|DFT_SCALE);
	
	return result;
}

void ejercicio5(char** argv)
{
	//punto 1
	Mat * imgs = new Mat[2];
	imgs[0] = imread(argv[1],0);
	
	imgs[0].convertTo(imgs[0], CV_32F, 1./255, 0);
	
	int
		original_rows = imgs[0].rows,
		original_cols = imgs[0].cols;
	imgs[0] = optimum_size(imgs[0]);
	
//	Mat filtro = calculeH(imgs[0].rows,imgs[0].cols);
	
	Mat filtro2 = inverse_motion_blur(imgs[0].size(),2,2);
//	filtro2 = 1/filtro2;
//	
//	for(int K=0; K<filtro2.rows; ++K)
//		for(int L=0; L<filtro2.cols; ++L){
//		double
//			u = (L-filtro2.cols/2)/(double)filtro2.cols,
//			v = (K-filtro2.rows/2)/(double)filtro2.rows;
//		
//		filtro2.at<complex<float>>(K,L) = 1 / filtro2.at<complex<float>>(K,L);
//	}
	
	imgs[1] = filter_with_fase_nozero(imgs[0],filtro2);
//	imgs[1] = filter(imgs[0],filtro2);
//	cout<<imgs[1];
//	Mat transformada;
//	Mat mult(imgs[0].rows,imgs[0].cols,CV_32F);
//	dft(imgs[0], transformada, DFT_COMPLEX_OUTPUT);
//	for(int i=0;i<imgs[0].rows;i++) { 
//		for(int j=0;j<imgs[0].cols;j++) { 
//			mult.at<float>(i,j) = imgs[0].at<float>(i,j)*filtro.at<float>(i,j);
//		}
//	}
//	imshow("mult",mult);
//	idft(mult, imgs[1], cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
	
	normalize(imgs[1],imgs[1], 0.0, 1.0, CV_MINMAX, CV_32F);
	
//	cout<<imgs[1]<<endl;
	
	ShowMultipleImages(imgs,2,2,400,400,30);
	
	waitKey(0);
} 
