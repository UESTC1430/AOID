#pragma once

#include "CyCameraConnection.h"
#include "CyDalsaSpyderMono1or2KGigECamera.h"
#include "CyGrabberExtension.h"
#include "CyDisplayEx.h"
#include <conio.h>
#include <time.h>

#define  IMAGE_WIDTH  2000  //默认扫描一次图像的宽度
#define  IMAGE_HEIGHT 4000  //默认扫描一次图像的高度

class Camera
{
public:
	Camera(void);
	~Camera(void);

	CyCameraConnection camCon;
	CyDalsaSpyderMono1or2KGigECamera *camera;
	unsigned char *tempBuffer;//内存指针1
	unsigned char *tempBuffer2;//内存指针2

	Mat img_sweep;//存放X移动拼接好的图片4096,480*10，在初始化时修改大小；
	Mat img_sweep_change;//img_sweep的翻面图像
	Mat img_sweep_temp;//一副图采集超界时用的第二幅临时图片
	Mat img_auto_focus;//自动对焦图片
	int imagenum;//采集单幅图像时拼接图像的个数
	unsigned long height;
	unsigned long width;
	bool GetConnect();//摄像头的连接
	bool GetOnePicture();//获取摄像头默认大小的图片
	bool GetPicture();//获取系统默认大小的图片
	bool CloseCamera();//关闭摄像头
};


