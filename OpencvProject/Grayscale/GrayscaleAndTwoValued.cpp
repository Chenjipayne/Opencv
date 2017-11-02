// Grayscale.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>  
#include<opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat& I);

int main()
{
	Mat grayscaleImg;
	const char* filename = "input.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	grayscaleImg = ScanImageAndReduceC(srcImg);
	imshow("source", grayscaleImg);
	waitKey(0);
    return 0;
}
Mat& ScanImageAndReduceC(Mat& I)
{
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols;  //ÿ�е�Ԫ�ظ���
	
	Mat GrayscaleImg(I.rows, I.cols, CV_8U);
	int i, j, k;
	//˫��ѭ����������������ֵ
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0,k = 0; j < nCols; ++j)
		{
			GrayscaleImg.at<uchar>(i, j) = I.at<Vec3b>(i, j)[0] * 0.11 + I.at<Vec3b>(i, j)[1] + I.at<Vec3b>(i, j)[2];
		}
	}
	return GrayscaleImg;
}

