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
}DrillEnvParaStruct;
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
}DrillKnifeStruct;
//打孔数据结构
/*typedef struct
{	
	HoleEnvParaStruct m_DrillEnvPara;//打孔环境数据
	structDrillStatic m_DrillStatic[DRILL_Tool_NUM];//刀具信息数据
}structDrill;*/

//孔位置
typedef struct 
{
	int nXs;//普通孔的x坐标值
	int nYs;//普通孔的y坐标值
	float diameter;
}HolePositionStruct;
//孔位结点结构
typedef struct HOLEINFONODE
{	
	int m_ToolNum;//表明当前孔位所属哪一个刀具
	int m_Toolform;//判断所打孔是否是组合孔或者是原点孔（0：是普通的孔位信息，1：代表是原点孔位信息 2：代表的是槽孔 3：代表的是字符信息 5:代表组合空 …）
	int m_LINENUM;//表示此孔位属于打孔文件的第几行
	int m_CurrentDrillNum;//表明这个孔在当前打孔文件中处于第几个孔
	HolePositionStruct position; //孔位置
	struct HOLEINFONODE *pnext;//指向下一个孔结点
}HoleInfoNode;


typedef struct
{
	char x1[20];//指向x坐标的字符串指针
	char y1[20];//指向y坐标的字符串指针
	char x2[20];//指向x坐标的字符串指针（经过补零和加小数点的处理）
	char y2[20];//指向y坐标的字符串指针（经过补零和加小数点的处理）
	double  Xanalyse;//经过处理的X的坐标（此处由于槽孔需要记录起始坐标和终点坐标，所以需要两个孔的位置来存放，其他孔位只需用到Xanalyse[0]即可）
	double  Yanalyse;//经过处理的Y的坐标
	double  Xoriganposition;
	double  Yoriganposition;
}DrillLocationStruct;

typedef struct LINK
{
	double XLocation;
	double YLocation;
	struct LINK *pnext;
}LinkStruct;//用于处理槽孔和字符串的临时链表
typedef struct INSTRUCT
{
	char m_instruct[256];
	struct INSTRUCT *pnext;
}InLinkStruct;//用于处理槽孔和字符串的临时链表


typedef struct
{
	bool flagNeedCallback; //回调标记
	int  messageid;		//消息id
	char *messagecode;//[4096]; //命令串
	unsigned long imilisecond;//定时毫秒值	
}MastProgMessageType;
typedef struct _MastProgMessageNode
{
	MastProgMessageType message;
	struct _MastProgMessageNode *pnext;
}MastProgMessageNode;



class CMastProgInOut
{
	public:
	CMastProgInOut();
	virtual ~CMastProgInOut();
	private:
	CString ImportFileInfo;//导入文件信息，文件名全路径
	CString ExportFileInfo;//导出文件信息，文件名全路径
	UINT	ExportOpenMode;
	CString importfilecontent;//导入文件信息字符串，最原始的文件内容

	int m_toolnumber;//当前文件内临时存放刀具号的全局变量（0表示当前孔位没有选定标记，其他自然数则表示相应的刀号）
	int DrillNumber;//保存刀具中打孔的数量  每把刀具对应的孔数
	int Drilllength;//保存刀具中孔位之间的总距离
	

	int m_LineNum;//保存记录当前指令是在打孔文件的第几行

	
	



	bool m_LineEndFlag;//表示每行结束时时候是“/n”当结束符（false表示不是 true表示是）
	bool m_FlagSubProEnd;//表示的是子程序块结束标志位

	int m_FlagEightPin;//八角形的判断标志位（当m_FlagEighPin<2时表示以下的两个坐标都属于八角形的定位坐标）
	int m_FlagDualLine;//双排直插式判断标志位（当m_FlagDualLine<2时表示以下的两个坐标都属于双排直插式的起点和终点的坐标）
	bool m_Flagstr;//表示此坐标是否属于字符串打印的起始坐标
	int m_XYdirection;//（1表示延x方向打印，2表示延y方向打印）
	char *tempstr;//用于分隔字符串的临时指针
	char tempstr1[256];//用于分隔字符串的临时变量
	int a[7][4];//用于临时存放字符转化成的中间代码
	int TempArray[7][4];//用于临时存储字符转换出来的点阵
	char csCmd[256];	//需要发送的命令字符串
	int M02Num;//用于存放M02已经执行的次数
	double Xoffset1;//储存X方向上的偏移量
	double Yoffset1;//储存Y方向上的偏移量

	
	
	XYLocationStruct xylocation;//最终向孔位数据结构中导入数据的数据结构实体(XPosition[0]和YPosition[0]保存当前孔位的坐标;XPosition[1]和YPosition[1]保存前一个点的坐标)
	XYLocationStruct xylocation1;//用于存放槽孔的起始坐标和终止坐标的结构实体
	XYLocationStruct xylocation2;//用于存放八角形(原型)的起始坐标和终止坐标的结构实体（XPosition[0],YPosition[0]存放第一个点的坐标 XPosition[1],XPosition[1]存放计算出来的原点坐标）
	XYLocationStruct xylocation3;//用于存放双排直插式的起点和对角线坐标的结构实体（XPosition[0],YPosition[0]存放第一个点的坐标 XPosition[1],XPosition[1]其对角线坐标，XPosition[2],XPosition[2]储存用于读到的或默认的XY间距
	XYLocationStruct xylocation4;//用于存放圆的中心点坐标(XPosition[0],YPosition[0])和圆的半径(XPosition[1]) 第一个计算出来的原点坐标(XPosition[2],YPosition[2])

	LinkStruct        *m_Previous;
	LinkStruct        *m_Current;
	LinkStruct        *m_first;//以上的指针是用于计算槽孔坐标时生成链表的指针
	LinkStruct        *m_Previous1;
	LinkStruct        *m_Current1;
	LinkStruct        *m_first1;//以上的指针是用于生成最终打孔链表时所用的指针
	LinkStruct        *m_temp;//储存临时生成节点

	InLinkStruct	*m_PreviousCode;
	InLinkStruct	*m_CurrentCode;
	InLinkStruct	*m_firstCode;

	//HoleInfoNode *m_OriPosition;
	HoleInfoNode *Previous;
	HoleInfoNode *Current;
	HoleInfoNode *m_pnext;

	HoleInfoNode *m_tempLocation1;//用于临时储存块中孔位链表的指针值(储存执行M02第二次孔位链表的首地址)
	HoleInfoNode *m_firstLocation;//接受到块指令时用于储存链表的首地址的前一个地址
	HoleInfoNode *m_lastLocation;//接受到块指令时用于储存链表的末尾地址
	//HoleInfoNode *m_WorkPosition;
	
	
	public:
	MastProgMessageNode *phead;//构造函数中赋初值NULL，析构时释放
	HoleInfoNode *m_OriPosition;
	HoleInfoNode *m_WorkPosition;
	DrillEnvParaStruct m_DrillEnvPara;//打孔环境数据
	DrillKnifeStruct m_DrillStatic[DRILL_Tool_NUM];//刀具信息数据
	int TOOLNUM;//用来记录打孔文件中使用了几把刀
	DrillLocationStruct drilllocation;//中间过渡的数据结构实体(包括处理XY坐标的偏移值)
	HoleInfoNode *m_tempLocation;//用于临时储存块中孔位链表的指针值
	XYLocationStruct StrarDrillLocation;//用于存储下一个钻孔时存放的起始点坐标
	int definetoolnum;//记录文件中定义的刀具数量 
	structDrill structdrill;
	HoleInfoNode *m_DrillXOptPosition;//x优化链表
	HoleInfoNode *m_DrillYOptPosition;//y优化链表

	bool relatedtodia;//文件解析与刀具直径有关标志 true：有关（槽孔、字符孔）add by su
	HoleInfoNode *m_DrillDisOptPosition;//距离优化链表
	int TotalDrillNumber;//保存总的孔数  add by su
	int m_ndataN;//表示公制的后几位
	int m_ndataM;//表示公制的前几位
	bool m_LeadTrailFlag;//前后补零的判断标志位（ture表示的前补零）
	bool METRIC;//机床数据的表示（true表示公制）
	bool m_FlagRelativeMod;//相对模式的判断标志位（false表示处于绝对模式，true表示处于相对模式）


	public:
	void ImportExe(CString *pfilecontent);//导入文件操作，文件打开，读取所有文件内容到importfilecontent中
	//---------------zns
	int ParseAnly(CString &ins,ToolParaStruct * Toolpara,DrillNote * drillnote,SpecialPoints * specialpoints);//主程序分析，将importfilecontent分析得到原始工作链表
	//--------------zns
	void ModifyOrigiLocation ();//修改原点位置，保存到原始链表原点对应结点位置，及对应在文件importfilecontent中的原点语句G93
	void ModifyImportFile();//修改导入的文件内容importfilecontent
	int ExportExe(CString filestr);//导出文件操作,输入为导出文件内容字符串
	void SetImportFile(CString filename);//设置导入文件路径信息,
	void SetExportFile(CString filename,UINT openmode);//设置导出文件路径信息
	bool GetBoundryNote(HoleInfoNode *firstnode,CodeBoundary *codeboundary);//获取链表中的XY的最大最小值
	int CopyHolePosNode();//HoleInfoNode *inlist,HoleInfoNode *outlist);//复制链表已存在，直接复制孔位信息
	int CreateAndCopyHolePosNode(HoleInfoNode *outlist);//复制链表不存在，需要创建链表并复制信息
	void XDrillOptProcess(HoleInfoNode * drilllink);//1.X路径优化
	void YDrillOptProcess(HoleInfoNode * drilllink);//2.Y路径优化
	void DistanceDrillOptProcess(HoleInfoNode * drilllink);//3.距离优化
	void FreeDrillLink(HoleInfoNode *firstnode);
	int ProcessArray1(char *str,double xPosition,double yPosition,ToolParaStruct * Toolpara);//函数功能：处理a[7]的一维数组，将其转换为能被ProcessArray处理的多为数组
	bool AddPosition(int Toolnum ,int toolform ,int linenum,int x, int y);//函数功能：向孔位数据链表中添加孔位坐标链表
    int ProcessT(char *ins,ToolParaStruct * FileStaticPara );//钻孔静态参数的处理函数

	private:
	int GetNewLine1( CString &ins, int ibegin, char *newline );//获得新的一行
	int GetTItemStr1( char *ins, char *outs );//获得子串及其长度
	
	char* strrmv( char *s1, char *s2);//将s2子串冲s1中删除
	int ProcessXY(char *ins );//理孔位信息的(函数的字符串输入是只包含有XY坐标信息的字符串)
	int ProcessData(DrillLocationStruct *q);//函数功能:存放有坐标信息的结构体内成员变量根据外部信息转化为正确的公制信息（单位um）
	int ProcessTrough( double p,ToolParaStruct * Toolpara);//函数功能：通过起始点坐标和终止点坐标来计算每个孔位的坐标(输入参数为两个孔之见的最小间距)-槽孔函数
	int ProcessCircle(double p,ToolParaStruct * Toolpara);//函数功能：通过传入的参数计算形成圆的每个圆心的坐标 传入的参数是角度
	int Insertdecimo(char*str1,char*str2,int n);//在一个字符串的指定位置中插入小数点
	int Round(double a);//decimal表示四舍五入保留的位置，1-十位，0-个位，-1十分位，其他以此类推
	int Listamend(HoleInfoNode *q,int x,int y);//此函数实现的功能：将孔位数据节点中的XY坐标按照传入的修正值进行修改
	int ProcessEightPin();//函数功能：根据得到的起始点和原点坐标计算出一个八角形的孔位坐标
	int ProcessDualLine();//函数功能：根据起点和终点坐标计算出双列直插的其他坐标并存入孔位数据链表
	int ProcessArray(int *p,double a,double b,ToolParaStruct * Toolpara);//函数功能： 根据得到相映的int型数组得到相映的坐标位置并输入链表中


	bool AddLinkNote(double x,double y);//向临时的链表中添加节点
	bool AddLinkNote1(double x,double y);//向临时的链表中添加节点
	bool DeletePosition(int x,int y);//完成根据起始坐标删除链表节点

	int XYPositonRevers(HoleInfoNode *note);//对于数据链表上的所有XY坐标进行XY交换
	int XPositonMirro(HoleInfoNode *note);//对于数据链表上的所有XY坐标进行X轴镜像
	int YPositonMirro(HoleInfoNode *note);//对于数据链表上的所有XY坐标进行Y轴镜像
	void TranslateStr(char *p);	
	double TranslateData(double data);

	void ProcessRelativeMod(char *ins);
	void ProcessAbsoluteMod(char *ins);
	void ProcessSlotPattern(char *ins,ToolParaStruct * Toolpara);
	void ProcessCirclePattern(char *ins,ToolParaStruct * Toolpara);
	void ProcessCannedTextPattern(char *ins,ToolParaStruct * Toolpara);
	void ProcessDualInlinePattern(char *ins);
	void ProcessEightPinPattern(char *ins);
	int GotoNextLine(int linelength);
	int ProcessMirro(int ver,HoleInfoNode *firstnode);//根据不同坐标系，转换x、y位置
	//int CopyHolePosNode(HoleInfoNode *inlist,HoleInfoNode *outlist);
	



};