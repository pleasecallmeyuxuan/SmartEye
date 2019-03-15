#pragma once

#include <QThread>
#include <opencv2/opencv.hpp>
#include <string>
#include <QMetaType>
#include<qdebug.h>

#include "TinySocket.h"
#include "Depthprocess.h"
#include "PCLConvert.h"

class DCam : public QThread
{
	Q_OBJECT

public:
	DCam(QObject *parent);
	DCam();
	DCam(std::string ip, int port);
	~DCam();
	void setRun(bool isRun);				//设置线程停止
	void setNet(std::string ip, int port);	//设置相机IP，端口
	void setPointcloudConvert(bool isConvert);	//设置点云显示
	void setCameraParameters(double fx, double fy, double cx, double cy, double k1, double k2, double p1, double p2, double k3);	//设置相机内参、畸变系数
	int setrealtemperature(char *buf);    //获取相机温度
	bool getRunState();						//获取运行状态

signals:
	void getImage(cv::Mat,int);				//获取图像后信号,Mat格式传回图像信息，int传回是否是图像0不是图像，1是图像，-1异常
	void getPointCloud(PointCloudT::Ptr);	//获取点云信号

protected:
	void run();				//继承自QThread，线程运行函数

private:
	Imagedepthprocess g_depthprocess;	//原始图像处理类
	CTinySocket	g_Tcpsocket;			//SOCKET类
	PCLConvert	g_pclConvert;			//点云转换使用
	bool isRun = false;					//是否运行
	bool isPointCloudConvert = false;	//是否点云转换
	std::string ip = "192.168.7.2";		//相机IP
	int port = 50660;					//相机端口
	int g_TempReadDelay = 0;                 //获取相机温度延迟信号
	int g_TempReadEnable = 0;                //获取相机温度信号
	char* send_distance = "getDistanceSorted";   //发送获取深度数据指令
	char* send_temp = "getTemperature";//发送获取温度数据指令
	ushort	realTempChip;		//温度
	ushort	realTempBoard1;
	ushort	realTempBoard2;

};

