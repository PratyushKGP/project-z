#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include<math.h>
#include<queue>

using namespace std;
using namespace cv;
Mat image = imread("aa1.png",IMREAD_COLOR);
int r = image.rows, c = image.cols;
struct cord
{
  Point pos;
  long int priority;
  cord *parent;
}*curr ,*next;

class PathPlanner
  {
  public:
    PathPlanner(Point s, Point e, Mat ob, string pl_method)
    {
      start= new cord; en=new cord;                         //to assign new struct cord
      start->pos=s;                                         //taking pos of start and also pos is a point in 2d array
      en->pos=e;
      start->parent=NULL;
      obstacle=ob.clone();                                  // to clone the image
      planning_method=pl_method;
      cout<<" start="<<start->pos.x<<","<<start->pos.y<<"\n";
      cout<<" end="<<en->pos.x<<","<<en->pos.y<<"\n";
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

  void PathPlanner::BFS()                                   // accessing the bfs of path planner class
  {
     total_point_traversed=1;
     path_length=1;
     curr= new cord; int flag=0;                            //?
     Mat mark(obstacle.rows,obstacle.cols,CV_8UC1,Scalar(0)); //defining a new image
     queue<cord *> q;                                       //?
     curr=start;                                            // assingnig start struct to curr
     cout<<" inside="<<curr->pos.x<<","<<curr->pos.y<<endl;
     q.push(curr);                                          //pusing curr in queue
 int p=0;
     while(!q.empty()&&flag==0)
     {
       q.pop();
       for(int i=1;i>=-1;i--)
       for(int j=1;j>=-1;j--)
       {
         if(curr->pos.y+i<r && curr->pos.x+j<c && curr->pos.y+i>=0 && curr->pos.x+j>=0)
           if(mark.at<uchar>(curr->pos.y+i,curr->pos.x+j)!=255 && obstacle.at<uchar>(curr->pos.y+i,curr->pos.x+j)!=255)
           {

             next=new cord;
             next->pos.x=curr->pos.x+j;
             next->pos.y=curr->pos.y+i;
             total_point_traversed++;
             if(next->pos==en->pos)
              {
                en->parent=curr;
                cout<<"got the end"<<" "<<en->pos.x<<","<<en->pos.y<<endl;
                flag=1;
              }
             next->parent=curr;
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
     cout<<"total_point_traversed="<<total_point_traversed<<endl;
     cout<<"path length="<<path_length<<endl;
     waitKey(0);
  }
int main()
{
    Mat img = imread("aa.png", 0);
    int i,j;
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
int green_x=sum_green_x*1.0/green;
int green_y=sum_green_y*1.0/green;
cout<<"sum_green=" <<sum_green_x << "," << sum_green_y <<" greenn="<<green<< "\n";

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
