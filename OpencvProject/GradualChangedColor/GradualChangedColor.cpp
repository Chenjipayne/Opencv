
#include<iostream>  
#include<opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

int main()
{
	Mat GradualChangedColorImg(306, 306, CV_8UC3);
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 0; j < 51; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = 0;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = j * 5;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 51; j < 102; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = 0;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = 255;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = 255 - (j - 51) * 5;
		}
	}
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 102; j < 153; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = (j - 102) * 5;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = 255;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = 0;
		}
	}
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 153; j < 204; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = 255;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = 255 - (j - 153) * 5;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = 0;
		}
	}
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 204; j < 255; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = 255;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = 0;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = (j - 204) * 5;
		}
	}
	for (int i = 0; i < 306; ++i)
	{
		for (int j = 255; j < 306; ++j)
		{
			GradualChangedColorImg.at<Vec3b>(i, j)[0] = 255 - (j - 255) * 5;
			GradualChangedColorImg.at<Vec3b>(i, j)[1] = 0;
			GradualChangedColorImg.at<Vec3b>(i, j)[2] = 255;
		}
	}
	imshow("source", GradualChangedColorImg);
	waitKey(0);
	return 0;
}