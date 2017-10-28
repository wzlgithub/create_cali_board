#ifndef IMAGE_PROJECTOR_H
#define IMAGE_PROJECTOR_H

#include <stdint.h>
#include <opencv2/opencv.hpp>

class ImageProjector
{
public:	
	/* intrinsic			内参矩阵（double类型）
	 * distortion			畸变向量（double类型）
	 * extrinsicR			外参旋转矩阵（double类型）
	 * extrinsicT			外参平移矩阵（double类型）
	 * srcImageWidth		原始图像宽度（4的倍数）
	 * srcImageHeight		原始图像高度（4的倍数）
	 * projImageWidth		投影图像宽度（4的倍数）
	 * projImageHeight		投影图像高度（4的倍数）
	 * worldRangeWidth		世界坐标系范围宽度
	 * worldRangeHeight		世界坐标系范围高度
	 * projImageROIWidth	投影图像ROI宽度（不指定时等于projImageWidth）
	 * projImageROIHeight	投影图像ROI高度（不指定时等于projImageHeight）*/
	ImageProjector(const cv::Mat& intrinsic, const cv::Mat& distortion, const cv::Mat& extrinsicR, const cv::Mat& extrinsicT, int srcImageWidth, int srcImageHeight, int projImageWidth, int projImageHeight, double worldRangeWidth, double worldRangeHeight, int projImageROIWidth = -1, int projImageROIHeight = -1);
	~ImageProjector();

	/* distort_point	畸变点
	 * undistort_point	去畸变点
	 * world_point		世界点
	 * project_point	投影点*/
	//畸变点转世界点(z = 0)
	void distort2worldPoint(const cv::Point2d& distort_point, cv::Point3d* world_point);
	//畸变点转去畸变点
	void distort2undistortPoint(const cv::Point2d& distort_point, cv::Point2d* undistort_point);
	//畸变点转投影点
	void distort2projectPoint(const cv::Point2d& distort_point, cv::Point2d* project_point);
	//去畸变点转畸变点
	void undistort2distortPoint(const cv::Point2d& undistort_point, cv::Point2d* distort_point);
	//去畸变点转投影点
	void undistort2projectPoint(const cv::Point2d& undistort_point, cv::Point2d* project_point);
	//世界坐标转投影点(z = 0)
	void world2projectPoint(const cv::Point3d& world_point, cv::Point2d* project_point);
	//投影点转去畸变点
	void project2undistortPoint(const cv::Point2d& project_point, cv::Point2d* undistort_point);
	//投影点转畸变点
	void project2distortPoint(const cv::Point2d& project_point, cv::Point2d* distort_point);
	//投影点转世界坐标(z = 0)
	void project2worldPoint(const cv::Point2d& project_point, cv::Point3d* world_point);

	/* 计算投影图像
	 * srcImg			IN	原始图像
	 * projImg			OUT	投影图像
	 * centerDistortLoc	IN	投影图ROI中心点在畸变图中的坐标（不指定时该点在投影图的中心）
	 * oriProjLoc		OUT	投影图的起始点*/
	void projectImage(const cv::Mat& srcImg, cv::Mat& projImg, const cv::Point2d centerDistortLoc = cv::Point2d(-1, -1), cv::Point oriProjLoc = cv::Point());

private:
	struct InterLinearTable
	{
		uint16_t x;
		uint16_t y;
		uint16_t a;
		uint16_t b;
	};

	void GetXYGivenZ(const double u, const double v, const double Z, double* X, double* Y);
	void calcObjCoeffs();
	void generateProjTable();

	double fx;
	double fx_;
	double fy;
	double fy_;
	double cx;
	double cy;
	double k1;
	double k2;
	double exParamR[9];
	double exParamR_[9];
	double exParamT[3];
	
	int srcWidth;
	int srcHeight;
	int projWidth;	
	int projHeight;
	double worldWidth;
	double worldHeight;
	int projROIWidth;
	int projROIHeight;
	int projWidth_2;
	int projHeight_2;
	int projROIWidth_2;
	int projROIHeight_2;
	
	double coeffs_x;
	double coeffs_y;
	double proj_ratio_x;
	double proj_ratio_x_;
	double proj_ratio_y;
	double proj_ratio_y_;

	InterLinearTable* proj_table;
};

#endif
