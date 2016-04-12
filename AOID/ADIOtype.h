//////////////////////////////////////////////////////////////
//�޸�����2013/05/23

#ifndef MAX_ADF
#define MAX_ADF
////////////////////////////////////////////////////////////////
//ATP Const
#define ATP_Tool_NUM               300  //��ʾ���ߵ�����
#define DRILL_Tool_NUM             500  
#define ATP_MagazineLine_NUM       200  //�����Ϸŵ�������
#define ATP_MagazineLifeStatus_NUM 200  //�����ϵ���ʹ������״̬
#define ATP_Tolerance_NUM          16	//������Ϣ
#define ATP_PeckDrill_NUM          500	//�ֶ������Ͷ���
//
#define DTable_NUM                 300	//ֱ������Ŀ��������
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
#define f_XYJG 1007     //�����˶�
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
//ֱ����ṹ��,��̬�б�����ṹ
typedef struct 
{
	double m_Diameter;//����ֱ��
	int    ToolType;//��������
	double m_SpindleSpeed;//���ת��
	double m_PlungeRate;//�����ٶ�
	double m_RetractRate;//�����ٶ�
	double m_WaitTime;//XY �ᶨλ��ֱ������г��𶯵ĵȴ�ʱ��
	double m_Compensate;//���߼�ǲ�������
	double m_ToolLife;//���ߵ�����
}StaticListStruct;
//���߶�̬�������ṹ
typedef struct
{
	int m_ToolUsedLife;//�����Ѿ�ʹ������
	int m_MillingUsedLife;//ϳ��ʹ������
}DynamicListStruct;
//���߾�̬�б�2����
typedef struct
{
	bool m_FlagMeaD; //ֱ������־λ
	bool m_FlagMeaL; //��ȼ���ж�λ
	bool m_FlagMeaR; //ƫ�ڼ���ж�λ
	bool m_FlagTOTO;//�Ӵ����ж�λ
	bool m_FlagQuick;//�����ж�λ
	bool m_FlagPeck;//����ֶ������λ
}StaticList2Struct;
///////////////////////////
//�ӹ��ļ��еĵ��߲����ṹ
typedef struct 
{
	double m_Diameter;//����ֱ��
	int    ToolType;//��������
	double m_SpindleSpeed;//���ת��
	double m_PlungeRate;//�����ٶ�
	double m_RetractRate;//�����ٶ�
	int	   m_Peck;//�ֶ������
	int    m_MagazineNum;//���̺���
	double m_Compensate;//���߼�ǲ�������
	int    m_ToolLife;//���ߵ�����
	int iToolNumber;//�ļ��еĵ������
	int iToolNumberInAtp;
	bool useflag;//�ļ��ж���ĵ����Ƿ�ʹ�ã����������0��
}FileStaticStruct;
//���߲����ṹ
typedef struct
{
	int iToolNumber;
	//��̬����
	StaticListStruct  StaticPara;
	//��̬
	DynamicListStruct DynamicPara;
	//��̬2-����
	StaticList2Struct   StatePara;
	//�ӹ��ļ��еĵ�����Ϣ
	FileStaticStruct FileStaticPara;	 

}ToolParaStruct;  //T ������Ϣ����̬1����̬����̬2-���ܣ�δ֪
//��׻�������
typedef struct 
{
	int STRUCTHOLE_VER;//��������������ϵ
	int FMAT;//������ָ��ģʽ
	bool ICI;//ѡ���������ģʽ�ı�־λ(ture��ʾ��������)
	bool T01;//��ʾ1�ŵ������߲�֪����ζ��壩
	float m_tooldiameter;//��ʾ���ߵ�ֱ��
	int m_tooltype;//��ʾ���ߵ�����
	int nXMirror;//��ʾ����
	int nYMirror;//��ʾY����
	bool XYchangeFlag;//false ����Ҫ���� true��Ҫ����
}HoleEnvParaStruct;
//����ļ�����ĵ�����Ϣ����
typedef struct
{
	double m_Diameter;//����ֱ��
	int    ToolType;//��������
	double m_SpindleSpeed;//���ת��
	double m_PlungeRate;//�����ٶ�
	double m_RetractRate;//�����ٶ�
	int	   m_Peck;//�ֶ������
	int    m_MagazineNum;//���̺���
	double m_Compensate;//���߼�ǲ�������
	int    m_ToolLife;//���ߵ�����
	int iToolNumber;//��ʾ���ǵ��ļ��еĵڼ��ѵ�
	int iToolNumberInAtp;
}structDrillStatic;
//������ݽṹ
typedef struct
{	
	HoleEnvParaStruct m_DrillEnvPara;
	structDrillStatic m_DrillStatic[DRILL_Tool_NUM];
}structDrill;
//��λ��
typedef struct 
{
	int nXs;//��ͨ�׵�x����ֵ
	int nYs;//��ͨ�׵�y����ֵ
	int distance;
	int vectlength;//·������
}HolePosStruct;
//��λ���ṹ
typedef struct HOLEPOSNODE
{	
	int m_ToolNum;//������ǰ��λ������һ������
	int m_Toolform;//�ж�������Ƿ�����Ͽ׻�����ԭ��ף�0������ͨ�Ŀ�λ��Ϣ��1��������ԭ���λ��Ϣ 2��������ǲۿ� 3����������ַ���Ϣ 5:������Ͽ� ����
	int m_LINENUM;//��ʾ�˿�λ���ڴ���ļ��ĵڼ���
	int m_CurrentDrillNum;//����������ڵ�ǰ����ļ��д��ڵڼ�����
	HolePosStruct position; //��λ��
	struct HOLEPOSNODE *pnext;//ָ����һ���׽��
}HolePosNode;

//�û���Ϣ�ṹ��
typedef  struct USERDATASTRUCT
{
	char m_UserName[20];
	int  m_UserPassword[20];
	int  m_UserLevel;
	bool  m_OpLevel[62];//����Ȩ��
	int m_UserId;
}UserDatastruct;

//�ϵ���Ϣ�ṹ��
typedef struct FRACTUREINFOSTUCT
{	
//	Time m_broketime;//�ϵ�ʱ��
	char *  m_brokeprocess;//�ϵ�������
	HolePosStruct m_pos;//�ϵ�ʱXY������
	int  m_brokeAxis;//�ϵ�����
	int  m_brokeTool;//�ϵ����ߺ�
}FractureInfoStuct;

//ֱ����ṹ��
typedef struct 
{
	double m_Diameter;//����ֱ��
	int    ToolType;//��������
	double m_SpindleSpeed;//���ת��
	double m_PlungeRate;//�����ٶ�
	double m_RetractRate;//�����ٶ�
	double m_WaitTime;//XY �ᶨλ��ֱ������г��𶯵ĵȴ�ʱ��
	double m_Compensate;//���߼�ǲ�������
	double m_ToolLife;//���ߵ�����
}structStatic;
typedef struct
{
	char m_letter;
	int a[7];
}CHARACTERSET;//������һ������ṹ�壬�������A-Z��0-9���ַ������ʾ
/*
//���߶�̬�ṹ��
typedef struct
{
	int m_ToolUsedLife;//�����Ѿ�ʹ������
	int m_MillingUsedLife;//ϳ��ʹ������
}structDynamic;
//���߾�̬����
typedef struct
{
	bool m_FlagMeaD; //ֱ������־λ
	bool m_FlagMeaL; //��ȼ���ж�λ
	bool m_FlagMeaR; //ƫ�ڼ���ж�λ
	bool m_FlagTOTO;//�Ӵ����ж�λ
	bool m_FlagQuick;//�����ж�λ
	bool m_FlagPeck;//����ֶ������λ
}structState;

typedef struct 
{
	double m_Diameter;//����ֱ��
	int    ToolType;//��������
	double m_SpindleSpeed;//���ת��
	double m_PlungeRate;//�����ٶ�
	double m_RetractRate;//�����ٶ�
	int	   m_Peck;//�ֶ������
	int    m_MagazineNum;//���̺���
	double m_Compensate;//���߼�ǲ�������
	int    m_ToolLife;//���ߵ�����
	int iToolNumber;//�ļ��еĵ������
	int iToolNumberInAtp;
	bool useflag;//�ļ��ж���ĵ����Ƿ�ʹ�ã����������0��
}structFileStatic;

typedef struct
{
	int iToolNumber;
	//��̬����
	structStatic  StaticPara;
	//��̬
	structDynamic DynamicPara;
	//��̬2-����
	structState   StatePara;
	//�ӹ��ļ��еĵ�����Ϣ
	structFileStatic FileStaticPara;	 

}structToolPara;  //T ������Ϣ����̬1����̬����̬2-���ܣ�δ֪

//���̵������ݽṹ
typedef struct
{
	int m_MagazineLine;//��ʾ���̵ڼ���
	int m_MagazineVolume;//��ʾһ�ŵ��м��ѵ�
	int m_MagazineList[8];//��ʾ����λ������Ӧ�ĵ��߱��
}structMagazineLink; //L �����Ϸ��õĵ��ţ���structToolPara �������壩

typedef struct
{
	int m_MagazineLine;//��ʾ���̵ڼ���
	int m_MagazineVolume;//��ʾһ�ŵ��м��ѵ�
	char m_MagazineState[8];//����״̬(new ,used ,end)

}structMagazineLifeStatus;  //W //�����ϵ���ʹ������״̬

typedef struct
{
	int    m_ToleranceNumber;//������
	double m_ToleranceRange; //����ֵ
	double m_MeaDMax;//ֱ�����Χ���ֵ
	double m_MeaDMin;//ֱ�����Χ��Сֵ
	double m_MeaLMax;//���ȹ��Χ���ֵ
	double m_MeaLMin;//���ȹ��Χ��Сֵ
	double m_MeaRMin;//ƫ�ڹ��Χ
}structTolerance; //Q //������Ϣ

typedef struct
{
	int iPeckNum;    //�ֶ�����
	int iSegVolume;  //�ֶ�����
	struct SegInf
	{
		bool flagValid;  //��Ч��־
		double fI; //�������
		double fJ; //̧���ĸ߶�
		double fF; //���߽����ٶ�
		double fR; //���߻����ٶ�
	}seg[10];

}structPeckDrill; //P //�ֶ������Ͷ���
*/


//ֱ�����������
typedef struct
{
	bool flagValid;     //��Ч��־
	structStatic Para;  //����
}structDimeterItem;
//ֱ�������ݽṹ
typedef struct
{
	int iVolume;   //ֱ��������
	structDimeterItem Diameter[DTable_NUM]; //ֱ������Ŀ
}structDiameterTable;
typedef struct _CodeBoundary//�ɴ���ļ��ó����ͼ�εı߽���Ϣ
{
	int xMax;
	int yMax;
	int xMin;
	int yMin;
}CodeBoundary;
//----------------------------------------------------------------------------
//�����ǻ���״̬��Ϣ���ݽṹ
/*typedef struct
{
	int MACControlState;//��ʾ�������Ķ���״̬
	int MDState;//��ʾ�ŷ����Ķ���״̬
	int LimitState;//��ʾ������λ��״̬
	int AxisTemperature;//�����¶�״̬
	int AxisPressure1;//����1������ѹ״̬
	int AxisPressure2;//����1������ѹ״̬
	int FCState;//��Ƶ��״̬
	int AxisRotateRate1;//����1��ת��
	int AxisRotateRate2;//����2��ת��
	bool OrganSwitch;//��λ����
	bool ChangeToolPress;//������ѹ
	bool BreakCheck;//�������־λ
	int ToolMeasure;//���߲���
	int PressureFoot;//ѹ��λ��
	bool QIC;//QIC�жϱ�־λ
}FCSingalState;*/
typedef struct FILEPATH//���ڴ�ű�����һ��Ŀ¼����ʱ����
{
	char pathstr[256];
	struct FILEPATH *pnext;
}FilePath;//���ڴ�ŷ���·��������
typedef struct structCheckXYLocation//����λ����
{
	double x;//����X����
	double y;//����Y����
	double Xdistance;//����X������
	double Ydistance;//����Y������
}CheckXYLocation;//����λ����
typedef struct STRUCTINVIRONMENTPARA//���ڱ�����ʱ�����Ļ�������
{
	double H;//���ߵ���ֹ��
	double Q;//���ʱ���ߵ����ӵľ���
	double K;//���ʱ����������ӵ����
	double Z;//�����½���̨��ľ���(���ߵ���ֹ��)
	double SUTO;//����Ĳ���
	double TOTO;//�Ӵ���Ĳ���
	double XLocation;//����ַ���X������ʼ����
	double YLocation;//����ַ���Y������ʼ����
	char CheckText[128];//��������ַ���
	double XYdiameter;//�����ַ�����ֱ��ֵ
	CString StrPath[5];//�������ļ���ŵ�·��
	CString LastStrPath;//�������һ�δ򿪵��ļ����·��
	CString MainProPath;//����ѡ��Ĵ��.drl��·��
	CString FileStr;//�����޸��Ժ��.drl�ļ�����
	CheckXYLocation checkxylocation;//����λ����
}structInvironmentPara;//���ڴ�ŷ���·��������

typedef struct DRILLNOTE
{
	int ToolNum;//�ӹ��ļ���ʹ�õĵ��ߺţ�ע������ʹ�á��롰���塱��
	double ToolDiameter;//����ֱ��
	int ToolDrillNum;//������Ҫ�������
	int ToolDrillDistance;//���������ߵ�·��
	int ToolNumInAtp;//������ATP�еĵ��ߺ�,���ļ���ʹ�õĵ���ֱ����ATP�в����ڣ�ToolNumberInAtp=0��
}DrillNote;//����ӹ��ļ���ʹ�õ�ÿ�ѵ��ߵ���Ϣ

/*typedef struct DRILLNOTEPARA
{
	//int ToolNum[128]; //�����Ѿ�ʹ�õĵ��ߺ�
	DrillNote drillnote[128];//ÿ������������Ĳ����ṹ��
}DrillNotePara;*/ 
/////////////////////////////////////////////////////////////////////////2013/05/14

typedef struct AXISSTATE
{
	bool XSTATE;//��ʾX����ŷ���״̬  ��1=���0=δ���
	bool YSTATE;//��ʾY����ŷ���״̬  ��1=���0=δ���
	bool Z1STATE;//��ʾZ1����ŷ���״̬��1=���0=δ���
	bool Z2STATE;//��ʾZ2����ŷ���״̬��1=���0=δ���
}Motistate;

typedef struct AXISPOSITION
{
	double XPOS;//��ʾX���λ��
	double YPOS;//��ʾY���λ��
	double Z1POS;//��ʾZ1���λ��
	double Z2POS;//��ʾZ2���λ��
}AxisPosition;
//______________________________________________zns0414����״̬�ṹ��
typedef struct CNCCONDITION
{
	int XD;//�ж��˶��Ƿ����
	int YD;
	int ZD;
	float XPOS;//λ��
	float YPOS;
	float ZPOS;
}CncCondition;

typedef struct CIRCLESTRUCT
{
	int x;//λ��
	int y;
	float R;
}circlestruct;
//-------------------------------------------------------------------

typedef struct SIGNALSTATE
{
//int Freqstat;//��ʾ����������ѹ����ֵ0=��ѹ������1=Ƿѹ
		bool Freqstat;//��ʾ����������ѹ����ֵ0=��ѹ������1=Ƿѹ
	int Knifpres;//��ʾ������ѹ������ֵ0=��ѹ������1=Ƿѹ�� 
//	int FCSTATE;//��ʾ��Ƶ��״̬������ֵ0=��ת��1=ֹͣ��
	 bool FCSTATE;//��ʾ��Ƶ��״̬������ֵ0=��ת��1=ֹͣ��
	int CONTROLSTATE;//������״̬
	int AxisRunFlag;//������ת״̬
	Motistate handsup;//��ʾ��е����λ״̬
	Motistate handsdwon;//��ʾ��е����λ״̬
	Motistate posiswitch;//��ʾ���������λ����״̬
	Motistate breaktest;//��ʾ������Ķ���״̬
	Motistate footposition;//��ʾ������ѹ�ŵ�λ��
	Motistate measuresign;//��ʾ������ĵ��߲���״̬
	Motistate qicbigs;//��ʾ�������ѹ�ŵ�״̬
	Motistate qicsmalls;//��ʾ������Сѹ�ŵ�״̬
	Motistate motistate;//��ʾ��������ŷ���״̬
	Motistate axletemps;//��ʾ��������¶�״̬
	Motistate XAxisLimitPositive;//X�������λ״̬
	Motistate XAxisLimitNegative;//X��ĸ���λ״̬
	Motistate YAxisLimitPositive;//Y�������λ״̬
	Motistate YAxisLimitNegative;//Y��ĸ���λ״̬
	AxisPosition AxisAbsolutePosition;//������ľ���λ��
}SignalState;

typedef struct USERFLAG
{
	bool userFlag[20];
}UserFlag;

typedef struct DATAPARA //����F8�������ݷ����Ľṹ��
{
	SYSTEMTIME AxisTime;//��¼������תʱ��
	CString  StateReport;//״̬����
	int DrillNum;//����Ĵ������
	int DrillPath;//����������˶�·��
	struct FRACTUREINFOSTUCT fractureinfostuct;//��¼�ϵ��ṹ��
}DataPara;
typedef struct CmdPara
{
	int cmdcode;
	float firstpara;
	float secondpara;
}cmdpara;
//�������û�����ڴ�ṹ��
typedef struct USERMARKFLAG
{
	bool AUTOCHANGEFLAG;//�����Զ�����
	bool MEARUETICKNESS;//��������ӹ����
	bool DRILLMARCHING;//�������׼ӹ�
	bool CHECKSPRUNDRILLING;//����ǰ���������Ƿ��
	bool RUNSPBEFOREDRILLMTC;//�ֶ�����ģʽ�£����ǰ�Ƿ��Զ��򿪵�����
	bool BREAKTOOLCHECK;//���������
	bool BREAKEDGECHECK;//��ֹ���ӱ�Ե������
	bool AFTERCHECKTOOLLENGTH;// ��������׺���е��߳��ȼ��
	bool AUTOAJUESTTOOLLENGH;//�Զ��������߳���
	bool MEARUENEWTOOL;//ֱ����⣨ֻ��������µ���ֱ����
	bool MEARUEALLTOOL;//����������е���ֱ��
	bool AUTOCHANGETOOLLIFE;//�Զ�����ģʽ�µ�������������ʾ
	bool QIC;//����QIC
}UserMarkFlag;

typedef struct TOOLCHECKPARA//���ڵ��߼��ṹ���ӽṹ
{
	double Z1para;
	double Z2para;
	double Z3para;
	double Z4para;
	double Z5para;
	double Z6para;
}toolcheckpara;

typedef struct TOOLDETECTPARA//���ڴ��浶�߼�����Ľṹ��
{
	struct TOOLCHECKPARA TOOLLENGTHCHECK;//���߳��Ȳ���
	struct TOOLCHECKPARA TOOLDIAMETERCHECK;//����ֱ������
	struct TOOLCHECKPARA TOOLRUNOUTCHECK;//����ƫ�ڲ���
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
typedef struct SPECIALPOINTS//���������
{
	Position M0;//������еԭ��
	Position P0;//G93����Ĺ���ԭ��
	Position Center;//�����������ĵ㣨��ɫ�������ģ�
}SpecialPoints;

typedef struct MOVEDISTANCE//�����˶�����  ���ڻ����˶�·����ʾ
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