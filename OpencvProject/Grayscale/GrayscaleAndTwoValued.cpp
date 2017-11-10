// Grayscale.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>  
#include<opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

Mat grayscale(Mat& I);
Mat twovalue(Mat& I);

int main()
{
	Mat grayscaleImg;
	const char* filename = "input.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	int channels = srcImg.channels();
	int nRows = srcImg.rows;
	int nCols = srcImg.cols;  //ÿ�е�Ԫ�ظ���

	//�ҶȻ�
	grayscaleImg = grayscale(srcImg);
	imshow("source", grayscaleImg);
	waitKey(0);
    return 0;

	//��ֵ��
	/*grayscaleImg = twovalue(srcImg);
	imshow("source", grayscaleImg);
	waitKey(0);
	return 0;*/
}


Mat grayscale(Mat& I)
{
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols;  //ÿ�е�Ԫ�ظ���
	
	Mat GrayscaleImg(nRows, nCols, CV_8UC1);
	int i, j,k;
	//˫��ѭ����������������ֵ
	for (i = 0; i < nRows; ++i)
	{
		for (j = 0,k = 0; j < nCols; ++j,k = k+3)
		{
			GrayscaleImg.ptr(i)[j] = (int)(I.ptr(i)[k] * 0.11 + I.ptr(i)[k+1] * 0.59 + I.ptr(i)[k+2] * 0.30);
			//GrayscaleImg.at<uchar>(i, j) = (int)( I.at<Vec3b>(i, j)[0] * 0.11 + I.at<Vec3b>(i, j)[1]*0.59 + I.at<Vec3b>(i, j)[2] * 0.30);
			//cout <<(int)( I.at<Vec3b>(i, j)[0] * 0.11 + I.at<Vec3b>(i, j)[1]*0.59 + I.at<Vec3b>(i, j)[2] * 0.30) << " ";
		}
	}
	return GrayscaleImg;
}

Mat twovalue(Mat& I)
{
	int nRows = I.rows;
	int nCols = I.cols;
	Mat Twovalue(nRows, nCols, CV_8UC1);

	I = grayscale(I);
	for (int i = 0; i < nRows; ++i)
	{
		for (int j = 0; j < nCols; ++j)
		{
			if (I.ptr(i)[j] < 105)
			{
				Twovalue.ptr(i)[j] = 0;
			}
			else
			{
				Twovalue.ptr(i)[j] = 255;
			}
		}
	}
	return Twovalue;
}