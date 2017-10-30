#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
//#include <bits/stdc++.h>
using namespace cv;
using namespace std;
Mat a = imread("aa.png", 0);
int r = a.rows, c = a.cols;
Mat b(r, c, CV_8UC1, Scalar(0));
void DFS_visit(int i, int j, int ctr)
{
b.at<uchar>(i, j) = ctr;
for (int k = i - 1; k < i + 2; k++)
{
for (int l = j - 1; l < j + 2; l++)
{
if (a.at<uchar>(k, l) == 255 && b.at<uchar>(k, l) == 0)
{
DFS_visit(k, l, ctr);
}
}
}
}
int main()
{
for (int i = 0; i < r; i++)
{
for (int j = 0; j < c; j++)
{
b.at<uchar>(i, j) = 0;
}
}
int sumx[5];
int sumy[5];
int num[5], gx[5], gy[5];
int ctr = 1;
for (int i = 0; i < r; i++)
{
for (int j = 0; j < c; j++)
{
if (a.at<uchar>(i, j) == 255 && b.at<uchar>(i, j) == 0)
{
DFS_visit(i, j, ctr);
ctr++;
}
}
}
namedWindow("image", WINDOW_AUTOSIZE);
imshow("image", a);
cout << "No of blobs is "<<--ctr<<"\n"<<"no of rows is"<<a.rows<<"no of cols is"<<a.cols;
for (int k = 0; k <ctr; k++)
{
sumx[k] = 0;
sumy[k] = 0;
num[k] = 0;
for (int i = 1; i < r - 1; i++)
{
for (int j = 1; j < c - 1; j++)
{
if (b.at<char>(i, j) == k)
{
sumx[k] += i;
sumy[k] += j;
num[k]++;
}
}
}
gx[k] = sumx[k] / num[k];
gy[k] = sumy[k] / num[k];
}
cout << "required centroids are at:-" << endl;
for (int i = 0; i < ctr; i++)
cout << "blob " << i << "x=" << gx[i] << "\ty=" << gy[i] << endl;
waitKey(0);
return 0;
}
