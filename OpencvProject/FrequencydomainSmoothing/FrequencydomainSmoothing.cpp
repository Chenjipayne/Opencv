// FrequencydomainSmoothing.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void ShowSpectrum(Mat input, string caption);
void ShowImage(Mat input, string caption);
void IdealFilter(Mat& input, float d0, bool flag);
void GaussianFilter(Mat&, float, bool);
void ButterworthFilter(Mat&, float, float, bool);

int main()
{
	Mat InImg = imread("lena.jpg",0);
	if (InImg.empty())
		return -1;
	imshow("原图", InImg);
	Mat OutImg = InImg.clone();
	//拓展图像以进行高效的DFT
	int h = getOptimalDFTSize(InImg.rows);
	int w = getOptimalDFTSize(InImg.cols);
	Mat img_pad; // 拓展后的图像
	if (w > InImg.cols || h > InImg.rows)
		copyMakeBorder(InImg, img_pad, 0, h - InImg.rows, 0, w - InImg.cols, BORDER_CONSTANT, Scalar::all(0));
	else
		InImg.copyTo(img_pad);

	//谱的中心化
		img_pad.convertTo(img_pad, CV_32FC1);
	for (int i = 0; i<img_pad.rows; i++)
	{
		float *ptr = img_pad.ptr<float>(i);
		for (int j = 0; j < img_pad.cols; j++)
			ptr[j] *= pow(-1.0, i + j);
	}

	//为傅立叶变换的结果(实部和虚部)分配存储空间
	Mat plane[] = { img_pad, Mat::zeros(img_pad.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg);

	//快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	ShowSpectrum(complexImg, "原频谱图");
	//ButterworthFilter(complexImg,30,2, true);		//巴特沃斯
	//IdealFilter(complexImg, 30, true);		//理想滤波
	GaussianFilter(complexImg, 30, true);		//高斯滤波
	ShowSpectrum(complexImg, "滤波后频谱图");
	//傅里叶逆变换及复原图像显示
	idft(complexImg, complexImg);
	ShowImage(complexImg, "滤波后图像");
	waitKey(0);

    return 0;
}

// 显示DFT后的频谱
void ShowSpectrum(Mat input, string caption)
{
	Mat plane[2];		//创建一个二维的Mat对象来存放傅里叶变换后的实部和虚部
	split(input, plane);		//将input的通道分离到plane中
	magnitude(plane[0], plane[1], plane[0]);		//计算幅值
	plane[0] += Scalar::all(1);
	log(plane[0], plane[0]);		//对数变换，增强细节
	normalize(plane[0], plane[0], 0, 1, CV_MINMAX);		//归一化
	cvNamedWindow(caption.c_str(), CV_WINDOW_AUTOSIZE);
	imshow(caption.c_str(), plane[0]);
}
// 显示IDFT后的复原图像
void ShowImage(Mat input, string caption)
{
	Mat plane[2];		//创建一个二维的Mat对象来存放傅里叶变换后的实部和虚部
	split(input, plane);		//将input的通道分离到plane中
	for (int i = 0; i<plane[0].rows; i++)
	{
		float *ptr = plane[0].ptr<float>(i);
		for (int j = 0; j < plane[0].cols; j++)
			ptr[j] *= pow(-1, i + j);		//逆中心化
	}
	normalize(plane[0], plane[0], 0, 1, CV_MINMAX);		//归一化
	cvNamedWindow(caption.c_str(), CV_WINDOW_AUTOSIZE);
	imshow(caption.c_str(), plane[0]);
}

//理想滤波器
void IdealFilter(Mat& input, float d0, bool flag)
{
	//参数1：DFT频谱；参数2：滤波器参数；参数3：低 / 高通标识
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			float d2 = pow(pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0),0.5);
			if (flag)
			{
				if (d2 < d0)
				{
					input.at<Vec2f>(i, j)[0] *= 1;
					input.at<Vec2f>(i, j)[1] *= 1;
				}
				else
				{
					input.at<Vec2f>(i, j)[0] *= 0;
					input.at<Vec2f>(i, j)[1] *= 0;
				}
				
			}
			else
			{
				if (d2 < d0)
				{
					input.at<Vec2f>(i, j)[0] *= 0;
					input.at<Vec2f>(i, j)[1] *= 0;
				}
				else
				{
					input.at<Vec2f>(i, j)[0] *= 1;
					input.at<Vec2f>(i, j)[1] *= 1;
				}
			}
		}
	}
}
	
//高斯滤波器
void GaussianFilter(Mat& input, float d0, bool flag)
{
	//参数1：DFT频谱；参数2：滤波器参数；参数3：低 / 高通标识
	float D0 = 2 * pow(double(d0), 2.0);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			float d2 = pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0);
			if (flag)
			{
				input.at<Vec2f>(i, j)[0] *= expf(-d2 / D0);
				input.at<Vec2f>(i, j)[1] *= expf(-d2 / D0);
			}
			else
			{
				input.at<Vec2f>(i, j)[0] *= 1 - expf(-d2 / D0);
				input.at<Vec2f>(i, j)[1] *= 1 - expf(-d2 / D0);
			}
		}
	}
}
	
//巴特沃斯滤波器
void ButterworthFilter(Mat& input, float d0,float n, bool flag)
{
	//参数1：DFT频谱；参数2 - 3：滤波器参数；参数4：低 / 高通标识
	float D0 = 2 * pow(double(d0), 2.0);
	for (int i = 0; i < input.rows; i++)
	{
		for (int j = 0; j < input.cols; j++)
		{
			float d2 = pow(pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0), 0.5);
			if (flag)
			{
				input.at<Vec2f>(i, j)[0] *= -pow(1 + pow((d2 / d0), 2 * n), -1);
				input.at<Vec2f>(i, j)[1] *= -pow(1 + pow((d2 / d0), 2 * n), -1);
			}
			else
			{
				input.at<Vec2f>(i, j)[0] *= -pow(1 + pow((d0 / d2), 2 * n), -1);
				input.at<Vec2f>(i, j)[1] *= -pow(1 + pow((d0 / d2), 2 * n), -1);
			}
		}
	}
}

