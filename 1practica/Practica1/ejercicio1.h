#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int ejercicio1(int argc, char** argv)
{
	Mat image;
	image = imread(argv[1],1);
	if ( !image.data )
	{
		printf("No image data \n ");
		return -1;
	}
	
//	información de la imagen
//	cout<<image<<endl;				//valores de pixeles
//	cout<<image.size()<<endl;		//tamaño de imagen
//	cout<<image.cols<<endl;			//cantidad de columnas
//	cout<<image.rows<<endl;			//cantidad de filas
//	cout<<image.channels()<<endl;	//cantidad de canales
	
//	crear ROI
	Mat ROI1(image,Rect(100,100,100,100));
	Mat ROI2 = image(Range::all(),Range(100,300));
	
//	ver intensidad en un pixel especifico
	Vec3b intensity = ROI1.at<Vec3b>(1,1);
	cout<<intensity<<endl;
	
//	cambiar intensidad de un pixel
	for(int i=0;i<100;i++) {  ROI1.at<Vec3b>(i,i) = 0; }
	
//	mostrar varias imagenes
	int espacio = 20;
	int dstWidth = ROI1.size[1]+ROI2.size[1]+espacio;
	int dstHeight = max(ROI1.size[0],ROI2.size[0]);
	Mat dst(dstHeight,dstWidth,CV_8UC(3));
	ROI1.copyTo(dst.rowRange(0, ROI1.rows).colRange(0, ROI1.cols));
	ROI2.copyTo(dst.rowRange(0,ROI2.rows).colRange(espacio+ROI1.cols,espacio+ROI1.cols+ROI2.cols));
	
	namedWindow("Display Image", WINDOW_AUTOSIZE);
	imshow("Display Image", dst);
	waitKey(0);
	
	return 0;
}
