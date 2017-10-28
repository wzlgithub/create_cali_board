/*************************************************************************
	> File Name: compose_dm.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年08月31日 星期四 10时13分37秒
 ************************************************************************/

#include<iostream>
#include<vector>
#include<string>
#include<iostream>
#include<opencv2/opencv.hpp>
#include"DataMatrixCreator.h"
#include<sstream>
#include<unistd.h>

using namespace std;
using namespace cv;

int main()
{
    vector<string> num_str{"0","1","2","3","4","5","6","7","8","9"};
    cout<<"please input size ,pixels(recommend 40) and space proportion(recommend 4) :"<<endl;
    cout<<"for example: 20 20 40 4"<<endl;
    int h_num,w_num,pixels,proportion;
    cin>>h_num>>w_num>>pixels>>proportion;
    Mat data_mat;
    createDataMatrix(data_mat,"00",pixels);
    int pixels_each_grid=data_mat.rows;
    int space = pixels_each_grid/proportion;
    int img_height=h_num*(pixels_each_grid+space)+space;
    int img_width =w_num*(pixels_each_grid+space)+space;
    Mat result(img_height,img_width,CV_8UC3,Scalar(255,255,255));

    for(int i=0;i!=h_num;i++)
    {
        for(int j=0;j!=w_num;j++)
        {
            Mat temp(result,Rect(pixels_each_grid*j+space*(j+1),pixels_each_grid*i+space*(i+1),pixels_each_grid,pixels_each_grid));
            int h_10=i/10;
            int h_1=i%10;
            int w_10=j/10;
            int w_1=j%10;
            string str=num_str[h_10]+num_str[h_1]+num_str[w_10]+num_str[w_1];
            Mat dm;
            //Mat dm=imread(str+".jpg");
            createDataMatrix(dm,str,pixels);
            //cout<<"image type: "<<dm.type()<<endl;
            //imwrite(str+".jpg",dm);
            dm.copyTo(temp);
        }
    }

    imwrite("img.jpg",result);
    cout<<"save successfully!"<<endl;
    return 0;
}


