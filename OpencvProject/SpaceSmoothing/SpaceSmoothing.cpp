// SpaceSmoothing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void Meanblur(Mat InImg, Mat OutImg, int size);//均值滤波
void Gaussianblur(Mat InImg, Mat OutImg, int size, double sigmaX, double singmaY);//高斯滤波
void Laplaceblur(Mat InImg, Mat OutImg, Mat kernel);//拉普拉斯滤波
void Medianblur(Mat InImg, Mat OutImg, int size);//中值滤波

void Meanblur(Mat InImg, Mat OutImg, int size, bool f_overload);//均值滤波重载
void Gaussianblur(Mat InImg, Mat OutImg, int size, float sigma);//高斯滤波重载

int main()
{
	Mat InImg = imread("input.jpg");
	Mat OutImg = InImg.clone();
	//Meanblur(InImg, OutImg,5,1);//此处第三个参数传入模板的size，最后一参数为了实现重载与原函数区分，无意义
	//imshow("原图像", InImg);
	//waitKey(0);
	Gaussianblur(InImg, OutImg, 5, 1.4);
	imshow("原图像", InImg);
	waitKey(0);
	Mat kernel_3(3, 3, CV_32FC1);
	kernel_3.at<float>(0, 0) = -1;
	kernel_3.at<float>(0, 1) = -1;
	kernel_3.at<float>(0, 2) = -1;
	kernel_3.at<float>(1, 0) = -1;
	kernel_3.at<float>(1, 1) = 9;
	kernel_3.at<float>(1, 2) = -1;
	kernel_3.at<float>(2, 0) = -1;
	kernel_3.at<float>(2, 1) = -1;
	kernel_3.at<float>(2, 2) = -1;
}



void Meanblur(Mat InImg, Mat OutImg, int size, bool f_overload)//均值滤波重载
{
	int bianyuan = size / 2;
	int sum = 0;
	for (int r = 0; r < InImg.rows; r++)
	{
		for (int c = 0; c < InImg.cols; c++)
		{
			if (c < bianyuan || r < bianyuan || c > InImg.rows - 1 - bianyuan || r > InImg.rows - 1 - bianyuan)
				;//此处应为边缘处理，暂时尚未解决
			else
			{
				for (int k = 0; k < 3; k++)
				{
					for (int i = r - bianyuan; i < r + bianyuan + 1; i++)
					{
						for (int j = c - bianyuan; j < c + bianyuan + 1; j++)
						{
							sum = sum + (InImg.at<Vec3b>(i, j)[k]);
						}
					}
					OutImg.at<Vec3b>(r, c)[k] = (int)(sum / (size*size));
					//cout<< (int)(sum / (size*size))<<" ";
					sum = 0;
				}
			}
		}
	}
	imshow("均值滤波", OutImg);
}

void Gaussianblur(Mat InImg, Mat OutImg, int size, float sigma)//高斯滤波重载
{
	//定义一个二维动态数组来存放高斯模板
	int **arr = new int*[size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			arr[i][j] = 0;
		}
	}
	float siz;
	int i, j;
	siz = (size - 1) / 2;
	float **a, **b;
	a = new float*[size];
	for (int i = 0; i<size; i++)   a[i] = new float[size];
	b = new float*[size];
	for (i = 0; i<size; i++)   b[i] = new float[size];
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			a[i][j] = -siz + j;
		}
	}
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			b[i][j] = a[j][i];
		}
	}
	float h_sum = 0;
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			a[i][j] = a[i][j] * a[i][j];
			b[i][j] = b[i][j] * b[i][j];
			a[i][j] = -(a[i][j] + b[i][j]) / (2 * sigma*sigma);
			a[i][j] = exp(a[i][j]);
			if (a[i][j]<0.0001) a[i][j] = 0;
			h_sum = h_sum + a[i][j];
		}
	}
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			a[i][j] = a[i][j] / h_sum;
		}
	}
	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			arr[i][j] = int(a[i][j]*100);
			//cout << arr[i][j] << " ";
		}
	}
	int bianyuan = size / 2;
	float sum = 0;
	for (int r = 0; r < InImg.rows; r++)
	{
		for (int c = 0; c < InImg.cols; c++)
		{
			if (c < bianyuan || r < bianyuan || c > InImg.rows - 1 - bianyuan || r > InImg.rows - 1 - bianyuan)
				;//此处应为边缘处理，暂时尚未解决
			else
			{
				for (int k = 0; k < 3; k++)
				{
					for (int i = r - bianyuan, e = 0; i < r + bianyuan + 1; i++, e++)
					{
						for (int j = c - bianyuan, f = 0; j < c + bianyuan + 1; j++, f++)
						{
							sum = sum + arr[e][f]*(int)(InImg.at<Vec3b>(i, j)[k]);
						}						
					}
					OutImg.at<Vec3b>(r, c)[k] = (int)(sum / 100);
					sum = 0;
				}
			}
		}
	}
	imshow("高斯滤波", OutImg);
	//释放二维动态数组
	for (int i = 0; i < size; i++)
	{
		delete[]arr[i];
	}
	delete[]arr;
}

void Laplaceblur(Mat InImg, Mat OutImg)//拉普拉斯滤波重载
{
	imshow("拉普拉斯滤波", OutImg);
}

void Medianblur(Mat InImg, Mat OutImg)//中值滤波重载
{
	imshow("中值滤波", OutImg);
}


void Meanblur(Mat InImg, Mat OutImg, int size)//opencv自带均值滤波
{
	blur(InImg, OutImg, Size(size, size), Point(-1, -1), BORDER_DEFAULT);
	imshow("均值滤波", OutImg);
}

void Gaussianblur(Mat InImg, Mat OutImg, int size, double sigmaX, double singmaY)//opencv自带高斯滤波
{
	GaussianBlur(InImg, OutImg, Size(size, size), sigmaX, sigmaX, BORDER_DEFAULT);
	imshow("高斯滤波", OutImg);
}

void Laplaceblur(Mat InImg, Mat OutImg, Mat kernel)//opencv自带拉普拉斯滤波
{
	filter2D(InImg, OutImg, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	imshow("拉普拉斯滤波", OutImg);
}

void Medianblur(Mat InImg, Mat OutImg, int size)//opencv自带中值滤波
{
	medianBlur(InImg, OutImg, size);
	imshow("中值滤波", OutImg);
}

//********************************动态数组创建和释放***************************************
//int **filter = new int*[size+1];
//for (int i = 0; i < size + 1; i++)
//{
//	filter[i] = new int[size + 1];
//	for (int j = 0; j < size + 1; j++)
//	{
//		filter[i][j] = 0;
//	}
//}
//for (int r = 1; r < InImg.rows-1; r++)
//{
//	for (int c = 1; c < InImg.cols-1; c++)
//	{
//		for (int i = 0; i < size; i++)
//		{
//			for (int j = 0; j < size; i++)
//			{
//				filter[i][j] = InImg.at<uchar>(r, c);
//			}
//		}
//	}
//}
//
//for (int i = 0; i < size + 1; i++)
//{
//	delete[]filter[i];
//}
//delete[]filter;


/***********************************滑动条控制opencv滤波器的实现***************************************/

//Mat src;
//Mat blurSrc, gaussianSrc, medianSrc;
//
//const int b_nKwidthTrackBarMaxValue = 9;
//const int b_nKheightTrackBarMaxValue = 9;
//int b_nKwidthTrackBarValue = 1;
//int b_nKheightTrackBarValue = 1;
//int b_kernelWidthValue;
//int b_kernelHeightValue;
//
//////定义轨迹条最大值参量
//const int g_nKwidthTrackBarMaxValue = 9;
//const int g_nKheightTrackBarMaxValue = 9;
//const int g_nsigmaXTrackBarMaxValue = 5;
//const int g_nsigmaYTrackBarMaxvalue = 5;
//////定义每个轨迹条的初始值
//int g_nKwidthTrackBarValue = 1;
//int g_nKheightTrackBarValue = 1;
//int g_nsigmaXTrackBarValue = 1;
//int g_nsigmaYTrackBarValue = 1;
//int g_kernelWidthValue;
//int g_kernelHeightValue;
//
//const int m_nKsizeTrackBarMaxValue = 9;
//int m_nKsizeTrackBarValue = 1;
//
//void on_BlurTrackbar(int, void*);
//void on_GaussianBlurTrackbar(int, void*);
//void on_MedianBlurTrackbar(int, void*);
//
//int main()
//{
//	src = imread("input.jpg", 1);
//	//判断图像是否加载成功
//	if (!src.data)
//	{
//		cout << "图像加载失败!" << endl;
//		return -1;
//	}
//	else
//		cout << "图像加载成功!" << endl << endl;
//
//	imshow("原图像", src);
//
//	//均值滤波
//	namedWindow("均值滤波", WINDOW_AUTOSIZE);
//	char b_widthTrackBarName[20];
//	sprintf(b_widthTrackBarName, "width %d", b_nKwidthTrackBarMaxValue);
//	char b_heightTrackBarName[20];
//	sprintf(b_heightTrackBarName, "height %d", b_nKheightTrackBarMaxValue);
//	createTrackbar(b_widthTrackBarName, "均值滤波", &b_nKwidthTrackBarValue, b_nKwidthTrackBarMaxValue, on_BlurTrackbar);
//	on_BlurTrackbar(b_nKwidthTrackBarValue, 0);
//	createTrackbar(b_heightTrackBarName, "均值滤波", &b_nKheightTrackBarValue, b_nKheightTrackBarMaxValue, on_BlurTrackbar);
//	on_BlurTrackbar(b_nKheightTrackBarValue, 0);
//
//	//高斯滤波
//	namedWindow("高斯滤波", WINDOW_AUTOSIZE);
//	char g_widthTrackBarName[20];
//	sprintf(g_widthTrackBarName, "width %d", g_nKwidthTrackBarMaxValue);
//	char g_heightTrackBarName[20];
//	sprintf(g_heightTrackBarName, "height %d", g_nKheightTrackBarMaxValue);
//	char g_sigmaXTrackBarName[20];
//	sprintf(g_sigmaXTrackBarName, "sigmaX %d", g_nsigmaXTrackBarMaxValue);
//	char g_sigmaYTrackBarName[20];
//	sprintf(g_sigmaYTrackBarName, "sigmaY %d", g_nsigmaYTrackBarMaxvalue);
//	createTrackbar(g_widthTrackBarName, "高斯滤波", &g_nKwidthTrackBarValue, g_nKwidthTrackBarMaxValue, on_GaussianBlurTrackbar);
//	on_GaussianBlurTrackbar(g_nKwidthTrackBarValue, 0);
//	createTrackbar(g_heightTrackBarName, "高斯滤波", &g_nKheightTrackBarValue, g_nKheightTrackBarMaxValue, on_GaussianBlurTrackbar);
//	on_GaussianBlurTrackbar(g_nKheightTrackBarValue, 0);
//	createTrackbar(g_sigmaXTrackBarName, "高斯滤波", &g_nsigmaXTrackBarValue, g_nsigmaXTrackBarMaxValue, on_GaussianBlurTrackbar);
//	on_GaussianBlurTrackbar(g_nsigmaXTrackBarValue, 0);
//	createTrackbar(g_sigmaYTrackBarName, "高斯滤波", &g_nsigmaYTrackBarValue, g_nsigmaYTrackBarMaxvalue, on_GaussianBlurTrackbar);
//	on_GaussianBlurTrackbar(g_nsigmaYTrackBarValue, 0);
//
//	//中值滤波
//	namedWindow("中值滤波", WINDOW_AUTOSIZE);
//	char m_sizeTrackBarName[20];
//	sprintf(m_sizeTrackBarName, "size %d", m_nKsizeTrackBarMaxValue);
//	createTrackbar(m_sizeTrackBarName, "中值滤波", &m_nKsizeTrackBarValue, m_nKsizeTrackBarMaxValue, on_MedianBlurTrackbar);
//	on_MedianBlurTrackbar(m_nKsizeTrackBarValue, 0);
//	waitKey(0);
//	return 0;
//}
//
//void on_BlurTrackbar(int, void*)
//{
//	blur(src, blurSrc, Size(b_nKwidthTrackBarValue, b_nKheightTrackBarValue));
//	imshow("均值滤波", blurSrc);
//}
//
//void on_GaussianBlurTrackbar(int, void*)
//{
//	g_kernelWidthValue = g_nKwidthTrackBarValue * 2 + 1;
//	g_kernelHeightValue = g_nKheightTrackBarValue * 2 + 1;
//
//	GaussianBlur(src, gaussianSrc, Size(g_kernelWidthValue, g_kernelHeightValue), g_nsigmaXTrackBarValue, g_nsigmaYTrackBarValue);
//	imshow("高斯滤波", gaussianSrc);
//}
//
//void on_MedianBlurTrackbar(int, void*)
//{
//	m_nKsizeTrackBarValue = m_nKsizeTrackBarValue * 2 + 1;
//	medianBlur(src, medianSrc, m_nKsizeTrackBarValue);
//	imshow("中值滤波", gaussianSrc);
//}

/*****************************************通过OpenCV的滤波函数（filter2D）实现滤波************************************************/

//int w = 3;
//int gaussArray3[9] = { 1, 2, 1,
//2, 4, 2,
//1, 2, 1 };
//
//int gaussArray5[26] = { 1, 4, 7, 4, 1,
//4,16,26,16, 4,
//7,26,41,26, 7,
//4,16,26,16, 4,
//1, 4, 7, 4, 1 };
//
//int lapArray1[9] = { -1,-1,-1,
//-1, 9,-1,
//-1,-1,-1 };
//
//int lapArray2[9] = { 0,-1, 0,
//-1, 5,-1,
//0,-1, 0 };
//
//Mat& BlurKernel(Mat& dstKernel);
//Mat& GaussianBlurKernel(Mat& dstKernel, int arry[]);
//Mat& LapBlurKernel(Mat& dstKernel, int arry[]);
//Mat& fn(Mat& I);
//
//int main()
//{
//	Mat src = imread("input.jpg", 1);
//	if (!src.data)
//	{
//		return -1;
//	}
//	else
//		imshow("原图像", src);
//	//均值
//	Mat blur_res;
//	Mat blur_kernel(w, w, CV_32FC1);
//	BlurKernel(blur_kernel);
//	filter2D(src, blur_res, -1, blur_kernel, cvPoint(-1, -1), 0, BORDER_DEFAULT);
//	imshow("均值滤波", blur_res);
//
//	//高斯
//	Mat gauss_res;
//	Mat gauss_kernel(w, w, CV_32FC1);
//	if (w == 3)
//		GaussianBlurKernel(gauss_kernel, gaussArray3);
//	else
//		GaussianBlurKernel(gauss_kernel, gaussArray5);
//	filter2D(src, gauss_res, -1, gauss_kernel, cvPoint(-1, -1), 0, BORDER_DEFAULT);
//	imshow("高斯滤波", gauss_res);
//
//	//拉普拉斯
//	Mat lap_res;
//	Mat lap_kernel(w, w, CV_32FC1);
//	LapBlurKernel(lap_kernel, lapArray2);
//	filter2D(src, lap_res, -1, lap_kernel, cvPoint(-1, -1), 0, BORDER_DEFAULT);
//	imshow("拉普拉斯", lap_res);
//
//	waitKey();
//	return 0;
//}
//
//Mat& BlurKernel(Mat& dstKernel)
//{
//	float val = 1.0f / (float)(w*w);
//	for (int x = 0; x < w; x++)
//	{
//		for (int y = 0; y < w; y++)
//		{
//			dstKernel.at<float>(x, y) = val;
//		}
//	}
//	return dstKernel;
//}
//
//Mat& GaussianBlurKernel(Mat& dstKernel, int arry[])
//{
//	int temp = 0;
//	for (int i = 0; i < w*w; i++)
//		temp += arry[i];
//
//	int pos = 0;
//	for (int x = 0; x < w; x++)
//		for (int y = 0; y < w; y++)
//			dstKernel.at<float>(x, y) = (float)arry[pos++] / (float)temp;
//
//	return dstKernel;
//}
//
//Mat& LapBlurKernel(Mat& dstKernel, int arry[])
//{
//	int pos = 0;
//	for (int x = 0; x < w; x++)
//		for (int y = 0; y < w; y++)
//			dstKernel.at<float>(x, y) = arry[pos++];
//
//	return dstKernel;
//}