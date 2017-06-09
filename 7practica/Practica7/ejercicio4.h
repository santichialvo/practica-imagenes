#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

//recibe 3 canales
Mat etiquetado (Mat &img, list<int> &colors)
{
	cvtColor(img,img,CV_BGR2GRAY);
//	replico bordes para que no joda en los bordes justamente
	copyMakeBorder(img, img, 1, 1, 1, 1, BORDER_REPLICATE);
	int cols = img.cols;
	int rows = img.rows;
	
	int * labels = new int[cols*rows];
	
	for(int i=1;i<img.rows-1;i++) { 
		for(int j=1;j<img.cols-1;j++) {
			labels[i*cols + j] = 0;
		}
	}
	
//	contador de vecinos
	int countveczero;
//	valores a utilizar
	int values=50;
	list<int> labelsvec;
	list<pair<int,int>> equivalences;
	
	for (int p=0;p<15;p++)
	{
		equivalences.clear();
		for(int i=1;i<img.rows-1;i++) { 
			for(int j=1;j<img.cols-1;j++) {
				if (!img.at<uchar>(i,j)) continue;
				labelsvec.clear();
				countveczero = 0;
				for(int u=-1;u<2;u++) 
				{ 
					for(int v=-1;v<2;v++) 
					{ 
						if (!u && !v) continue;
						int currentval = labels[((i+u)*cols) + (j+v)];
						if (currentval==0)
							countveczero++;
						else
						{
							labelsvec.push_back(currentval);
						}
					}
				}
				//	etiqueto con un valor no usado
				if (countveczero==8)
				{
					labels[(i*cols) + j] = values;
					values+=10;
				}
				else if (labelsvec.size()==1)
				{
					labels[(i*cols) + j] = (*labelsvec.begin());
				}
				else if (labelsvec.size()>1)
				{
					labels[(i*cols) + j] = (*labelsvec.begin());
					labelsvec.sort();
					labelsvec.unique();
					// inserto cada posible par
					list<int>::iterator it,it2;  
					for(it=labelsvec.begin();it!=labelsvec.end();it++) {
						it2 = it;
						it2++;
						for(it2;it2!=labelsvec.end();it2++) {
							pair<int,int> p(*it,*it2);
							equivalences.push_back(p);
						}
					}
				}
			}
		}
		
		//	ordeno y limpio las equivalencias, dejo las unicas
		equivalences.sort();
		equivalences.unique();
		list<pair<int,int>>::iterator it;
//		for(it = equivalences.begin(); it != equivalences.end(); it++)
//		{
//			cout<<(*it).first<<" "<<(*it).second<<endl;
//		}
		
		for (it=equivalences.begin(); it!=equivalences.end(); ++it)
		{
			int fir = (*it).first;
			int sec = (*it).second;
			for(int i=0;i<img.rows;i++) { 
				for(int j=0;j<img.cols;j++) { 
					if (labels[(i*cols) + j] == sec)
						labels[(i*cols) + j] = fir;
				}
			}
		}
		
		cout<<"Iteracion "<<p<<endl;
	}
	
	Mat result(img.rows,img.cols,CV_8U);
	
	for(int i=0;i<result.rows;i++) {
		for(int j=0;j<result.cols;j++) {
			uchar aux = labels[(i*cols) + j];
			result.at<uchar>(i,j) = aux;
			if (aux) colors.push_back(aux);
		}
	}
	
//	colores utilizados
	colors.sort();
	colors.unique();
	
	return result;
}


void ejercicio4(char** argv)
{
	Mat * imgs = new Mat[6];
//	imgs[0] = imread(argv[1],1);
	imgs[1] = imread(argv[1],1);
//	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	threshold(imgs[1],imgs[1],0,255,0);
	list<int> colors;
	Mat res = etiquetado(imgs[1],colors);
	
//	list<int>::iterator it;
//	for (it=colors.begin();it!=colors.end();it++)
//		cout<<(*it)<<" ";
	
	make_circles(res,colors);
	
//	imshow("Rosas", imgs[1]);
	imshow("res", res);
	waitKey(0);
}
