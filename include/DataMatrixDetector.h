#ifndef DATAMATRIXDETECTOR_H
#define DATAMATRIXDETECTOR_H

#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <opencv2/opencv.hpp>

class DataMatrixDetector
{
public:
	enum ErrorCode
	{
		SUCCEED,
		COARSELOCFAILED,
		DETECTING,
		DETECTED
	};

	enum DataMatrixType
	{
		DmtxSymbolRectAuto = -3,
		DmtxSymbolSquareAuto = -2,
		DmtxSymbolShapeAuto = -1,
		DmtxSymbol10x10 = 0,
		DmtxSymbol12x12,
		DmtxSymbol14x14,
		DmtxSymbol16x16,
		DmtxSymbol18x18,
		DmtxSymbol20x20,
		DmtxSymbol22x22,
		DmtxSymbol24x24,
		DmtxSymbol26x26,
		DmtxSymbol32x32,
		DmtxSymbol36x36,
		DmtxSymbol40x40,
		DmtxSymbol44x44,
		DmtxSymbol48x48,
		DmtxSymbol52x52,
		DmtxSymbol64x64,
		DmtxSymbol72x72,
		DmtxSymbol80x80,
		DmtxSymbol88x88,
		DmtxSymbol96x96,
		DmtxSymbol104x104,
		DmtxSymbol120x120,
		DmtxSymbol132x132,
		DmtxSymbol144x144,
		DmtxSymbol8x18,
		DmtxSymbol8x32,
		DmtxSymbol12x26,
		DmtxSymbol12x36,
		DmtxSymbol16x36,
		DmtxSymbol16x48
	};

	struct DetectParams
	{
		int imgWidth;			//ͼ����
		int imgHeight;			//ͼ��߶�
		int edgeMin;			//��ά���Ե���ȼ�Сֵ��ICARRIER�·�42��IAGV 17��ICARRIER�Ϸ�32��
		int edgeMax;			//��ά���Ե���ȼ���ֵ��IAGV 200��ICARRIER 52��
		int edgeThresh;			//���ӵ��Ե�ݶ���ֵ��77��
		int edgeStopThresh;		//��Ե�յ��ݶ���ֵ��50��
		int solidContiAngRng;	//�����˶�ʱ��ʵ�߱ߵĻ���任�ĽǶ�����������Χ��15��
		int dashedContiAngRng;	//�����˶�ʱ�����߱ߵĻ���任�ĽǶ�����������Χ��2��
		DataMatrixType type;	//��ά�����ͣ�IAGV DmtxSymbolSquareAuto��ICARRIER DmtxSymbol10x10��
		int isCoarse2Fine;		//��������Ƿ�Ϊ�ֶ�λ��Ķ�ά��ͼ��0 ���ǣ���0 �ǣ�
	};

	struct CoarseLocParams
	{
		int leastGridCnt;	//��С��ͨ���������2��
		int gridSize;		//����ߴ磨30��
		int locDriftThresh;	//��ͨ�������������ƫ����ֵ��60��

		float ratio_k;
		int min_min_k;
		int min_max_k;
		int max_max_k;
	};

	struct DataMatrixInfo
	{
		double x;			//��ά��ǵ�ͼ������
		double y;			//��ά��ǵ�ͼ������
		double angle;		//��ά��ױ���x��ļнǣ����ȣ�
		char message[80];	//��ά����Ϣ
	};

	/* params1	��ά�������
	 * params2	�ֶ�λ����*/
	DataMatrixDetector(const DetectParams& params1, const CoarseLocParams& params2 = CoarseLocParams());
	~DataMatrixDetector();

	/* �ֶ�λ
	 * srcImg		IN	����ԭʼͼ��
	 * centerLoc	OUT	��ά�����ĵ���������*/
	ErrorCode coarseLoc(const cv::Mat& srcImg, cv::Point2d* centerLoc);

	/* ������������
	 * srcImg			IN	ԭʼͼ��
	 * continuousAction	IN	ԭʼͼ��*/
	void detect(const cv::Mat& srcImg, bool continuousAction = true);

	/* ֹͣ���*/
	void abort();

	/* ��ȡ���¼����
	 * dmInfo	OUT	�����
	 * ����ֵ		����Ƿ��ѽ���*/
	ErrorCode getDetectInfo(std::vector<DataMatrixInfo>& dmInfo);

	/* �������㣬��������Ұ��С����ά��ߴ����Ϣ�����仯ʱ
	* objecject_size	ʵ����Ұ��Χ����λΪmm
	* dm_obj_size		ʵ�ʶ�ά��ߴ磬��λΪmm
	* label_obj_size	ʵ�ʱ�ǩ�ߴ磬��λΪmm
	* best_param		��ѷֱ��ʣ���λΪ����/mm*/
	void calc_param(const double object_size, const double dm_obj_size, const double label_obj_size, const double best_param);
	
private:
	enum DetectState
	{
		IDLE,
		READY,
		BUSY,
		ABORT = -1
	};

	void detectLoop();

	DetectParams dp;
	CoarseLocParams clp;
	cv::Mat procImg;
	void* cacheBuf;
	void* outlineBuf;
	int bufLen;
	int outlineBufLen;
	int16_t lastBottomAng;
	DetectState ds;
	bool keepRunning;
	std::vector<DataMatrixInfo> dmResults;

	std::thread detectThread;
	std::mutex detectStateMtx;
	std::mutex getResultsMtx;
	std::condition_variable detectProcFinishedCS;
	std::condition_variable detectDataReadyCS;
};


#endif