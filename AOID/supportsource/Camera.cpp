#include "StdAfx.h"
#include "Camera.h"
UINT PutPicture(LPVOID pParam);//数据取出线程1
UINT PutPicture2(LPVOID pParam);//数据取出线程2

Camera::Camera(void)
{
	img_auto_focus=Mat::zeros(480,4096,CV_8UC1);//(rows,cols)
	img_sweep_change=Mat::zeros(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC1);
	img_sweep=Mat::zeros(IMAGE_HEIGHT,IMAGE_WIDTH,CV_8UC1);
}


Camera::~Camera(void)
{
}


bool Camera::GetConnect()
{
	if ( camCon.Open("13053435")!=TRUE )
	{
		MessageBox(NULL,_T("摄像头连接失败"),_T("错误"),MB_OK);
		return FALSE;
	}
	camera = (CyDalsaSpyderMono1or2KGigECamera  *)camCon.GetCamera();
	CyGrabber *grabber = camera->get_Grabber();
	camera->get_GPIOSelector().set_Value(eGPIOSelector_Line0);                           
	camera->get_SignalInputFormat().set_Value(eSignalFormat_TTL);
	// Set Exposure mode
	camera->get_ExposureMode().set_Value(eExposureMode_Maximum);
	camera->get_LineTriggerMode().set_Value(eLineTriggerMode_External);
	// Set LUT
	CyAssert(grabber->GetDevice().HasExtension( CY_DEVICE_EXT_GPIO_LUT ));
	CyString program = "Q4 = i0";

	CyDeviceExtension &ext = grabber->GetDevice().GetExtension(CY_DEVICE_EXT_GPIO_LUT);
	ext.SetParameter( CY_GPIO_LUT_PARAM_GPIO_LUT_PROGRAM, program ); 
	ext.SetParameter( CY_GPIO_LUT_PARAM_INPUT_CONFIG0, 0); // Set the first entry in the signal routing block to Input line 0

	return TRUE;
}

bool Camera::GetPicture()
{
	CyUserBuffer userBuffer(NULL, 0);
	CyUserBuffer userBuffer2(NULL,0);

	camera->AllocateBuffer(userBuffer);
	camera->AllocateBuffer(userBuffer2);
	tempBuffer=userBuffer.GetBuffer();
	tempBuffer2=userBuffer2.GetBuffer();

	CyGrabber* grabber = camera->get_Grabber();

	CyResult res=CY_RESULT_OK;

    imagenum=0;	
    width = camera->get_SizeX().get_Value();
    height = camera->get_SizeY().get_Value();
	while ( res == CY_RESULT_OK&&imagenum<11)
	{
		if (0==imagenum%2)//图片数为偶数
		{
			CyResultEvent &evnt = userBuffer.GetCompletionEvent();
			grabber->Grab( CyChannel(0), userBuffer, CY_GRABBER_FLAG_NO_WAIT );
			bool done=false;
			while (!done)
			{
				res = evnt.WaitUntilSignaled(1000);
				if( res == CY_RESULT_TIMEOUT )
				{
					MessageBox(NULL,_T("图像采集超时"),_T("错误"),MB_OK);
				} 
				else 
				{
					done = true;
					if( res != CY_RESULT_OK ) 
					{
						MessageBox(NULL,_T("图像获取时运动结束"),_T("提示"),MB_OK);
						return FALSE;
					}
					else
					{
						imagenum++;
						CWinThread *PutPictureThread= AfxBeginThread(PutPicture,this);
					}
				}
			}
		}
		else//图片数为奇数
		{
			CyResultEvent &evnt2 = userBuffer2.GetCompletionEvent();  
			grabber->Grab( CyChannel(0), userBuffer2, CY_GRABBER_FLAG_NO_WAIT );
			bool done=FALSE;
			while (!done)
			{
				res = evnt2.WaitUntilSignaled(100);
				if( res == CY_RESULT_TIMEOUT )
				{
					MessageBox(NULL,_T("图像采集超时"),_T("错误"),MB_OK);
				} 
				else 
				{
					done = true;
					if( res != CY_RESULT_OK ) 
					{
						MessageBox(NULL,_T("图像获取时运动结束"),_T("提示"),MB_OK);
						return FALSE;
					}
					else
					{
						imagenum++;
						CWinThread *PutPictureThread2= AfxBeginThread(PutPicture2,this);
					}
				}
			}
		}

	}	
	grabber->AbortGrab(CyChannel(0));
	camera->FreeBuffer(userBuffer);
	camera->FreeBuffer(userBuffer2);
	return TRUE;
} 

bool Camera::GetOnePicture()
{
	CyUserBuffer userBuffer(NULL, 0);
	camera->AllocateBuffer(userBuffer);
	unsigned char*tempBuffer=userBuffer.GetBuffer();
	CyGrabber*grabber = camera->get_Grabber();
	CyResult res=CY_RESULT_OK;
	width = camera->get_SizeX().get_Value();
	height = camera->get_SizeY().get_Value();
	CyResultEvent &evnt = userBuffer.GetCompletionEvent();
	grabber->Grab( CyChannel(0), userBuffer, CY_GRABBER_FLAG_NO_WAIT );	
	bool done=false;
	while (!done)
	{
		res = evnt.WaitUntilSignaled(1000);
		if( res == CY_RESULT_TIMEOUT )
		{
			MessageBox(NULL,_T("图像获取超时"),_T("错误"),MB_OK);
			return FALSE;
		} 
		else 
		{
			done = true;
			if( res != CY_RESULT_OK ) 
			{
				MessageBox(NULL,_T("图像获取失败"),_T("错误"),MB_OK);
				return FALSE;

			}			
		}

	}
	for (int i=0;i<(int)height;i++)
	{
		for (int j=0;j<(int)width;j++)
		{
			img_auto_focus.at<unsigned char>(i,j)=(unsigned char)(tempBuffer[ i*width+j]);
		}
	}
	grabber->AbortGrab(CyChannel(0));
	camera->FreeBuffer(userBuffer);
	return true;
}

bool Camera::CloseCamera()
{

	if ( true == camCon.Disconnect())
	{
		return TRUE;
	}
	else
	{
		return  FALSE;
	}
}

UINT PutPicture(LPVOID pParam)
{
	Camera *pwnd=(Camera*)pParam;
	int xoffset=((pwnd->imagenum)-1)*(pwnd->height);
	int iMax=(int)pwnd->height;
	int jMax=(int)pwnd->width;
	int joff=(int)((pwnd->width)/2-IMAGE_WIDTH/2);
	for (int i=0;i<iMax;i++)
	{
		for (int j=0;j<IMAGE_WIDTH;j++)
		{
			pwnd->img_sweep.at<unsigned char>(i+xoffset,j)=(unsigned char)(pwnd->tempBuffer[ i*jMax+j+joff]);
			pwnd->img_sweep_change.at<unsigned char>(i+xoffset,IMAGE_WIDTH-1-j)=(unsigned char)(pwnd->tempBuffer[ i*jMax+j+joff]);
		}
	}
	return TRUE;
}

UINT PutPicture2(LPVOID pParam)
{
	Camera *pwnd=(Camera*)pParam;
	int xoffset=((pwnd->imagenum)-1)*(pwnd->height);
	int iMax=(int)pwnd->height;
	int jMax=(int)pwnd->width;
	int joff=(int)((pwnd->width)/2-IMAGE_WIDTH/2);
	for (int i=0;i<iMax;i++)
	{
		for (int j=0;j<IMAGE_WIDTH;j++)
		{
			pwnd->img_sweep.at<unsigned char>(i+xoffset,j)=(unsigned char)(pwnd->tempBuffer2[ i*jMax+j+joff]);
			pwnd->img_sweep_change.at<unsigned char>(i+xoffset,IMAGE_WIDTH-1-j)=(unsigned char)(pwnd->tempBuffer2[ i*jMax+j+joff]);
		}
	}
	return TRUE;
}

