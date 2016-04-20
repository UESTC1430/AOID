
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#define _ATL_APARTMENT_THREADED 
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS     


#define _AFX_ALL_WARNINGS
#include "winpara.h"
#include <afxwin.h>        
#include <afxext.h>         


#include <afxdisp.h>        



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             
#endif 

#include <afxcontrolbars.h>    


#include "AOIDtype.h"

//*****************************************************ͼƬ����OPENCVͷ�ļ�

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

#include <opencv2/stitching/stitcher.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>

#define  PI 3.14159

using namespace cv;











#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
