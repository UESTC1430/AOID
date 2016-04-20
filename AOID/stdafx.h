
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#define _ATL_APARTMENT_THREADED 
#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
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

//*****************************************************图片处理OPENCV头文件

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
