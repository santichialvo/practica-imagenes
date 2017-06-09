#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables
Mat src, erosion_dst, dilation_dst, opening_dst, gradient_dst;

int erosion_elem = 0;
int opening_elem = 0;
int gradient_elem = 0;
int erosion_size = 0;
int opening_size = 0;
int gradient_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int opening_closing = 0; //0 para abrir, 1 para cerrar
int const max_elem = 2;
int const max_kernel_size = 200;

/** Function Headers */
void Erosion (int,void*);
void Dilation(int,void*);
void Opening_Closure(int,void*);
void Gradient(int,void*);

void ejercicio1(char** argv )
{
	/// Load an image
	src = imread(argv[1],0);
	
	/// Create windows
	namedWindow("Erosion",CV_WINDOW_AUTOSIZE);
	namedWindow("Dilation",CV_WINDOW_AUTOSIZE);
	namedWindow("Opening",CV_WINDOW_AUTOSIZE);
	namedWindow("Gradient",CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Dilation",src.cols,0);
	
	/// Create Erosion Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion", &erosion_elem, max_elem, Erosion);
	createTrackbar("Kernel size:\n 2n +1", "Erosion", &erosion_size, max_kernel_size, Erosion);
	
	/// Create Dilation Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation", &dilation_elem, max_elem,Dilation);
	createTrackbar("Kernel size:\n 2n +1", "Dilation", &dilation_size, max_kernel_size,Dilation);
	
	/// Create Opening Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Opening", &opening_elem, max_elem, Opening_Closure);
	createTrackbar("Kernel size:\n 2n +1", "Opening", &opening_size, max_kernel_size, Opening_Closure);
	createTrackbar("Operation: \n", "Opening", &opening_closing, 1, Opening_Closure);
	
	/// Create Gradient Trackbar
	createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Gradient", &gradient_elem, max_elem, Gradient);
	createTrackbar("Kernel size:\n 2n +1", "Gradient", &gradient_size, max_kernel_size, Gradient);
	
	/// Default start
	Erosion(0,0);
	Dilation(0,0);
	Opening_Closure(0,0);
	Gradient(0,0);
	
	waitKey(0);
}

void Erosion(int, void*)
{
	int erosion_type;
	if (erosion_elem == 0 ) { erosion_type = MORPH_RECT; }
	else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
	else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
	
	Mat element = getStructuringElement(erosion_type, Size( 2*erosion_size + 1, 2*erosion_size+1 ), Point( erosion_size, erosion_size ));
	
	/// Apply the erosion operation
	erode(src,erosion_dst,element);
	imshow("Erosion",erosion_dst);
}

void Dilation(int,void*)
{
	int dilation_type;
	if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
	else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
	else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
	
	Mat element = getStructuringElement(dilation_type, Size( 2*dilation_size + 1, 2*dilation_size+1 ), Point( dilation_size, dilation_size ));
	
	/// Apply the dilation operation
	dilate(src, dilation_dst, element);
	imshow("Dilation", dilation_dst);
}

void Opening_Closure(int,void*)
{
	int opening_type;
	if( opening_elem == 0 ){ opening_type = MORPH_RECT; }
	else if( opening_elem == 1 ){ opening_type = MORPH_CROSS; }
	else if( opening_elem == 2) { opening_type = MORPH_ELLIPSE; }
	
	Mat element = getStructuringElement(opening_type, Size( 2*opening_size + 1, 2*opening_size+1 ), Point( opening_size, opening_size ));
	
	/// Apply the erotion and then dilation operation
	if (!opening_closing) 
	{
//		abrir
//		Useful for removing small objects
//		erode (src, opening_dst, element);
//		dilate(opening_dst, opening_dst, element);
		morphologyEx(src,opening_dst,cv::MORPH_OPEN,element);
	}
	else
	{
//		cerrar
		dilate(src, opening_dst, element);
		erode (opening_dst, opening_dst, element);
	}
	imshow("Opening", opening_dst);
}

void Gradient(int,void*)
{
	int gradient_type;
	if( gradient_elem == 0 ){ gradient_type = MORPH_RECT; }
	else if( gradient_elem == 1 ){ gradient_type = MORPH_CROSS; }
	else if( gradient_elem == 2) { gradient_type = MORPH_ELLIPSE; }
	
	Mat element = getStructuringElement(gradient_type, Size( 2*gradient_size + 1, 2*gradient_size+1 ), Point( gradient_size, gradient_size ));
	
	dilate(src,dilation_dst,element); 
	erode (src,erosion_dst,element);
	gradient_dst = dilation_dst-erosion_dst;
	
	imshow("Gradient", gradient_dst);
}
