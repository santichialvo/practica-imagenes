#ifndef HOUGH_H
#define HOUGH_H

typedef unsigned int uint;

int w,h,accu_h,accu_w;
uint * accu;
double hough_h;

int Hough_Transform(Mat img)
{
	w = img.cols;
	h = img.rows;
	hough_h = ((sqrt(2.0) * (double)(h>w?h:w))/2.0);
	accu_h = hough_h * 2.0; // -r -> +r
	accu_w = 180;
	
	accu = new uint[accu_h*accu_w];
	
	double center_x = w/2; 
	double center_y = h/2;
	
	for(int i=0;i<h;i++) { 
		for(int j=0;j<w;j++) { 
			if(img.at<uchar>(i,j) > 250)
			{
				for(int t=0;t<180;t++) 
				{
					double r = (((double)j - center_x) * cos((double)t * M_PI/180.)) + (((double)i - center_y) * sin((double)t * M_PI/180.));
					accu[ (int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Hough_GetLines(int threshold, int minangle = 0, int maxangle = 180)
{
	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;
	
	if (accu == 0)
		return lines;
	
	Mat accuImg(accu_h,accu_w,CV_8U);
	
	for(int r=0;r<accu_h;r++)
	{
		for(int t=0;t<accu_w;t++)
		{
			accuImg.at<uchar>(r,t) = 5*uchar(accu[(r*accu_w) + t]);
			if((int)accu[(r*accu_w) + t] >= threshold)
			{
				//Is this point a local maxima (9x9)
				int max = accu[(r*accu_w) + t];
				for(int ly=-4;ly<=4;ly++)
				{
					for(int lx=-4;lx<=4;lx++)  
					{  
						if( (ly+r>=0 && ly+r<accu_h) && (lx+t>=0 && lx+t<accu_w) )  
						{  
							if( (int)accu[( (r+ly)*accu_w) + (t+lx)] > max )  
							{ 
								max = accu[( (r+ly)*accu_w) + (t+lx)];  
								ly = lx = 5;  
							} 
						}
					}
				}
				if(max > (int)accu[(r*accu_w) + t])  
					continue;
				
				int x1, y1, x2, y2;  
				x1 = y1 = x2 = y2 = 0;  
				
				if(t >= 45 && t <= 135)  
				{  
					//y = (r - x cos(t)) / sin(t)  
					x1 = 0;  
					y1 = ((double)(r-(accu_h/2)) - ((x1 - (w/2) ) * cos(t * M_PI/180.))) / sin(t * M_PI/180.) + (h / 2);  
					x2 = w - 0;  
					y2 = ((double)(r-(accu_h/2)) - ((x2 - (w/2) ) * cos(t * M_PI/180.))) / sin(t * M_PI/180.) + (h / 2);
				}  
				else  
				{  
					//x = (r - y sin(t)) / cos(t);  
					y1 = 0;  
					x1 = ((double)(r-(accu_h/2)) - ((y1 - (h/2) ) * sin(t * M_PI/180.))) / cos(t * M_PI/180.) + (w / 2);  
					y2 = h - 0;
					x2 = ((double)(r-(accu_h/2)) - ((y2 - (h/2) ) * sin(t * M_PI/180.))) / cos(t * M_PI/180.) + (w / 2);  
				}
				
				t = t<90?t+180:t;
//				cout<<t<<endl;
				if (t-90>=minangle && t-90<=maxangle){
//					cout<<max<<endl;
//					cout<<r<<" "<<t<<endl;
					lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1,y1), std::pair<int, int>(x2,y2)));
				}
			}
		}
	}
//	imshow("accu",accuImg);
	std::cout << "lines: " << lines.size() << " " << threshold << std::endl;  
	return lines;  
}

#endif
