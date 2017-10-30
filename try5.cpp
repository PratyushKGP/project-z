#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
typedef struct
{
  int x;
  int y;
}coordi;

struct Node {
   // vector<Node *> children;
    //Node *parent;
    coordi position;
};

Node start_node;
Node end_node;
Mat image;
int a[100],b[100];
int k=0,z=0,c=0,d=0;
int n, sum1=0, sum2=0;

void init()
{
    start_node.position.x = 0;
    start_node.position.y = 0;
    for(int i=0; i <450; i++)
    {
      for(int j=0; j <450 ; j++)
      {

       if(image.at<Vec3b>(i, j)[0] ==0 && image.at<Vec3b>(i, j)[1] ==255 && image.at<Vec3b>(i, j)[2] == 0)
        {
         a[k]=i;
         b[k]=j;
          k++;
        }
      }
    }
    n=k;
    for(c=0; c<n; c++)
    {
     sum1=sum1 + a[c];
     sum2=sum2 + b[c];
    }
    start_node.position.x = sum1*1.0/n;
    start_node.position.y = sum2*1.0/n;
   
    end_node.position.x = 0;
    end_node.position.y = 0;

    for(int i=0; i <450; i++)
    {
      for(int j=0; j <450; j++)
      {
        if(image.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[1] == 0 && image.at<Vec3b>(i, j)[2] == 255)
          {
           a[z]=i;
           b[z]=j;
            z++;
          }
      }
    }
    n=z;
    sum1=0;
    sum2=0;
    for(d=0; d<n; d++)
    {
     sum1=sum1 + a[d];
     sum2=sum2 + b[d];
    }
    end_node.position.x = sum1*1.0/n;
    end_node.position.y = sum2*1.0/n;
cout<<  end_node.position.x << "  " << end_node.position.y;
} 

int main()
{
   
    image = imread( "aa.png", IMREAD_COLOR ); 
    if( image.empty() )                    
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
cout<< image.rows << image.cols;
    init();
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", image );
    waitKey(0); 
    return 0;
}
