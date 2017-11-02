// ColorSpaceReduction.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include"stdafx.h"
#include<iostream>  
#include<opencv2/opencv.hpp>  

using namespace std;
using namespace cv;

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table);
void timetestway1(Mat& I, const uchar* const table);
void timetestway2(Mat& I, const uchar* const table);
void timetestway3(Mat& I, const uchar* const table);

int main(int argc, char **argv)
{
	const char* filename = "input.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	/*imshow("source", srcImg);
	waitKey(0);*/

	
	//�ռ�����table
	int divideWith = 10;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
	{
		table[i] = divideWith* (i / divideWith);
	}
		timetestway1(srcImg,table);
		timetestway2(srcImg, table);
		timetestway3(srcImg, table);
	system("pause");
	return 0;
}

void timetestway1(Mat& I, const uchar* const table)
{
	double t;
	t = static_cast<double>(getTickCount());
	for (int i = 1; i < 100; i++)
	{
		ScanImageAndReduceC(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "ָ�����C��������ƽ����ʱ��" << t / 100 << "s"<<endl;
}

void timetestway2(Mat& I, const uchar* const table)
{
	double t;
	t = static_cast<double>(getTickCount());
	for (int i = 1; i < 100; i++)
	{
		ScanImageAndReduceIterator(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "������iterator��ƽ����ʱ��" << t / 100 << "s" << endl;
}

void timetestway3(Mat& I, const uchar* const table)
{
	double t;
	t = static_cast<double>(getTickCount());
	for (int i = 1; i < 100; i++)
	{
		ScanImageAndReduceRandomAccess(I, table);
	}
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "��̬��ַ���㷨ƽ����ʱ��" << t / 100 << "s" << endl;
}

//��Ч�ķ�������ָ����ʣ�C������[ ]��ʱ�㷨
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	int channels = I.channels();
	int nRows = I.rows;
	int nCols = I.cols* channels;  //ÿ�е�Ԫ�ظ���
	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	int i, j;
	uchar* p;
	//˫��ѭ����������������ֵ
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);   //��ȡ��i�е��׵�ַ
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}

//��̬��ַ�����ʱ�㷨
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}
	return I;
}

//������iterator����ʱ�㷨
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));
	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;

		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}
	return I;
}
