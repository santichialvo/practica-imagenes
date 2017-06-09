#include <iostream>
#include "pdi_functions.h"
#include "utils.h"
#include <math.h>
#include <cstdio>
using namespace std;

int segmentation_slider;
Mat *imgs;
int bprom,gprom,rprom;
int hprom,sprom;

void segmentation_sphere(int, void*)
{
	int bdist,rdist,gdist;
	float totaldist;
	imgs[1] = imgs[0].clone();
	for(int i=0;i<imgs[0].rows;i++) { 
		for(int j=0;j<imgs[0].cols;j++) { 
			bdist = (imgs[0].at<Vec3b>(i,j)[0]-bprom);
			gdist = (imgs[0].at<Vec3b>(i,j)[1]-gprom);
			rdist = (imgs[0].at<Vec3b>(i,j)[2]-rprom);
			
			totaldist = calc_dist_sphere(bdist,gdist,rdist);
			if (totaldist>segmentation_slider)
				imgs[1].at<Vec3b>(i,j) = Vec3b(0,0,0);
		}
	}
	
	imshow("Segmentation ",imgs[1]);
}

void segmentation_rectangle(int, void*)
{
	int hdist,sdist;
	float totaldist;
	imgs[1] = imgs[0].clone();
	for(int i=0;i<imgs[0].rows;i++) { 
		for(int j=0;j<imgs[0].cols;j++) { 
			hdist = (imgs[0].at<Vec3b>(i,j)[0]-hprom);
			sdist = (imgs[0].at<Vec3b>(i,j)[1]-sprom);
			
			totaldist = calc_dist_rect_hsv(hdist,sdist);
			if (totaldist<(segmentation_slider/2))
				imgs[1].at<Vec3b>(i,j) = Vec3b(0,0,0);
		}
	}
	
	cvtColor(imgs[1],imgs[1],CV_HSV2BGR);
	imshow("Segmentation ",imgs[1]);
}

void ejercicio4(char** argv)
{
	imgs = new Mat[3];
	imgs[0] = imread(argv[1],1);
	if (imgs[0].empty()) cout << "Error loading the image" << endl;
	
	//futbol.jpg
	int punto = 1;
	
	switch (punto)
	{
	case 1:
	{
//		Mat roi(imgs[0],Rect(131,177,50,50));
//		Mat roi(imgs[0],Rect(0,0,100,100));
//		Mat roi(imgs[0],Rect(200,580,50,50));
//		Mat roi(imgs[0],Rect(275,215,16,12));
		Mat roi(imgs[0],Rect(50,100,30,30));
		
		imshow("roi",roi);
		
//		Mat pkern3 = create_prom_kernel(12);
//		filter2D(imgs[0], imgs[0], imgs[0].depth(), pkern3);
		
//		obtengo el centro de la esfera
		bprom=gprom=rprom=0;
		for(int i=0;i<roi.rows;i++) { 
			for(int j=0;j<roi.cols;j++) { 
				bprom+=roi.at<Vec3b>(i,j)[0];
				gprom+=roi.at<Vec3b>(i,j)[1];
				rprom+=roi.at<Vec3b>(i,j)[2];
			}
		}
		bprom/=(roi.cols*roi.rows);
		gprom/=(roi.cols*roi.rows);
		rprom/=(roi.cols*roi.rows);
		
		bprom = 0;
		gprom = 0;
		rprom = 255;
		
		cout<<bprom<<" "<<gprom<<" "<<rprom<<endl;
		
		Mat * bgr = new Mat[3];
		split(roi,bgr);
		
		/// Create Windows
		namedWindow("Segmentation ", 1);
		segmentation_slider = 0;
		int segmentation_slider_max = 255;
		createTrackbar("SegTrackbar" ,"Segmentation ", &segmentation_slider, segmentation_slider_max, segmentation_sphere);
		
		/// Show some stuff
		segmentation_sphere(segmentation_slider,0);
		waitKey(0);
		break;
	}
	case 2:
	{
		
		cvtColor(imgs[0],imgs[0],CV_BGR2HSV);
//		Mat roi(imgs[0],Rect(131,177,50,50));
//		Mat roi(imgs[0],Rect(0,0,100,100));
//		Mat roi(imgs[0],Rect(200,580,50,50));
//		rosas.jpg
		Mat roi(imgs[0],Rect(295,215,16,12));
		
//		imshow("roi",roi);
		
//		Mat pkern3 = create_prom_kernel(12);
//		filter2D(imgs[0], imgs[0], imgs[0].depth(), pkern3);
		
//		obtengo el centro del rectangulo
		hprom=sprom=0;
		for(int i=0;i<roi.rows;i++) { 
			for(int j=0;j<roi.cols;j++) { 
				hprom+=roi.at<Vec3b>(i,j)[0];
				sprom+=roi.at<Vec3b>(i,j)[1];
			}
		}
		hprom/=(roi.cols*roi.rows);
		sprom/=(roi.cols*roi.rows);
		
		cout<<hprom<<" "<<sprom<<" "<<endl;
		
		/// Create Windows
		namedWindow("Segmentation ", 1);
		segmentation_slider = 0;
		int segmentation_slider_max = 255*10;
		createTrackbar("SegTrackbar" ,"Segmentation ", &segmentation_slider, segmentation_slider_max, segmentation_rectangle);
		
		/// Show some stuff
		segmentation_rectangle(segmentation_slider,0);
		waitKey(0);
		break;
	}
	
	}
}
