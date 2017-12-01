
#include<iostream>  
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

void ContrastAndBright(int, void*);
Mat grayscale(Mat& I);

Mat img = imread("input.jpg");
Mat newimg = img.clone();
//
//
//int ContrastValue = 100;
//int BrightnessValue = 0;
//
//int main()
//{
//	namedWindow("���ҶȻ����ڡ�", WINDOW_NORMAL);
//	createTrackbar("�Աȶȣ�", "���ҶȻ����ڡ�", &ContrastValue, 300, ContrastAndBright);
//	createTrackbar("���ȣ�", "���ҶȻ����ڡ�", &BrightnessValue, 255, ContrastAndBright);
//	ContrastAndBright(ContrastValue, 0);
//	ContrastAndBright(BrightnessValue, 0);
//	waitKey(0);
//	return 0;
//}
//
//void ContrastAndBright(int, void*)
//{
//	for (int i = 0; i<img.rows; ++i)
//	{
//		for (int j = 0; j<img.cols; ++j)
//		{
//			for (int c = 0; c<3; c++)
//			{
//				newimg.at<Vec3b>(i, j)[c] = saturate_cast<uchar>((img.at<Vec3b>(i, j)[c] * 0.01*ContrastValue) + BrightnessValue);
//			}
//		}
//	}
//	imshow("��ԭͼ��", img);
//	imshow("���ҶȻ����ڡ�", newimg);
//}

int main()
{
	int x1, y1, x2, y2;
	cout << "����յ�A���꣺" << endl;
	cin >> x1 >> y1;
	cout << "����յ�B���꣺" << endl;
	cin >> x2 >> y2;
	uchar table[256];
	for (int i = 0; i < 256; ++i)
	{
		if (i < x1)
			table[i] = (y1 / x1) * i;
		else if (x1 < i && i < x2)
			table[i] = (y2 - y1) / (x2 - x1)*i + y1;
		else if (i > x2)
			table[i] = ((255-y2) / (255-x2))*i + y2;
	}
	for (int i = 0; i<img.rows; ++i)
	{
		for (int j = 0; j<img.cols; ++j)
		{
			for (int c = 0; c<3; c++)
			{
				newimg.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(table[(img.at<Vec3b>(i, j)[c])]);
			}
		}
	}
	imshow("��ԭͼ��", img);
	imshow("���ҶȻ����ڡ�", newimg);
	waitKey(0);
}

//int main()
//{
//	Mat img = imread("input.jpg");
//	Mat Img = grayscale(img);
//	uchar table[256];
//	for (int i = 0; i < 256; ++i)
//	{
//			table[i] = 40*log(1+i);
//	}
//	for (int i = 0; i<Img.rows; ++i)
//	{
//		for (int j = 0; j<Img.cols; ++j)
//		{
//			Img.at<uchar>(i, j) = saturate_cast<uchar>(table[(Img.at<uchar>(i, j))]);
//		}
//	}
//	imshow("���ҶȻ����ڡ�", Img);
//	imshow("��ԭͼ���ڡ�", img);
//	waitKey(0);
//}
//
//Mat grayscale(Mat& I)
//{
//	int channels = I.channels();
//	int nRows = I.rows;
//	int nCols = I.cols;  //ÿ�е�Ԫ�ظ���
//
//	Mat GrayscaleImg(nRows, nCols, CV_8UC1);
//	int i, j, k;
//	//˫��ѭ����������������ֵ
//	for (i = 0; i < nRows; ++i)
//	{
//		for (j = 0, k = 0; j < nCols; ++j, k = k + 3)
//		{
//			GrayscaleImg.at<uchar>(i, j) = (int)( I.at<Vec3b>(i, j)[0] * 0.11 + I.at<Vec3b>(i, j)[1]*0.59 + I.at<Vec3b>(i, j)[2] * 0.30);
//		}
//	}
//	return GrayscaleImg;
//}