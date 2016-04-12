//////////////////////////////////////////////////////////////
//修改日期2013/05/23

#ifndef MAX_ADF
#define MAX_ADF
////////////////////////////////////////////////////////////////
//ATP Const
#define ATP_Tool_NUM               300  //表示刀具的数量
#define DRILL_Tool_NUM             500  
#define ATP_MagazineLine_NUM       200  //刀盘上放刀的排数
#define ATP_MagazineLifeStatus_NUM 200  //刀盘上道具使用寿命状态
#define ATP_Tolerance_NUM          16	//公差信息
#define ATP_PeckDrill_NUM          500	//分段钻类型定义
//
#define DTable_NUM                 300	//直径表项目数量定义
/////////////////////////////////
#define f_NULL -1
#define f_None 0
#define f_DXYZ 1000 	//define x&y motor zero
#define f_DZZ 1001		//define z axes motor zero
#define f_FMZ 1002		//find all axes machine zero
#define f_XYMVREL 1003
#define f_XYMVABS 1004
#define f_ZMVREL 1005
#define f_ZMVABS 1006
#define f_XYJG 1007     //连续运动
#define f_ZJG 1008       
#define f_DRL1 1009
#define f_SDRL 1010      //start drill
#define f_GPUP 1011      //Grip Move Up
#define f_GPDN 1012      //Grip Move Down
#define f_GFO 1013      //Grip Finger Open
#define f_GFC 1014      //Grip Finger Close
#define f_ACT 1015      //Auto Change Tool
#define f_TDC 1016      //Tool Depth Check
#define f_INIT 1017      //Initialize System var
#define f_SDRLF 1018


//Define Maestro Emergency Message ID
#define e_DCN 0
#define e_SND 1	//Ver16.7.3.48-2
#define e_RLS 50
#define e_FLS 51
#define e_BAL 52
#define e_GER 53
#define e_INV 54
#define e_SOT 55
#define e_PER 99
//Define Maestro Message ID
#define m_DDU 100
//直径表结构体,静态列表参数结构
typedef struct 
{
	double m_Diameter;//刀具直径
	int    ToolType;//刀具类型
	double m_SpindleSpeed;//电机转速
	double m_PlungeRate;//进刀速度
	double m_RetractRate;//出刀速度
	double m_WaitTime;//XY 轴定位后直至钻孔行程起动的等待时间
	double m_Compensate;//刀具尖角补偿参数
	double m_ToolLife;//刀具的寿命
}StaticListStruct;
//刀具动态类表参数结构
typedef struct
{
	int m_ToolUsedLife;//刀具已经使用寿命
	int m_MillingUsedLife;//铣刀使用寿命
}DynamicListStruct;
//刀具静态列表2参数
typedef struct
{
	bool m_FlagMeaD; //直径检测标志位
	bool m_FlagMeaL; //深度检测判断位
	bool m_FlagMeaR; //偏摆检测判断位
	bool m_FlagTOTO;//接触钻判断位
	bool m_FlagQuick;//快钻判断位
	bool m_FlagPeck;//激活分段钻控制位
}StaticList2Struct;
///////////////////////////
//加工文件中的刀具参数结构
typedef struct 
{
	double m_Diameter;//刀具直径
	int    ToolType;//刀具类型
	double m_SpindleSpeed;//电机转速
	double m_PlungeRate;//进刀速度
	double m_RetractRate;//出刀速度
	int	   m_Peck;//分段钻次数
	int    m_MagazineNum;//刀盘号码
	double m_Compensate;//刀具尖角补偿参数
	int    m_ToolLife;//刀具的寿命
	int iToolNumber;//文件中的刀号序号
	int iToolNumberInAtp;
	bool useflag;//文件中定义的刀具是否使用（钻孔数大于0）
}FileStaticStruct;
//刀具参数结构
typedef struct
{
	int iToolNumber;
	//静态参数
	StaticListStruct  StaticPara;
	//动态
	DynamicListStruct DynamicPara;
	//静态2-功能
	StaticList2Struct   StatePara;
	//加工文件中的刀具信息
	FileStaticStruct FileStaticPara;	 

}ToolParaStruct;  //T 刀具信息：静态1，动态，静态2-功能，未知
//打孔环境数据
typedef struct 
{
	int STRUCTHOLE_VER;//机床工作的坐标系
	int FMAT;//机床的指令模式
	bool ICI;//选择相对坐标模式的标志位(ture表示绝对坐标)
	bool T01;//表示1号刀（刀具不知道如何定义）
	float m_tooldiameter;//表示刀具的直径
	int m_tooltype;//表示刀具的类型
	int nXMirror;//表示镜像
	int nYMirror;//表示Y镜像
	bool XYchangeFlag;//false 不需要交换 true需要交换
}HoleEnvParaStruct;
//打孔文件输入的刀具信息数据
typedef struct
{
	double m_Diameter;//刀具直径
	int    ToolType;//刀具类型
	double m_SpindleSpeed;//电机转速
	double m_PlungeRate;//进刀速度
	double m_RetractRate;//出刀速度
	int	   m_Peck;//分段钻次数
	int    m_MagazineNum;//刀盘号码
	double m_Compensate;//刀具尖角补偿参数
	int    m_ToolLife;//刀具的寿命
	int iToolNumber;//表示的是第文件中的第几把刀
	int iToolNumberInAtp;
}structDrillStatic;
//打孔数据结构
typedef struct
{	
	HoleEnvParaStruct m_DrillEnvPara;
	structDrillStatic m_DrillStatic[DRILL_Tool_NUM];
}structDrill;
//孔位置
typedef struct 
{
	int nXs;//普通孔的x坐标值
	int nYs;//普通孔的y坐标值
	int distance;
	int vectlength;//路径长度
}HolePosStruct;
//孔位结点结构
typedef struct HOLEPOSNODE
{	
	int m_ToolNum;//表明当前孔位所属哪一个刀具
	int m_Toolform;//判断所打孔是否是组合孔或者是原点孔（0：是普通的孔位信息，1：代表是原点孔位信息 2：代表的是槽孔 3：代表的是字符信息 5:代表组合空 …）
	int m_LINENUM;//表示此孔位属于打孔文件的第几行
	int m_CurrentDrillNum;//表明这个孔在当前打孔文件中处于第几个孔
	HolePosStruct position; //孔位置
	struct HOLEPOSNODE *pnext;//指向下一个孔结点
}HolePosNode;

//用户信息结构体
typedef  struct USERDATASTRUCT
{
	char m_UserName[20];
	int  m_UserPassword[20];
	int  m_UserLevel;
	bool  m_OpLevel[62];//操作权限
	int m_UserId;
}UserDatastruct;

//断刀信息结构体
typedef struct FRACTUREINFOSTUCT
{	
//	Time m_broketime;//断刀时间
	char *  m_brokeprocess;//断刀程序名
	HolePosStruct m_pos;//断刀时XY的坐标
	int  m_brokeAxis;//断刀轴标号
	int  m_brokeTool;//断刀刀具号
}FractureInfoStuct;

//直径表结构体
typedef struct 
{
	double m_Diameter;//刀具直径
	int    ToolType;//刀具类型
	double m_SpindleSpeed;//电机转速
	double m_PlungeRate;//进刀速度
	double m_RetractRate;//出刀速度
	double m_WaitTime;//XY 轴定位后直至钻孔行程起动的等待时间
	double m_Compensate;//刀具尖角补偿参数
	double m_ToolLife;//刀具的寿命
}structStatic;
typedef struct
{
	char m_letter;
	int a[7];
}CHARACTERSET;//定义了一个数组结构体，里面包括A-Z，0-9的字符点阵表示
/*
//刀具动态结构体
typedef struct
{
	int m_ToolUsedLife;//刀具已经使用寿命
	int m_MillingUsedLife;//铣刀使用寿命
}structDynamic;
//刀具静态参数
typedef struct
{
	bool m_FlagMeaD; //直径检测标志位
	bool m_FlagMeaL; //深度检测判断位
	bool m_FlagMeaR; //偏摆检测判断位
	bool m_FlagTOTO;//接触钻判断位
	bool m_FlagQuick;//快钻判断位
	bool m_FlagPeck;//激活分段钻控制位
}structState;

typedef struct 
{
	double m_Diameter;//刀具直径
	int    ToolType;//刀具类型
	double m_SpindleSpeed;//电机转速
	double m_PlungeRate;//进刀速度
	double m_RetractRate;//出刀速度
	int	   m_Peck;//分段钻次数
	int    m_MagazineNum;//刀盘号码
	double m_Compensate;//刀具尖角补偿参数
	int    m_ToolLife;//刀具的寿命
	int iToolNumber;//文件中的刀号序号
	int iToolNumberInAtp;
	bool useflag;//文件中定义的刀具是否使用（钻孔数大于0）
}structFileStatic;

typedef struct
{
	int iToolNumber;
	//静态参数
	structStatic  StaticPara;
	//动态
	structDynamic DynamicPara;
	//静态2-功能
	structState   StatePara;
	//加工文件中的刀具信息
	structFileStatic FileStaticPara;	 

}structToolPara;  //T 刀具信息：静态1，动态，静态2-功能，未知

//刀盘刀号数据结构
typedef struct
{
	int m_MagazineLine;//表示刀盘第几排
	int m_MagazineVolume;//表示一排刀有几把刀
	int m_MagazineList[8];//表示刀库位置所对应的刀具编号
}structMagazineLink; //L 刀盘上放置的刀号（由structToolPara 参数定义）

typedef struct
{
	int m_MagazineLine;//表示刀盘第几排
	int m_MagazineVolume;//表示一排刀有几把刀
	char m_MagazineState[8];//刀盘状态(new ,used ,end)

}structMagazineLifeStatus;  //W //刀盘上刀具使用寿命状态

typedef struct
{
	int    m_ToleranceNumber;//公差标号
	double m_ToleranceRange; //公差值
	double m_MeaDMax;//直径公差范围最大值
	double m_MeaDMin;//直径公差范围最小值
	double m_MeaLMax;//长度公差范围最大值
	double m_MeaLMin;//长度公差范围最小值
	double m_MeaRMin;//偏摆公差范围
}structTolerance; //Q //公差信息

typedef struct
{
	int iPeckNum;    //分段钻编号
	int iSegVolume;  //分段数量
	struct SegInf
	{
		bool flagValid;  //有效标志
		double fI; //下钻深度
		double fJ; //抬刀的高度
		double fF; //刀具进给速度
		double fR; //刀具回退速度
	}seg[10];

}structPeckDrill; //P //分段钻类型定义
*/


//直径表表项数据
typedef struct
{
	bool flagValid;     //有效标志
	structStatic Para;  //参数
}structDimeterItem;
//直径表数据结构
typedef struct
{
	int iVolume;   //直径表容量
	structDimeterItem Diameter[DTable_NUM]; //直径表项目
}structDiameterTable;
typedef struct _CodeBoundary//由打孔文件得出打孔图形的边界信息
{
	int xMax;
	int yMax;
	int xMin;
	int yMin;
}CodeBoundary;
//----------------------------------------------------------------------------
//以下是机床状态信息数据结构
/*typedef struct
{
	int MACControlState;//表示控制器的多种状态
	int MDState;//表示伺服器的多种状态
	int LimitState;//表示正负限位的状态
	int AxisTemperature;//主轴温度状态
	int AxisPressure1;//主轴1气浮气压状态
	int AxisPressure2;//主轴1气浮气压状态
	int FCState;//变频器状态
	int AxisRotateRate1;//主轴1的转速
	int AxisRotateRate2;//主轴2的转速
	bool OrganSwitch;//零位开关
	bool ChangeToolPress;//换刀气压
	bool BreakCheck;//断钻检测标志位
	int ToolMeasure;//刀具测量
	int PressureFoot;//压脚位置
	bool QIC;//QIC判断标志位
}FCSingalState;*/
typedef struct FILEPATH//用于存放保存上一级目录的临时链表
{
	char pathstr[256];
	struct FILEPATH *pnext;
}FilePath;//用于存放访问路径的链表
typedef struct structCheckXYLocation//检查孔位坐标
{
	double x;//检查孔X坐标
	double y;//检查孔Y坐标
	double Xdistance;//检查孔X方向间距
	double Ydistance;//检查孔Y方向间距
}CheckXYLocation;//检查孔位坐标
typedef struct STRUCTINVIRONMENTPARA//用于保存打孔时机床的环境参数
{
	double H;//刀具的上止点
	double Q;//钻孔时刀具到板子的距离
	double K;//钻孔时刀具钻入板子的深度
	double Z;//刀具下降到台面的距离(刀具的下止点)
	double SUTO;//快钻的参数
	double TOTO;//接触钻的参数
	double XLocation;//检查字符串X方向起始坐标
	double YLocation;//检查字符串Y方向起始坐标
	char CheckText[128];//保存检查的字符串
	double XYdiameter;//保存字符串的直径值
	CString StrPath[5];//保存打孔文件存放的路径
	CString LastStrPath;//保存最近一次打开的文件存放路径
	CString MainProPath;//保存选择的存放.drl的路径
	CString FileStr;//保存修改以后的.drl文件内容
	CheckXYLocation checkxylocation;//检查孔位坐标
}structInvironmentPara;//用于存放访问路径的链表

typedef struct DRILLNOTE
{
	int ToolNum;//加工文件中使用的刀具号（注意区别“使用”与“定义”）
	double ToolDiameter;//刀具直径
	int ToolDrillNum;//刀具需要打孔数量
	int ToolDrillDistance;//刀具所需走的路径
	int ToolNumInAtp;//刀具在ATP中的刀具号,若文件中使用的刀具直径在ATP中不存在，ToolNumberInAtp=0。
}DrillNote;//保存加工文件中使用的每把刀具的信息

/*typedef struct DRILLNOTEPARA
{
	//int ToolNum[128]; //保存已经使用的刀具号
	DrillNote drillnote[128];//每个刀具所保存的参数结构体
}DrillNotePara;*/ 
/////////////////////////////////////////////////////////////////////////2013/05/14

typedef struct AXISSTATE
{
	bool XSTATE;//表示X轴的伺服器状态  （1=激活；0=未激活）
	bool YSTATE;//表示Y轴的伺服器状态  （1=激活；0=未激活）
	bool Z1STATE;//表示Z1轴的伺服器状态（1=激活；0=未激活）
	bool Z2STATE;//表示Z2轴的伺服器状态（1=激活；0=未激活）
}Motistate;

typedef struct AXISPOSITION
{
	double XPOS;//表示X轴的位置
	double YPOS;//表示Y轴的位置
	double Z1POS;//表示Z1轴的位置
	double Z2POS;//表示Z2轴的位置
}AxisPosition;
//______________________________________________zns0414机床状态结构体
typedef struct CNCCONDITION
{
	int XD;//判断运动是否完成
	int YD;
	int ZD;
	float XPOS;//位置
	float YPOS;
	float ZPOS;
}CncCondition;

typedef struct CIRCLESTRUCT
{
	int x;//位置
	int y;
	float R;
}circlestruct;
//-------------------------------------------------------------------

typedef struct SIGNALSTATE
{
//int Freqstat;//表示主轴气浮气压返回值0=气压正常；1=欠压
		bool Freqstat;//表示主轴气浮气压返回值0=气压正常；1=欠压
	int Knifpres;//表示换刀气压（返回值0=气压正常；1=欠压） 
//	int FCSTATE;//表示变频器状态（返回值0=运转；1=停止）
	 bool FCSTATE;//表示变频器状态（返回值0=运转；1=停止）
	int CONTROLSTATE;//控制器状态
	int AxisRunFlag;//主轴运转状态
	Motistate handsup;//表示机械手上位状态
	Motistate handsdwon;//表示机械手下位状态
	Motistate posiswitch;//表示各个轴的零位开关状态
	Motistate breaktest;//表示各个轴的断钻状态
	Motistate footposition;//表示各个轴压脚的位置
	Motistate measuresign;//表示各个轴的刀具测量状态
	Motistate qicbigs;//表示各个轴大压脚的状态
	Motistate qicsmalls;//表示各个轴小压脚的状态
	Motistate motistate;//表示各个轴的伺服器状态
	Motistate axletemps;//表示各个轴的温度状态
	Motistate XAxisLimitPositive;//X轴的正限位状态
	Motistate XAxisLimitNegative;//X轴的负限位状态
	Motistate YAxisLimitPositive;//Y轴的正限位状态
	Motistate YAxisLimitNegative;//Y轴的负限位状态
	AxisPosition AxisAbsolutePosition;//各个轴的绝对位置
}SignalState;

typedef struct USERFLAG
{
	bool userFlag[20];
}UserFlag;

typedef struct DATAPARA //用于F8机床数据分析的结构体
{
	SYSTEMTIME AxisTime;//记录主轴运转时间
	CString  StateReport;//状态报告
	int DrillNum;//当天的打孔总数
	int DrillPath;//当天机床的运动路径
	struct FRACTUREINFOSTUCT fractureinfostuct;//记录断刀结构体
}DataPara;
typedef struct CmdPara
{
	int cmdcode;
	float firstpara;
	float secondpara;
}cmdpara;
//以下是用户标记内存结构体
typedef struct USERMARKFLAG
{
	bool AUTOCHANGEFLAG;//允许自动换刀
	bool MEARUETICKNESS;//允许测量加工厚度
	bool DRILLMARCHING;//允许引孔加工
	bool CHECKSPRUNDRILLING;//下钻前检测电主轴是否打开
	bool RUNSPBEFOREDRILLMTC;//手动换刀模式下，钻孔前是否自动打开电主轴
	bool BREAKTOOLCHECK;//允许断钻检测
	bool BREAKEDGECHECK;//禁止板子边缘断钻检测
	bool AFTERCHECKTOOLLENGTH;// 允许钻完孔后进行刀具长度检测
	bool AUTOAJUESTTOOLLENGH;//自动调整刀具长度
	bool MEARUENEWTOOL;//直径检测（只允许测量新刀具直径）
	bool MEARUEALLTOOL;//允许测量所有刀具直径
	bool AUTOCHANGETOOLLIFE;//自动换刀模式下刀具寿命到有提示
	bool QIC;//允许QIC
}UserMarkFlag;

typedef struct TOOLCHECKPARA//用于刀具检测结构的子结构
{
	double Z1para;
	double Z2para;
	double Z3para;
	double Z4para;
	double Z5para;
	double Z6para;
}toolcheckpara;

typedef struct TOOLDETECTPARA//用于储存刀具检测结果的结构体
{
	struct TOOLCHECKPARA TOOLLENGTHCHECK;//刀具长度测量
	struct TOOLCHECKPARA TOOLDIAMETERCHECK;//刀具直径测量
	struct TOOLCHECKPARA TOOLRUNOUTCHECK;//刀具偏摆测量
}tooldetectpara;

typedef struct HOLEPOSITIONINBITMAP
{
	int m_xposition;
	int m_yposition;
	int m_radius;
	int m_linenumber;
	struct HOLEPOSITIONINBITMAP *m_Pnextnote;
}HolePositionInBitMap;

typedef struct 
{
	double xpos;
	double ypos;
}Position;
typedef struct SPECIALPOINTS//特殊点坐标
{
	Position M0;//机床机械原点
	Position P0;//G93定义的工作原点
	Position Center;//工作区域中心点（绿色区域中心）
}SpecialPoints;

typedef struct MOVEDISTANCE//各轴运动距离  用于机床运动路程显示
{
	double x;
	double y;
	double z1;
	double z2;
	double z3;
	double z4;
	double z5;
	double z6;
}MoveDistance;

typedef struct
{
	double XPosition[3];
	double YPosition[3];
}XYLocationStruct;
#endif MAX_ADF