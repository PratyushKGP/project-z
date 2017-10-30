//getting aa image
#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
    Mat image;
    image = imread( "aa.png", IMREAD_COLOR ); 
    if( image.empty() )                    
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    namedWindow( "Display window", WINDOW_AUTOSIZE );
    imshow( "Display window", image );
    waitKey(0); 
    return 0;
}
