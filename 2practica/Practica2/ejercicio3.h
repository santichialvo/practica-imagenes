#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
using namespace std;

void ejercicio3()
{
	Mat img1,img2,res;
	string name1 = "../../imgs/huang2.jpg";
	string name2 = "../../imgs/rmn.jpg";
	img1 = imread(name1,1);
	img2 = imread(name2,1);
	if (img1.empty() || img2.empty()) cout << "Error loading the image" << endl;
	
//	Punto 1
	
//	suma
//	res = arithmetic_operations(0,img1,img2);
//	resta
	res = arithmetic_operations(1,img1,img2);
//	multiplicacion
//	Mat mascara(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
//	for(int i=0;i<img1.rows/2;i++) { for(int j=0;j<img1.cols/2;j++) { for(int k=0;k<3;k++) { mascara.at<Vec3b>(i,j)[k]=255; } } }
//	res = arithmetic_operations(2,img1,mascara);
//	division
//	res = arithmetic_operations(3,img1,img2);
	
//	Mat *imgs = new Mat[3];
//	imgs[0]=img1; imgs[1]=img2; imgs[2]=res;
//	ShowMultipleImages(imgs, 3, 3, img1.rows, img1.cols, 20);
	
	
//	Punto 2
	
	Mat NoisyImage=DecreaseNoise(img1,50);
	
//	Muestro la imagen original y la reconstruida
	Mat *imgs = new Mat[2];
	imgs[0]=img1; imgs[1]=res;
	ShowMultipleImages(imgs, 2, 2, img1.rows, img1.cols, 20);
}
