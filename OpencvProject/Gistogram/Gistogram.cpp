// Gistogram.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "math.h"
#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int get_array_max(int a[]);
void show_gistogram(Mat Img);

int main()
{
	//**********************************3通道分离实现均衡化******************************************
	/*Mat Img = imread("input2.jpg");
	Mat equalizationImg_b , equalizationImg_g, equalizationImg_r;
	Mat Img_b(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_b.at<uchar>(i,j) = Img.at<Vec3b>(i, j)[0];
		}
	}
	Mat Img_g(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_g.at<uchar>(i, j) = Img.at<Vec3b>(i, j)[1];
		}
	}
	Mat Img_r(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_r.at<uchar>(i, j) = Img.at<Vec3b>(i, j)[2];
		}
	}
	equalizeHist(Img_b, equalizationImg_b);
	equalizeHist(Img_g, equalizationImg_g);
	equalizeHist(Img_r, equalizationImg_r);
	Mat equalizationImg(Img.rows, Img.cols, CV_8UC3, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			equalizationImg.at<Vec3b>(i, j)[0] = equalizationImg_b.at<uchar>(i, j);
			equalizationImg.at<Vec3b>(i, j)[1] = equalizationImg_g.at<uchar>(i, j);
			equalizationImg.at<Vec3b>(i, j)[2] = equalizationImg_r.at<uchar>(i, j);
		}
	}
	imshow("原图", Img);
	imshow("均衡化后的图像", equalizationImg);
	show_gistogram(equalizationImg);
	waitKey(0);*/


	//*******************************转YUV实现均衡化*****************************************
	Mat Img = imread("input2.jpg");
	Mat equalizationImg_y, equalizationImg_u, equalizationImg_v;
	Mat Img_y(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_y.at<uchar>(i, j) = Img.at<Vec3b>(i, j)[2] * 0.257 + Img.at<Vec3b>(i, j)[1] * 0.504 + Img.at<Vec3b>(i, j)[0] * 0.098 + 16;
		}
	}
	Mat Img_u(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_u.at<uchar>(i, j) = - Img.at<Vec3b>(i, j)[2] * 0.148 - Img.at<Vec3b>(i, j)[1] * 0.291 + Img.at<Vec3b>(i, j)[0] * 0.439 + 128;
		}
	}
	Mat Img_v(Img.rows, Img.cols, CV_8U, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			Img_v.at<uchar>(i, j) = Img.at<Vec3b>(i, j)[2] * 0.439 - Img.at<Vec3b>(i, j)[1] * 0.368 - Img.at<Vec3b>(i, j)[0] * 0.071 + 128;
		}
	}
	equalizeHist(Img_y, equalizationImg_y);
	Mat equalizationImg(Img.rows, Img.cols, CV_8UC3, Scalar(0));
	for (int i = 0; i < Img.rows; i++)
	{
		for (int j = 0; j < Img.cols; j++)
		{
			equalizationImg.at<Vec3b>(i, j)[0] = (equalizationImg_y.at<uchar>(i, j) - 16) * 1.164 + (Img_v.at<uchar>(i, j)-128) * 1.596;
			equalizationImg.at<Vec3b>(i, j)[1] = (equalizationImg_y.at<uchar>(i, j) - 16) * 1.164 - (Img_v.at<uchar>(i, j) - 128) * 0.813 - (Img_u.at<uchar>(i, j) - 128) * 0.391;
			equalizationImg.at<Vec3b>(i, j)[2] = (equalizationImg_y.at<uchar>(i, j) - 16) * 1.164 + (Img_u.at<uchar>(i, j) - 128) * 2.018;
		}
	}
	imshow("原图", Img);
	imshow("均衡化后的图像", equalizationImg);
	show_gistogram(equalizationImg);
	waitKey(0);

	//Mat Img1 = imread("1.jpg");
	//Mat Img2 = imread("2.jpg");
	//if (Img1.rows != Img2.rows || Img1.cols != Img2.cols)
	//{
	//	cout << "两图片大小不同";
	//	return -1;
	//}
	//int rows = Img1.rows;
	//int cols = Img1.cols;
	//Mat Img3(rows, cols, CV_8U, Scalar(0));
	//Mat Img4(rows, cols, CV_8U, Scalar(0));
	//for (int i = 0; i <rows; i++)
	//{
	//	for (int j = 0; j <cols; j++)
	//	{
	//		//cout<< abs(Img1.at<Vec3b>(i, j)[1] - Img2.at<Vec3b>(i, j)[1]) <<" ";
	//		if(abs(Img1.at<Vec3b>(i, j)[1] - Img2.at<Vec3b>(i, j)[1])>40)
	//			Img3.at<uchar>(i, j) = 255;
	//		else
	//			Img3.at<uchar>(i, j) = 0;
	//	}
	//}
	//for (int k = 0; k < 10; k++)
	//{
	//	for (int i = 1; i <rows - 1; i++)
	//	{
	//		for (int j = 1; j <cols - 1; j++)
	//		{
	//			if (Img3.at<uchar>(i, j) == 255 && Img3.at<uchar>(i - 1, j) != 0 && Img3.at<uchar>(i + 1, j) != 0 && Img3.at<uchar>(i, j - 1) != 0 && Img3.at<uchar>(i, j + 1) != 0)
	//				Img4.at<uchar>(i, j) = 255;
	//			else
	//				Img4.at<uchar>(i, j) = 0;
	//		}
	//	}
	//}	
	//imshow("source", Img4);
	//waitKey(0);
}

int get_array_max(int a[])//遍历数组获取数组最大值
{
	int max = 0;
	for (int i = 0; i < 256; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	cout << max<<endl;
	return max;
}

void show_gistogram(Mat Img)//显示输入图像的直方图
{
	int channels = Img.channels();
	int rows = Img.rows;
	int cols = Img.cols;
	int maxarray;
	int graylevel_histogram[256];//创建查找表
	for (int i = 0; i < 256; i++)
	{
		graylevel_histogram[i] = 0;//初始化为全0数组
	}
	if (channels == 1)
	{
		Mat histogram1(256, 256, CV_8U, Scalar(0));
		for (int i = 0; i <rows; i++)
		{
			for (int j = 0; j <cols; j++)
			{
				graylevel_histogram[(int)(Img.at<uchar>(i, j))]++;//查找表中下标对应灰度值频数累加
			}
		}
		maxarray = get_array_max(graylevel_histogram);
		//绘制直方图
		for (int j = 0; j <256; j++)
		{
			for (int i = 0; i <256; i++)
			{
				if (i>256 - (int)(graylevel_histogram[j] * 255 * 0.9 / (1 + maxarray)))
				{
					histogram1.at<uchar>(i, j) = 255;
				}
			}
		}
		imshow("直方图", histogram1);
	}
	else if (channels == 3)
	{
		Mat histogram3(256, 768, CV_8UC3, Scalar(0));
		//Mat的B通道
		int graylevel_histogram_b[256];
		for (int i = 0; i < 256; i++)
		{
			graylevel_histogram_b[i] = 0;
		}
		for (int i = 0; i <rows; i++)
		{
			for (int j = 0; j < cols; j = j++)
			{
				graylevel_histogram_b[(int)(Img.at<Vec3b>(i, j)[0])]++;
			}
		}
		maxarray = get_array_max(graylevel_histogram_b);
		//绘制三通道图像直方图的B通道部分
		for (int j = 0; j <256; j++)
		{
			for (int i = 0; i <256; i++)
			{
				if (i>256 - (int)(graylevel_histogram_b[j] * 255 * 0.9 / (1 + maxarray)))
				{
					histogram3.at<Vec3b>(i, j)[0] = 255;
					histogram3.at<Vec3b>(i, j)[1] = 0;
					histogram3.at<Vec3b>(i, j)[2] = 0;
				}
			}
		}
		//Mat的G通道
		int graylevel_histogram_g[256];
		for (int i = 0; i < 256; i++)
		{
			graylevel_histogram_g[i] = 0;
		}
		for (int i = 0; i <rows; i++)
		{
			for (int j = 0; j < cols; j = j++)
			{
				graylevel_histogram_g[(int)(Img.at<Vec3b>(i, j)[1])]++;
			}
		}
		maxarray = get_array_max(graylevel_histogram_g);
		//绘制三通道图像直方图的G通道部分
		for (int j = 256; j <511; j++)
		{
			for (int i = 0; i <256; i++)
			{
				if (i>256 - (int)(graylevel_histogram_g[j - 255] * 255 * 0.9 / (1 + maxarray)))
				{
					histogram3.at<Vec3b>(i, j)[0] = 0;
					histogram3.at<Vec3b>(i, j)[1] = 255;
					histogram3.at<Vec3b>(i, j)[2] = 0;
				}
			}
		}
		//Mat的R通道
		int graylevel_histogram_r[256];
		for (int i = 0; i < 256; i++)
		{
			graylevel_histogram_r[i] = 0;
		}
		for (int i = 0; i <rows; i++)
		{
			for (int j = 0; j < cols; j = j++)
			{
				graylevel_histogram_r[(int)(Img.at<Vec3b>(i, j)[2])]++;
			}
		}
		maxarray = get_array_max(graylevel_histogram_r);
		//绘制三通道图像直方图的R通道部分
		for (int j = 511; j <766; j++)
		{
			for (int i = 0; i <256; i++)
			{
				if (i>256 - (int)(graylevel_histogram_r[j - 511] * 255 * 0.9 / (1 + maxarray)))
				{
					histogram3.at<Vec3b>(i, j)[0] = 0;
					histogram3.at<Vec3b>(i, j)[1] = 0;
					histogram3.at<Vec3b>(i, j)[2] = 255;
				}
			}
		}
		imshow("直方图", histogram3);
	}
}