#include <vector>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "DataMatrixCreator.h"
#include <sstream>

using namespace cv;
using namespace std;

int main()
{
	Mat dm;
    for(int i=0;i!=81;i++)
    {
        stringstream name;
        string str;
        name<<i;
        name>>str;
        cout<<str<<endl;
        createDataMatrix(dm,str,40);
        imwrite(str+".jpg",dm);
    }
    cout<<dm.size()<<endl;
    cout<<dm.type()<<endl;
	imshow("dm", dm);
	waitKey(0);

	return 0;
}
