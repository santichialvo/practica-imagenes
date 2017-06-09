#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

void ejercicio5P2()
{
	Mat imgs[4];
	string name1 = "../../imgs/a7v600-X.jpg";
	string name2 = "../../imgs/a7v600-SE.jpg";
	string name3 = "../../imgs/a7v600-X_RImpulsivo.jpg";
	string name4 = "../../imgs/a7v600-SE_RImpulsivo.jpg";
	imgs[0] = imread(name1,1);
	imgs[1] = imread(name2,1);
	imgs[2] = imread(name3,1);
	imgs[3] = imread(name4,1);
	if (imgs[0].empty()||imgs[1].empty()||imgs[2].empty()||imgs[3].empty()) cout << "Error loading the image" << endl;
	
	
//	elimino el ruido impulsivo con un filtro de mediana
	medianBlur(imgs[2],imgs[2],3);
	medianBlur(imgs[3],imgs[3],3);
	
	for(int i=0;i<4;i++)
		cvtColor(imgs[i],imgs[i],CV_BGR2GRAY);
	
	//aplico el lut en las imagenes
	int** lut = new int*[4];
	for(int i=0; i<4; ++i)
		lut[i] = new int[256];
	
	Mat * imgslut = new Mat[4];
	Mat * graphslut = new Mat[4];
	
	for(int l=0;l<4;l++) {
		
//		realzo las partes blancas y veo si tiene disipador
		create_linear_lut(0,255,0,50,lut[l]);
		create_linear_lut(0,0,51,255,lut[l]);
		
		Mat intgraph(1,256,CV_32F,lut[l]);
		graphslut[l] = draw_graph(intgraph);
		
		imgslut[l] = imgs[l].clone();
		int intensity;
		for(int i=0;i<imgslut[l].rows;i++) {
			for(int j=0;j<imgslut[l].cols;j++) {
				intensity = imgslut[l].at<uchar>(i,j);
				imgslut[l].at<uchar>(i,j) = *(lut[l]+intensity);
			}
		}
//		region donde esta el disipador +/-
		int(imgslut[l].at<uchar>(124,220))==255?cout<<"Es una a7v600-X"<<endl:cout<<"Es una a7v600-SE"<<endl;
	}
	
	//muestro las dos imagenes juntas
	Mat *imgs2 = new Mat[12];
	for(int i=0,j=0;i<4;++i,j+=3)
	{ imgs2[j] = imgs[i]; imgs2[j+1]=graphslut[i]; imgs2[j+2] = imgslut[i]; }
	
	ShowMultipleImages(imgs2, 12, 3, 150, 150, 10);
}
