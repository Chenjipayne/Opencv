#include<iostream>  
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int ContrastValue;
int BrightValue;

void on_Trackbar(int, void *)
{
	
}

int main()
{
	const char* filename = "input.jpg";
	Mat srcImg = imread(filename, CV_LOAD_IMAGE_COLOR);
	if (srcImg.empty())
		return -1;
	int channels = srcImg.channels();
	int nRows = srcImg.rows;
	int nCols = srcImg.cols;  

	createTrackbar("ContrastValue", "ImageGrayLevelChange", &ContrastValue, 300, on_Trackbar);
	on_Trackbar(ContrastValue, 0);
	Mat graylevelchangeImg;
	for (int x = 0; x < srcImg.rows; x++)
	{
		for (int y = 0; y < srcImg.cols; y++)
		{
			for (int c = 0; c < 3; c++)
			{
				graylevelchangeImg.at<Vec3b>(x, y)[c] = saturate_cast<uchar>((ContrastValue*0.01)*(srcImg.at<Vec3b>(x, y)[c]) + BrightValue);
			}
		}
	}
	imshow("ImageGrayLevelChange", graylevelchangeImg);
	waitKey(0);
	return 0;
}
