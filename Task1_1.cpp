#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<math.h>
#include<queue>

using namespace std;
using namespace cv;
Mat image = imread("aa.png",IMREAD_COLOR);
int R = image.rows, C = image.cols;
struct cord
{
  Point pos;
  long int priority;
  cord *parent;
}*curr, *next;

class PathPlanner
  {
  public:
    PathPlanner(Point s, Point e, Mat ob, string pl_method)
    {
      start= new cord; en=new cord;
      start->pos=s;
      en->pos=e;
      start->parent=NULL;
      obstacle=ob.clone();
      planning_method=pl_method;
    }
    void getpath()
    {
         BFS();
    }
    void BFS();
  private:
    cord *start,*en;
    Mat obstacle  ;
    string planning_method;
    long int total_point_traversed;
    long int path_length;
  };

  void PathPlanner::BFS(void)
  {
     total_point_traversed=1;
     path_length=1;
     curr= new cord; int flag=0;
     Mat mark(obstacle.rows,obstacle.cols,CV_8UC1,Scalar(0));
     queue<cord *> q;
     curr=start;
     cout<<" inside="<<curr->pos.x<<" "<<curr->pos.y<<endl;
     q.push(curr);
 int p=0;
     while(!q.empty()&&flag==0)
     {
       q.pop();
       //cout<<" in while loop\n\n";
       for(int i=-1;i<=1;i++)
       for(int j=-1;j<=1;j++)
       {
         if(curr->pos.y+i<R&&curr->pos.x+j<C&&curr->pos.y+i>=0&&curr->pos.x+j>=0)
           if(mark.at<uchar>(curr->pos.y+i,curr->pos.x+j)!=255&&obstacle.at<uchar>(curr->pos.y+i,curr->pos.x+j)!=255)
           {

             next=new cord;
             next->pos.x=curr->pos.x+j;
             next->pos.y=curr->pos.y+i;
             //cout<<"curr pos: "<<next->pos.x<<","<<next->pos.y<<"    \n";
             total_point_traversed++;
             if(next->pos==en->pos)
              {
                en->parent=curr;
                cout<<"got the end"<<" "<<en->pos.x<<","<<en->pos.y<<endl;
                flag=1;
              }
             next->parent=curr;
             //if(p++<10)
             q.push(next);
             mark.at<uchar>(next->pos.y,next->pos.x)=255;
           }

       }
       if(!q.empty())
       curr=q.front();
     }
     if(q.empty())
     cout<<" Queue is empty";
     curr=en;
     while(curr!=NULL)
     {
       obstacle.at<uchar>(curr->pos.y,curr->pos.x)=255;
       curr=curr->parent;
       path_length++;
     }
     imshow("imageBFS",obstacle);
     imshow("mark",mark);
     //cout<<" \n end pos="<<en->pos.x<<","<<en->pos.y<<endl;
     cout<<"total_point_traversed="<<total_point_traversed<<endl;
     cout<<"path length="<<path_length<<endl;
     waitKey(0);
  }
int main(int argc, char *argv[])
{
    Mat img = imread("aa.png", 0);
    int r = image.rows, c = image.cols; int i,j;
int red=0,green=0,sum_green_x=0, sum_green_y=0,sum_red_x=0,sum_red_y=0; 
   for (i = 0; i < r; i++)
                {
                  for ( j = 0; j < c; j++)
                     {
                         if (image.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[1] == 255 && image.at<Vec3b>(i, j)[2] == 0)
                          {  green++;
                             sum_green_y+=i;
                             sum_green_x+=j;
                          }
                         else if (image.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[1] == 0 && image.at<Vec3b>(i, j)[2] == 255)
                          {  red++;
                             sum_red_y+=i;
                             sum_red_x+=j;
                          }
                     } 
                }

int red_x=sum_red_x/red;
int red_y=sum_red_y/red;
int green_x=sum_green_x/green;
int green_y=sum_green_y/green;


cout<<"red=" <<red_x << "," << red_y << "\n";
cout<<"green=" <<green_x << "," << green_y << "\n";
namedWindow("image", WINDOW_AUTOSIZE);
imshow("image", image);




    if(img.empty())
       return -1;
    cout<<"(r,c)="<<img.rows<<","<<img.cols<<endl;
    PathPlanner obj(Point(green_x,green_y),Point(red_x,red_y),img,"BFS");
    obj.getpath();

    waitKey(0);
    return 0;
}
