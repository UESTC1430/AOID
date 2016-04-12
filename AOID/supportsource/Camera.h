#pragma once

#include "CyCameraConnection.h"
#include "CyDalsaSpyderMono1or2KGigECamera.h"
#include "CyGrabberExtension.h"
#include "CyDisplayEx.h"
#include <conio.h>
#include <time.h>

#define  IMAGE_WIDTH  2000  //Ĭ��ɨ��һ��ͼ��Ŀ��
#define  IMAGE_HEIGHT 4000  //Ĭ��ɨ��һ��ͼ��ĸ߶�

class Camera
{
public:
	Camera(void);
	~Camera(void);

	CyCameraConnection camCon;
	CyDalsaSpyderMono1or2KGigECamera *camera;
	unsigned char *tempBuffer;//�ڴ�ָ��1
	unsigned char *tempBuffer2;//�ڴ�ָ��2

	Mat img_sweep;//���X�ƶ�ƴ�Ӻõ�ͼƬ4096,480*10���ڳ�ʼ��ʱ�޸Ĵ�С��
	Mat img_sweep_change;//img_sweep�ķ���ͼ��
	Mat img_sweep_temp;//һ��ͼ�ɼ�����ʱ�õĵڶ�����ʱͼƬ
	Mat img_auto_focus;//�Զ��Խ�ͼƬ
	int imagenum;//�ɼ�����ͼ��ʱƴ��ͼ��ĸ���
	unsigned long height;
	unsigned long width;
	bool GetConnect();//����ͷ������
	bool GetOnePicture();//��ȡ����ͷĬ�ϴ�С��ͼƬ
	bool GetPicture();//��ȡϵͳĬ�ϴ�С��ͼƬ
	bool CloseCamera();//�ر�����ͷ
};


