#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <opencv2/legacy/blobtrack.hpp>
#include <random>

using namespace cv;
using namespace std;

Mat * imgs;

//me quedo con la zona de mayor cantidad de pixeles (aguja) y la de menor (cosito arriba del norte)
pair<int,int> big_and_small_zones(Mat &img, list<int> &colors)
{
	list<int>::iterator it;
	int nropixels;
	int colormin,colormax,min=1e20,max=-1;
	for (it=colors.begin();it!=colors.end();it++) 
	{
		
		for(int i=0;i<img.rows;i++) {
			for(int j=0;j<img.cols;j++) { 
				int aux = img.at<uchar>(i,j);
				if (aux==(*it))
					nropixels++;
			}
		}
		if (nropixels<min) { colormin = (*it); min = nropixels; }
		if (nropixels>max) { colormax = (*it); max = nropixels; }
		cout<<(*it)<<" "<<nropixels<<endl;
	}
	pair<int,int> nros(colormin,colormax);
	return nros;
}

bool isLeft(Vec2i a, Vec2i b, Vec2i c){
	return ((b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0])) > 0;
}

//dados dos puntos calcula el angulo formando lineas con el centro
float calculate_angles(Vec2i center, Vec2i pmax, Vec2i pmin)
{
	Vec2i u(pmin-center);
	Vec2i v(pmax-center);
	
	double m1 = abs(u[0]*v[0] + u[1]*v[1]); 
	double m2 = sqrt(u[0]*u[0] + u[1]*u[1]) * sqrt(v[0]*v[0] + v[1]*v[1]); 
	double cosalpha = m1/m2;
	double alpha = acos(cosalpha);
	
	if (isLeft(center,pmin,pmax))
		cout<<180 + (alpha * (180/M_PI))<<endl;
	else
		cout<<180 - (alpha * (180/M_PI))<<endl;
}


//dada la zona mayor (aguja) y menor identifico el punto que esta mas lejos del centro
//zoneA la zona grande
//zoneB la zona chica
double find_farest_pixel(Mat &img, int zoneA, int zoneB)
{
	int centerx = img.rows/2;
	int centery = img.cols/2;
	double maydist = -1;
	int mayi,mayj;
	int o=10000,e=-1,n=10000,s=-1;
	
	for(int i=0;i<img.rows;i++) { 
		for(int j=0;j<img.cols;j++) { 
			int aux = img.at<uchar>(i,j);
			if (aux==zoneA) {
				double dist = sqrt((i-centerx)*(i-centerx) + (j-centery)*(j-centery));
				if (dist>maydist)
				{
					maydist = dist;
					mayi = i;
					mayj = j;
				}
			}
			if (aux==zoneB)
			{
				if (i<o){ o = i; }
				if (i>e){ e = i; }
				if (j<n){ n = j; }
				if (j>s){ s = j; }
			}
		}
	}
	cv::circle(img,Point(mayj,mayi), 3, Scalar::all(255), -1);
	cv::circle(img,Point(centerx,centery), 3, Scalar::all(255), -1);
	cv::circle(img,Point(n+(s-n)/2,o+(e-o)/2), 3, Scalar::all(255), -1);
	cv::line(img,Point(n+(s-n)/2,o+(e-o)/2),Point(centerx,centery),Scalar::all(255));
	cv::line(img,Point(mayj,mayi),Point(centerx,centery),Scalar::all(255));
	
	Vec2i pointmax(mayj,img.rows - mayi);
	Vec2i pointmin(n+(s-n)/2,img.rows - o+(e-o)/2);
	Vec2i center(centery,centerx);
	
	cout<<center<<" "<<pointmin<<" "<<pointmax<<endl;
	
	double angle = calculate_angles(center,pointmax,pointmin);
	
	return angle;
}

Mat segmentation_sphere(Mat &img, int thres)
{
	int bdist,rdist,gdist;
	int bprom=0,gprom=0,rprom=255;
	float totaldist;
	Mat res = img.clone();
	for(int i=0;i<img.rows;i++) { 
		for(int j=0;j<img.cols;j++) { 
			bdist = (img.at<Vec3b>(i,j)[0]-bprom);
			gdist = (img.at<Vec3b>(i,j)[1]-gprom);
			rdist = (img.at<Vec3b>(i,j)[2]-rprom);
			
			totaldist = calc_dist_sphere(bdist,gdist,rdist);
			if (totaldist>thres)
				res.at<Vec3b>(i,j) = Vec3b(0,0,0);
		}
	}
	
	return res;
//	imshow("Segmentation ", res);
}

void Parcial(char** argv)
{
	imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	imgs[0] = segmentation_sphere(imgs[0],120);
	
	imshow("Imagen segmentada",imgs[0]);
	
//	Mat laplacekern3 = (Mat_<float>(3,3) << -1,-1,-1,-1, 8,-1,-1,-1,-1);
//	Mat promkern3 = create_prom_kernel(3);
//	filter2D(imgs[0], imgs[0], imgs[0].depth(), laplacekern3);
	
	imshow("Imagen filtrada",imgs[0]);
	
	Mat element = getStructuringElement(0, Size(5,5));
	Mat res;
	cvtColor(imgs[0],res,CV_BGR2GRAY);
	morphologyEx(imgs[0],imgs[0],cv::MORPH_CLOSE,element);
	
	imshow("Imagen cerrada",imgs[0]);
	
	list<int> colors;
	imgs[1] = labeling(imgs[0],colors);
	
	
//	tengo que tener 3 zonas, sino algo falla
	assert(colors.size()==3);
	
	imshow("Imagen discriminada por zonas",imgs[1]);
	
//	pair<int,int> nros = big_and_small_zones(imgs[1],colors);
	pair<int,int> nros = make_circles(imgs[1],colors);
	cout<<nros.first<<" "<<nros.second<<endl;
	find_farest_pixel(imgs[1],nros.second,nros.first);
	
	
	imshow("Imagen con puntos detectados",imgs[1]);
	
	
	waitKey(0);
}
