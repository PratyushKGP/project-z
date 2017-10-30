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
    vector<Node *> children;
    Node *parent;
    coordi position;
};

Node start_node;
Node end_node;
Mat image;
int a[100],b[100];
int k=0,z=0;
int n, sum1=0, sum2=0;

void init()
{
    start_node.position.x = 0;
    start_node.position.y = 0;
    for(int i=0; i <20; i++)
    {
      for(int j=0; j <20 ; j++)
      {

       if(image.at<Vec3b>(i, j)[0] ==0 && image.at<Vec3b>(i, j)[1] ==255 && image.at<Vec3b>(i, j)[2] == 0)
        {
         start_node.position.x = i;
         start_node.position.y = j;
        }
      }
    }
    end_node.position.x = 0;
    end_node.position.y = 0;

    for(int i=0; i <20; i++)
    {
      for(int j=0; j <20; j++)
      {
        if(image.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[1] == 0 && image.at<Vec3b>(i, j)[2] == 255)
          {
           end_node.position.x = i;
           end_node.position.y = j;
          }
      }
    }
} 

int main()
{
    Mat image;
    image = imread( "aa.png", IMREAD_COLOR ); 
    if( image.empty() )                    
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    init();
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", image );
    waitKey(0); 
    return 0;
}
