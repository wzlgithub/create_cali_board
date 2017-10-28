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

    Mat result(5600,5600,CV_8UC3,Scalar(255,255,255));

    for(int i=0;i!=10;i++)
    {
        for(int j=0;j!=10;j++)
        {
            Mat temp(result,Rect(560*i,560*j,420,420));
            int num=i*10+j;
            stringstream ss;
            string str;
            ss<<num;
            ss>>str;
            Mat dm;
            //Mat dm=imread(str+".jpg");
            createDataMatrix(dm,str,40);
            //cout<<"image type: "<<dm.type()<<endl;
            //imwrite(str+".jpg",dm);
            dm.copyTo(temp);
        }
    }

    imwrite("img.jpg",result);
    Mat board(5740,5740,CV_8UC3,Scalar(255,255,255));
    Mat temp(board,Rect(140,140,5600,5600));
    result.copyTo(temp);
    imwrite("board.jpg",board);
    cout<<"finished!"<<endl;
    imshow("board",board);
    waitKey(0);
    return 0;
}


