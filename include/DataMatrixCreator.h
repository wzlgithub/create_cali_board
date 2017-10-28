#ifndef DATAMATRIXCREATOR_H
#define DATAMATRIXCREATOR_H

#include <string>
#include <opencv2/opencv.hpp>

/* ���ɶ�ά��ͼ��
 * dmImage		OUT	���ɵĶ�ά��ͼ��
 * str			IN	��ά����Ϣ
 * moduleSize	IN	�������سߴ�*/
void createDataMatrix(cv::Mat& dmImage, const std::string& str, const int& moduleSize);


#endif