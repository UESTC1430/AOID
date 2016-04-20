#include "stdafx.h"
#include  "MastProgInOut.h"
#define Pi      3.1415926
CHARACTERSET m_character[40]={{'0',{6,9,9,9,9,9,6}},
{'1',{7,2,2,2,2,6,2}},
{'2',{15,8,6,2,1,9,6}},
{'3',{6,9,1,6,1,9,6}},
{'4',{ 1,1,1,15,9,9,9}},
{'5',{15,1,1,15,8,8,15}},
{'6',{6,9,9,14,8,9,6}},
{'7',{8,8,6,2,1,1,15}},
{'8',{6,9,9,6,9,9,6}},
{'9',{6,9,1,7,9,9,6}},
{'A',{9,9,9,15,9,9,6}},
{'B',{14,9,9,14,9,9,14}},
{'C',{6,9,8,8,8,9,6}},
{'D',{14,9,9,9,9,9,14}},
{'E',{15,8,8,14,8,8,15}},
{'F',{8,8,8,14,8,8,15}},
{'G',{7,9,9,15,8,9,6}},
{'H',{9,9,9,15,9,9,9}},
{'I',{14,4,4,4,4,4,14}},
{'J',{6,10,2,2,2,2,7}},
{'K',{9,10,12,8,13,10,9}},
{'L',{15,8,8,8,8,8,8}},
{'M',{9,9,9,9,9,15,9}},
{'N',{9,9,9,9,11,13,9}},
{'O',{15,9,9,9,9,9,15}},
{'P',{8,8,8,14,9,9,14}},
{'Q',{1,15,13,9,9,9,15}},
{'R',{9,10,12,14,9,9,14}},
{'S',{6,9,1,6,8,9,6}},
{'T',{4,4,4,4,4,4,14}},
{'U',{15,9,9,9,9,9,9}},
{'V',{6,9,9,9,9,9,9}},
{'W',{9,15,9,9,9,9,9}},
{'X',{9,9,6,6,9,9,9}},
{'Y',{6,6,6,6,6,10,10}},
{'Z',{15,8,6,2,1,1,15}},
{'+',{0,0,6,14,6,0,0}},
{'-',{0,0,0,15,0,0,0}},
{'/',{8,8,8,6,2,1,1}},
{',',{0,0,0,0,0,0,0}}};
CMastProgInOut::CMastProgInOut()
{
//	m_OriPosition = NULL;
	m_WorkPosition = NULL;
	
	m_toolnumber=0;//当前文件内临时存放刀具号的全局变量（0表示当前孔位没有选定标记，其他自然数则表示相应的刀号）
	DrillNumber=0;//保存刀具中打孔的数量  每把刀具对应的孔数
	Drilllength=0;//保存刀具中孔位之间的总距离
	TotalDrillNumber=0;//保存总的孔数  add by su
	relatedtodia=false;//文件解析与刀具直径有关标志 true：有关（槽孔、字符孔）add by su
	m_LineNum=0;//保存记录当前指令是在打孔文件的第几行
	TOOLNUM=0;//用来记录打孔文件中使用了几把刀
	definetoolnum=0;//记录文件中定义的刀具数量 
	METRIC=true;//机床数据的表示（true表示公制）
	m_ndataM=0;//表示公制的前几位
	m_ndataN=0;//表示公制的后几位
	m_LeadTrailFlag;//前后补零的判断标志位（ture表示的前补零）
	m_LineEndFlag;//表示每行结束时时候是“/n”当结束符（false表示不是 true表示是）
	m_FlagSubProEnd=false;//表示的是子程序块结束标志位
	m_FlagRelativeMod=false;//相对模式的判断标志位（false表示处于绝对模式，true表示处于相对模式）
	m_FlagEightPin=2;//八角形的判断标志位（当m_FlagEighPin<2时表示以下的两个坐标都属于八角形的定位坐标）
	m_FlagDualLine=2;//双排直插式判断标志位（当m_FlagDualLine<2时表示以下的两个坐标都属于双排直插式的起点和终点的坐标）
	m_Flagstr=false;//表示此坐标是否属于字符串打印的起始坐标
	m_XYdirection=0;//（1表示延x方向打印，2表示延y方向打印）
	tempstr=NULL;//用于分隔字符串的临时指针
	//tempstr1[256]={0};//用于分隔字符串的临时变量
	//a[7][4]={0};//用于临时存放字符转化成的中间代码
	//TempArray[7][4]={0};//用于临时存储字符转换出来的点阵
	m_OriPosition=NULL;
	Previous=NULL;
	Current=NULL;
	m_pnext=NULL;
	m_tempLocation=NULL;//用于临时储存块中孔位链表的指针值
	m_tempLocation1=NULL;//用于临时储存块中孔位链表的指针值(储存执行M02第二次孔位链表的首地址)
	m_firstLocation=NULL;//接受到块指令时用于储存链表的首地址的前一个地址
	m_lastLocation=NULL;//接受到块指令时用于储存链表的末尾地址
	m_WorkPosition=NULL;
	m_DrillXOptPosition=NULL;//x优化链表
	m_DrillYOptPosition=NULL;//y优化链表

	m_DrillDisOptPosition=NULL;//距离优化链表
	
	m_Previous=NULL;
	m_Current=NULL;
	m_first=NULL;//以上的指针是用于计算槽孔坐标时生成链表的指针
	m_Previous1=NULL;
	m_Current1=NULL;
	m_first1=NULL;//以上的指针是用于生成最终打孔链表时所用的指针
	m_temp=NULL;//储存临时生成节点
	
	m_PreviousCode=NULL;
	m_CurrentCode=NULL;
	m_firstCode=NULL;
	
	
	M02Num=0;//用于存放M02已经执行的次数
	Xoffset1=0;//储存X方向上的偏移量
	Yoffset1=0;//储存Y方向上的偏移量
}

CMastProgInOut::~CMastProgInOut()
{
}
/********************************************************
Function: ImportExe
Description: 导入文件操作，文件打开，读取所有文件内容到importfilecontent中
Input: CString *pfilecontent    
Output: 
Return: 
Others: 其它说明 
* ********************************************************/
void CMastProgInOut::ImportExe(CString *pfilecontent)//
{
	
	CFile file;
	CFileException e;
	if(file.Open(this->ImportFileInfo,CFile::modeRead, &e ) )
	{
		int ilong = file.GetLength();
		char * pfilestr = new char[ilong+1];	
		ilong = file.Read(pfilestr,ilong);
		pfilestr[ilong]='\0';	
		if (strlen(pfilestr)!=0)
		{	
			//m_filecontentstr = pfilestr;
			this->importfilecontent = pfilestr;
			
			if(-1==importfilecontent.Find("\r\n",0))//对文件内容做处理，换行替换成回车换行
			{
				importfilecontent.Replace("\n","\r\n");
			}
			
			//去掉最后一个换行符号
			int Strlength=0;
			int LeftEnterPositon=0;
			Strlength=importfilecontent.GetLength();
			LeftEnterPositon=importfilecontent.ReverseFind('\n');
			if(LeftEnterPositon==Strlength-1)
			{
				importfilecontent.Delete(Strlength-2,2);
			}
			*pfilecontent = importfilecontent;
			//ProcessStr(&m_filecontentstr);
			//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//导出界面
			//	UpdateData(false);
		}
		delete pfilestr;
		pfilestr=NULL;
		file.Close();
	}
}
/********************************************************
Function: ParseAnly
Description: 主程序分析，将importfilecontent分析得到原始工作链表
Input: CString  filestr    
Output: 
Return: 
Others: 其它说明 
*********************************************************/
/*int CMastProgInOut::ParseAnly(CString &ins,DrillNote * drillnote,SpecialPoints * specialpoints )
{
	if (ins.IsEmpty())
	{
		return -1;
	}
	int errcode = 0;
	//	int iLen = 0;  //总长度
	int iLen =ins.GetLength();  //总长度
	int iPos = 0;  //记录行在整个字符串中的起始位置
	int iLineLen=0; //行的长度
	char buf[256]="";//每一行的临时指针
	char *title;//分段的时候临时段指针
	bool bProHead = true;//在头文件声明之前
	int ilen=0;//每一行的段指针
	
	m_LineEndFlag=true;	
	int flagBegin = 0; //0: 未开始，1：开始；2：结束
	
	char *p = (LPSTR)(LPCTSTR)ins;//此处用于判断是否每一行是“/n”
	for(int i=0; i<iLen; i++)
	{
		if( 0x0d == p[i] && 0x0a == p[i+1])
        {
			m_LineEndFlag=false;
			break;
		}
	} 
	//---------------------------------------------------------------------------------------
	//每次调用此处的时候都应该进行一次清空链表的操作
	if(m_OriPosition)
	{
		FreeDrillLink(m_OriPosition);
		free(m_OriPosition);
		m_OriPosition = NULL;
		
	}
	if(m_WorkPosition)
	{
		FreeDrillLink(m_WorkPosition);
		free(m_WorkPosition);
		m_WorkPosition = NULL;
	}
	//-------------------------------------------------------------------------------------------
	m_FlagSubProEnd=false;
	m_ndataM=0;//表示公制的前几位
	m_ndataN=0;//表示公制的后几位
	m_LineNum=0;//文件从第0行开始
	definetoolnum=0;//文件中定义的刀具数量
	TOOLNUM=0;//文件内用了几把刀
	DrillNumber=0;//刀具钻孔数为0
	relatedtodia=false;
	TotalDrillNumber=0;
	//-----------------------------------------zns修改
	/*char *m_filecontentstr2=ins.GetBuffer(0);
	ToolParaStruct * Toolpara=NULL;
	ProcessT(m_filecontentstr2,Toolpara);
	//for(int i=1;i<ATP_Tool_NUM;i++)
	//	memset(&Toolpara[i].FileStaticPara,0,sizeof(Toolpara[i].FileStaticPara));
	//-------------------------------------------------------------------------------------------
	
	char *tempstrstr=(LPSTR)(LPCTSTR)ins;
	if(NULL==strstr(tempstrstr,"G93"))//此处的代码是设定打孔文件没有出现设置值时的预设值
	{
		xylocation.XPosition[0]=0;
		xylocation.YPosition[0]=0;
		xylocation.XPosition[1]=0;
		xylocation.YPosition[1]=0;
		AddPosition(m_toolnumber,1,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
	}
	
	//---------------------------------------------------------------------------------------
	
	while( iPos < iLen ) //
	{
		iLineLen = GetNewLine1(ins,iPos,buf );
		if(0==strcmp(buf,""))
		{
			iPos += iLineLen + 2 ; //跳过0D0A
			continue;
		}
		if(!_strnicmp(buf, "M48", 3) && bProHead == true)
		{		
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "BLKD", 4) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "SBK", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "SG", 2) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "TCST", 4) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "OSTOP", 5) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "RSB", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "ATC", 3) && bProHead == true)
		{
			//此处暂时不做操作（自动换刀功能没有对应的数据结构）
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "FSB", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "M47", 3) && bProHead == false)
		{
			//此处暂时不做操作（暂停指令并显示后面的字符）
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if(!_strnicmp(buf, "VER", 3) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			m_DrillEnvPara.STRUCTHOLE_VER=atoi(title);
			/*switch(atoi(title))
			{
			case 1:
			drillpara->m_DrillEnvPara.nXMirror =  1;
			drillpara->m_DrillEnvPara.nYMirror = 1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=1;
			break;
			case 4:
			drillpara->m_DrillEnvPara.nXMirror = -1;
			drillpara->m_DrillEnvPara.nYMirror = 1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=4;
			break;
			case 6:
			drillpara->m_DrillEnvPara.nXMirror = -1;
			drillpara->m_DrillEnvPara.nYMirror = -1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=6;
			break;
			case 7:
			drillpara->m_DrillEnvPara.nXMirror =  1;
			drillpara->m_DrillEnvPara.nYMirror =  -1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=7;
			break;
		}
			
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "FMAT", 4) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			if(atoi(title)==1)
				m_DrillEnvPara.FMAT=1;
			else
				m_DrillEnvPara.FMAT=2;
			iPos+=GotoNextLine(iLineLen); 
			continue;
			
		}
		
		if((!_strnicmp(buf, "METRIC", 6))||(!_strnicmp(buf, "INCH", 4)) && bProHead == true)
		{
			char *p[2];
			if(!_strnicmp(buf, "INCH", 4))
				METRIC=false;
			else if(!_strnicmp(buf,"METRIC",6))
				METRIC=true;
			title = strtok(buf, ",");
			p[0] = strtok(NULL, ",");
			p[1] = strtok(NULL, ",");
			for(int i = 0; i < 2; i++)
			{
				if(p[i] == NULL)
					continue;
				else if(!_strnicmp(p[i], "TZ", 2))
					m_LeadTrailFlag=false;
				else if(!_strnicmp(p[i], "LZ", 2))
					m_LeadTrailFlag=true;
				else if(!_strnicmp(p[i], "000.000", 7))
				{
					m_ndataM = 3;
					m_ndataN = 3;
				}
				else if(!_strnicmp(p[i], "00.0000", 7))
				{
					m_ndataM=2;
					m_ndataN=4;
				}
				else if(!_strnicmp(p[i], "000.00", 6))
				{
					m_ndataM=3;
					m_ndataN=2;
				}
				else if(!_strnicmp(p[i], "0000.00", 7))
				{
					m_ndataM=4;
					m_ndataN=2;
				}
				else if(!_strnicmp(p[i], "00.000", 6))
				{
					m_ndataM=2;
					m_ndataN=3;
				}
				else if(!_strnicmp(p[i], "0.00000", 7))
				{
					m_ndataM=1;
					m_ndataN=5;
				}
				else if(!_strnicmp(p[i], "00000.0", 7))
				{
					m_ndataM=5;
					m_ndataN=1;
				}
				else if(!_strnicmp(p[i], "0.0000", 6))
				{
					m_ndataM=1;
					m_ndataN=4;
				}
				else if(!_strnicmp(p[i], "0000.0", 6))
				{
					m_ndataM=4;
					m_ndataN=1;
				}
			}
			
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "M71", 3))
		{
			//此处暂时不做操作
			METRIC=true;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "M72", 3)&& bProHead == false)
		{
			METRIC=false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "ICI", 3) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			if(strcmp(title,"OFF"))
				m_DrillEnvPara.ICI=true;
			else
				m_DrillEnvPara.ICI=false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "T", 1))
		{	
			
			if(bProHead == true)//处理打孔文件中参数配置值
			ProcessT(buf,Toolpara);
			else  //处理打孔文件正文的值
			{
				//	if(0<=TOOLNUM&&TOOLNUM<128&&DrillNum!=0)//这里是对每把刀具在孔位文件中的需求量，行程路径等参数进行设置
				if(DrillNumber!=0)//钻孔数不为0,保存至已使用刀具结构体
				{
					drillnote[TOOLNUM].ToolNum=m_toolnumber;
					drillnote[TOOLNUM].ToolDrillNum=DrillNumber;
					drillnote[TOOLNUM].ToolDrillDistance=(int)Drilllength;
					//Toolpara[m_toolnumber].FileStaticPara.useflag=true;
					TOOLNUM++;
					TotalDrillNumber+=DrillNumber;
				}
				char *ch="T";
				char *buffer=strrmv( buf, ch);
				m_toolnumber=atoi(buf);
				DrillNumber=0;//每碰到一个刀具将上一个刀具的打孔数和形成清零
				Drilllength=0;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "%", 1)) && bProHead == true)//此处表示文件头配置结束
		{
			bProHead = false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "G05", 3))||(!_strnicmp(buf, "G00", 3)) && bProHead == false)
		{	
			if(!_strnicmp(buf, "G05", 3))
			{}//钻床开始执行标志位处理
			else
			{}//铣床开始执行标志位处理
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "P", 1) && bProHead == false)//此时默认P紧跟在M82后
		{	
			int i=0;//串当前位置
			int j=0;//串长度
			int RepeatTime=0;//保存重复块的次数
			double Xoffset=0;
			double Yoffset=0;
			char buffer[256]; //子串	
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{				
				case 'P':
					strrmv(buffer,"P");
					RepeatTime=atoi(buffer);
					i+=j;//串头后移
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset=drilllocation.Xanalyse;
					i+=j; //串头后移
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset=drilllocation.Yanalyse;
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;
				}
			}
			m_tempLocation=m_firstLocation->pnext;
			for(int k=1;k<=RepeatTime;k++ )
			{
				while(m_lastLocation!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset*k;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset*k;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset*k;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset*k;
				DrillNumber++;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				m_tempLocation=m_firstLocation->pnext;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "G93", 3)) && bProHead == false)
		{	
			int Toolform=1;//1代表原点孔位信息
			char *ch="G93";
			char *buffer=strrmv( buf, ch);
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			//drilllocation.Xoriganposition=drilllocation.Xanalyse;//程序原点
			//drilllocation.Yoriganposition=drilllocation.Yanalyse;
			specialpoints->P0.xpos=drilllocation.Xanalyse;//程序原点
			specialpoints->P0.ypos=drilllocation.Yanalyse;
			
			xylocation.XPosition[0]=drilllocation.Xanalyse;
			xylocation.YPosition[0]=drilllocation.Yanalyse;
			xylocation.XPosition[1]=0;
			xylocation.YPosition[1]=0;
			AddPosition(m_toolnumber,1,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "G04", 3)) && bProHead == false)
		{
			ProcessXY(buf);
			ProcessData(&drilllocation);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(((!_strnicmp(buf, "G90", 3))||(!_strnicmp(buf, "G91", 3)))&& bProHead == false)
		{
			if(!_strnicmp(buf, "G90", 3))
			{
				m_FlagRelativeMod=false;//绝度模式
			}
			else
			{
				m_FlagRelativeMod=true;//相对模式
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		
		if(((!_strnicmp(buf, "X", 1))||(!_strnicmp(buf, "Y", 1))) && bProHead == false &&m_toolnumber!=0)
		{
			if(false==m_Flagstr&&m_FlagEightPin>1&&m_FlagDualLine>1)//非字符孔、非八角孔、非双列直插孔
			{	
				if(NULL==strstr(buf,"G85")&&NULL==strstr(buf,"G84"))//buf中不包含"G85"和"G84"
				{
					if(false==m_FlagRelativeMod)//处理绝对坐标模式
						ProcessAbsoluteMod(buf);
					else//处理相对坐标模式
						ProcessRelativeMod(buf);	
				}
				else
				{
					relatedtodia=true;//坐标与刀具直径相关
				//	if(NULL!=strstr(buf,"G85"))//buf中包含"G85"
//						ProcessSlotPattern(buf,Toolpara);	//对线槽的处理
			//		if(NULL!=strstr(buf,"G84"))
	//					ProcessCirclePattern(buf,Toolpara);	//对圆槽的处理
				}
			}
			//else if(true==m_Flagstr)//以下实现处理字符串起始坐标的功能（在调用的函数中自动区分x方向和y方向）
				//ProcessCannedTextPattern(buf,Toolpara);
			//else if(m_FlagEightPin<=1)//以下的代码处理八角形的坐标
			//	ProcessEightPinPattern(buf);
			//else if(m_FlagDualLine<=1)//此处是处理双列直插的
			//	ProcessDualInlinePattern(buf);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if((!_strnicmp(buf, "M97", 3)) && bProHead == false)
		{
			relatedtodia=true;//坐标与刀具直径相关
			tempstr=strrmv(buf,"M97,");
			TranslateStr(tempstr);
			strcpy_s(tempstr1,tempstr);
			m_Flagstr=true;
			m_XYdirection=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "M98", 3)) && bProHead == false)
		{
			relatedtodia=true;//坐标与刀具直径相关
			tempstr=strrmv(buf,"M98,");
			TranslateStr(tempstr);
			strcpy_s(tempstr1,tempstr);
			m_Flagstr=true;
			m_XYdirection=2;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "M25", 3)) && bProHead == false)
		{
			m_firstLocation=Current;
			iPos+=GotoNextLine(iLineLen);
			m_FlagSubProEnd=false;
			continue;
		}
		if(!_strnicmp(buf, "M01", 3) && bProHead == false)
		{
			m_lastLocation=Current;
			m_FlagSubProEnd =true;
			M02Num=0;
			Xoffset1=0;//在出现M01的时候偏移值被置零
			Yoffset1=0;//在出现M01的时候偏移值被置零
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf,"M02",3)&&bProHead==false)//此处处理的前提是前面已经有一个子块，如果没有就会报错
		{
			int i=0;//串当前位置
			int j=0;//串长度
			int k=0;//储存重复执行的次数
			int Flag=0;//用于标识M02指令中M70 M80 M90的状态（1表示M70在最后 2 表示M80在最后 3表示M90在最后）
			int NoteNum=0;//用于存放执行M02时生成了多少个节点数
			char buffer[256]; //子串	
			char *temp;
			if(0==strcmp(buf,"M02"))
			{
				iPos += iLineLen + 2 ; 
				m_LineNum++;
				continue;
			}
			temp=strrev(buf);//将字符串进行倒序排序
			if(!strnicmp(buf, "07M", 3))//此处判断M02行中哪个是最后一个（M70 M80 M90）
			{
				Flag=1;
			}
			else if(!strnicmp(buf, "08M", 3))
			{
				Flag=2;
			}
			else if(!strnicmp(buf, "09M", 3))
			{
				Flag=3;
			}
			strrev(buf);//将字符串恢复正序
			m_tempLocation=m_firstLocation->pnext;//此段代码用于执行M02的操作，将链表中的指定孔位进行复制一遍
			while(m_lastLocation!=m_tempLocation)
			{
				NoteNum+=1;
				xylocation.XPosition[0]=m_tempLocation->position.nXs;
				xylocation.YPosition[0]=m_tempLocation->position.nYs;
				DrillNumber++;
				AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				m_tempLocation=m_tempLocation->pnext;
			}
			xylocation.XPosition[0]=m_tempLocation->position.nXs;
			xylocation.YPosition[0]=m_tempLocation->position.nYs;
			DrillNumber++;
			AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
			NoteNum+=1;
			m_tempLocation=m_lastLocation->pnext;//此段代码用于确定新生成链表的首节点
			for(int a=NoteNum*M02Num;a>0;a--)
			{
				m_tempLocation=m_tempLocation->pnext;
			}
			m_tempLocation1=m_tempLocation;
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{
					
				case 'M':
					if(NULL!=strstr(buffer,"M70"))//进行XY轴交换的操作
					{
						if(Flag==1)//此处处理M70在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;	
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;
									xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;//此处是将最后一个节点的值进行XY的变换操作
								xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
							}
							else 
							{
								//此处对没有子块进行报错处理
							}
						}
						else//此处处理M70不在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;	
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nYs;
									xylocation.YPosition[0]=m_tempLocation->position.nXs;
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs;//此处是将最后一个节点的值进行XY的变换操作
								xylocation.YPosition[0]=m_tempLocation->position.nXs;	
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else 
							{
								//此处对没有子块进行报错处理
							}
						}
					}
					else if(NULL!=strstr(buffer,"M80"))//X镜像操作
					{
						if(2==Flag)
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
									xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//此处处理M80不在最后的情况
						{
							
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=-m_tempLocation->position.nXs;
									xylocation.YPosition[0]=m_tempLocation->position.nYs;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs;
								xylocation.YPosition[0]=m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else if(NULL!=strstr(buffer,"M90"))//Y镜像操作
					{
						if(Flag==3)//此处处理M90在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
									xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//此处处理M90 不在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nXs;
									xylocation.YPosition[0]=-m_tempLocation->position.nYs;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//					m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else 
					{
						//此处处理M02后面没有M70 M80 M90的情况
					}
					i+=j; //串头后移
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset1+=drilllocation.Xanalyse;//M02连续的时候需要将偏差值累计进行叠加
					
					i+=j; //串头后移
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset1+=drilllocation.Yanalyse;//M02连续的时候需要将偏差值累计进行叠加
					
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;		
					
				}
			}
			//			m_firstLocation=m_tempLocation1;
			
			if(NULL==strstr(buf,"M70")&&NULL==strstr(buf,"M80")&&NULL==strstr(buf,"M90"))//用于处理没有M70 M80 M90的情况
			{
				m_tempLocation=m_tempLocation1;
				while(Current!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
					m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
				m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
			}
			M02Num+=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == false)
		{	
			int i=0;//串当前位置
			int j=0;//串长度
			int k=0;//储存重复执行的次数
			double Xoffset=0;//储存X方向上的偏移量
			double Yoffset=0;//储存Y方向上的偏移量
			char buffer[256]; //子串	
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{
					
				case 'R':
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						strrmv(buffer,"R");
						k=atoi(buffer);
					}
					i+=j; //串头后移
					break;
				case 'X': 
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Xoffset=drilllocation.Xanalyse;
					}
					i+=j; //串头后移
					break;
				case 'Y': 
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Yoffset=drilllocation.Yanalyse;
					}
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;
				}
			}
			
			if(m_FlagSubProEnd == false)
			{
				for(int num1=0;num1<k;num1++)
				{
					
					xylocation.XPosition[0]+=Xoffset;
					xylocation.YPosition[0]+=Yoffset;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				}
			}
			else
			{
				int i=1;
				for(int num2=0;num2<k-1;num2++)
				{
					
					m_tempLocation=m_firstLocation->pnext;
					while(m_lastLocation!=m_tempLocation)
					{
						xylocation.XPosition[0]=Xoffset*i+m_tempLocation->position.nXs;
						xylocation.YPosition[0]=Yoffset*i+m_tempLocation->position.nYs;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						m_tempLocation=m_tempLocation->pnext;
					}
					xylocation.XPosition[0]=Xoffset*i+m_tempLocation->position.nXs;
					xylocation.YPosition[0]=Yoffset*i+m_tempLocation->position.nYs;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					i++;
				}
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == true)
		{
			//此处不做操作
			iPos += iLineLen + 2 ; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "M08", 3) && bProHead == false)
		{
			m_firstLocation=NULL;
			m_lastLocation=NULL;
			m_FlagSubProEnd=false;
			iPos += iLineLen + 2 ; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "G82", 3) && bProHead == false)
		{
			if(NULL!=strstr(buf,"X")&&NULL!=strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=drilllocation.Xanalyse;
				xylocation3.YPosition[2]=drilllocation.Yanalyse;
			}
			else if(NULL!=strstr(buf,"X")&&NULL==strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=drilllocation.Xanalyse;
				xylocation3.YPosition[2]=7.62*1000;
			}
			else if(NULL==strstr(buf,"X")&&NULL!=strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=2.54*1000;
				xylocation3.YPosition[2]=drilllocation.Yanalyse;
			}
			else if(NULL==strstr(buf,"X")&&NULL==strstr(buf,"Y"))
			{
				xylocation3.XPosition[2]=2.54*1000;
				xylocation3.YPosition[2]=7.62*1000;
			}
			else
			{
				//G82的容错机制
			}
			m_FlagDualLine=0;
			m_firstLocation=Current;//此处将前一个孔位坐标当作块的起始坐标赋予块的首地址
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "G83", 3) && bProHead == false)
		{
			m_FlagEightPin=0;
			iPos += iLineLen + 2; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "M99", 3) && bProHead == false)
		{
			//处理M99的标志位（暂时不做操作）
			iPos += iLineLen + 2; 
			m_LineNum++;
			continue;
		}		
		if((!strnicmp(buf, "M30", 3)) && bProHead == false)
		{
			char *str=NULL;
			char *ch="M30";
			char *buffer=strrmv( buf, ch);
			//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			if(DrillNumber!=0)
			{
				drillnote[TOOLNUM].ToolNum=m_toolnumber;
				drillnote[TOOLNUM].ToolDrillNum=DrillNumber;
				drillnote[TOOLNUM].ToolDrillDistance=(int)Drilllength;
	//			Toolpara[m_toolnumber].FileStaticPara.useflag=true;
				TOOLNUM++;
				TotalDrillNumber+=DrillNumber;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		iPos+=GotoNextLine(iLineLen); 		
	}
	return 0;
}*/
int CMastProgInOut::ParseAnly(CString &ins,ToolParaStruct * Toolpara,DrillNote * drillnote,SpecialPoints * specialpoints )
{
	if (ins.IsEmpty())
	{
		return -1;
	}
	int errcode = 0;
	//	int iLen = 0;  //总长度
	int iLen =ins.GetLength();  //总长度
	int iPos = 0;  //记录行在整个字符串中的起始位置
	int iLineLen=0; //行的长度
	char buf[256]="";//每一行的临时指针
	char *title;//分段的时候临时段指针
	bool bProHead = true;//在头文件声明之前
	int ilen=0;//每一行的段指针

	m_LineEndFlag=true;	
	int flagBegin = 0; //0: 未开始，1：开始；2：结束
	
	char *p = (LPSTR)(LPCTSTR)ins;//此处用于判断是否每一行是“/n”
	for(int i=0; i<iLen; i++)
	{
		if( 0x0d == p[i] && 0x0a == p[i+1])
        {
			m_LineEndFlag=false;
			break;
		}
	} 
	//---------------------------------------------------------------------------------------
	//每次调用此处的时候都应该进行一次清空链表的操作
	if(m_OriPosition)
	{
		FreeDrillLink(m_OriPosition);
		free(m_OriPosition);
		m_OriPosition = NULL;
		
	}
	/*if(m_WorkPosition)
	{
		FreeDrillLink(m_WorkPosition);
		free(m_WorkPosition);
		m_WorkPosition = NULL;
	}*/
	//-------------------------------------------------------------------------------------------
	m_FlagSubProEnd=false;
	m_ndataM=0;//表示公制的前几位
	m_ndataN=0;//表示公制的后几位
	m_LineNum=0;//文件从第0行开始
	definetoolnum=0;//文件中定义的刀具数量
	TOOLNUM=0;//文件内用了几把刀
	DrillNumber=0;//刀具钻孔数为0
	relatedtodia=false;
	TotalDrillNumber=0;
	for(int i=1;i<ATP_Tool_NUM;i++)  //ATP_Tool_NUM   -------------------------------------------------------------------------------------------====
		memset(&(Toolpara[i].FileStaticPara),0,sizeof(Toolpara[i].FileStaticPara));
	//-------------------------------------------------------------------------------------------
	
	char *tempstrstr=(LPSTR)(LPCTSTR)ins;
	if(NULL==strstr(tempstrstr,"G93"))//此处的代码是设定打孔文件没有出现设置值时的预设值
	{
		xylocation.XPosition[0]=0;
		xylocation.YPosition[0]=0;
		xylocation.XPosition[1]=0;
		xylocation.YPosition[1]=0;
		AddPosition(m_toolnumber,1,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
	}
	
	//---------------------------------------------------------------------------------------
	
	while( iPos < iLen ) //
	{
		iLineLen = GetNewLine1(ins,iPos,buf );
		if(0==strcmp(buf,""))
		{
			iPos += iLineLen + 2 ; //跳过0D0A
			continue;
		}
		if(!strnicmp(buf, "M48", 3) && bProHead == true)
		{		
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "BLKD", 4) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "SBK", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "SG", 2) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "TCST", 4) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "OSTOP", 5) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "RSB", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "ATC", 3) && bProHead == true)
		{
			//此处暂时不做操作（自动换刀功能没有对应的数据结构）
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "FSB", 3) && bProHead == true)
		{
			//此处暂时不做操作
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "M47", 3) && bProHead == false)
		{
			//此处暂时不做操作（暂停指令并显示后面的字符）
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if(!strnicmp(buf, "VER", 3) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			m_DrillEnvPara.STRUCTHOLE_VER=atoi(title);
			/*switch(atoi(title))
			{
			case 1:
			drillpara->m_DrillEnvPara.nXMirror =  1;
			drillpara->m_DrillEnvPara.nYMirror = 1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=1;
			break;
			case 4:
			drillpara->m_DrillEnvPara.nXMirror = -1;
			drillpara->m_DrillEnvPara.nYMirror = 1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=4;
			break;
			case 6:
			drillpara->m_DrillEnvPara.nXMirror = -1;
			drillpara->m_DrillEnvPara.nYMirror = -1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=6;
			break;
			case 7:
			drillpara->m_DrillEnvPara.nXMirror =  1;
			drillpara->m_DrillEnvPara.nYMirror =  -1;
			drillpara->m_DrillEnvPara.STRUCTHOLE_VER=7;
			break;
		}*/
			
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "FMAT", 4) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			if(atoi(title)==1)
				m_DrillEnvPara.FMAT=1;
			else
				m_DrillEnvPara.FMAT=2;
			iPos+=GotoNextLine(iLineLen); 
			continue;
			
		}
		
		if((!strnicmp(buf, "METRIC", 6))||(!strnicmp(buf, "INCH", 4)) && bProHead == true)
		{
			char *p[2];
			if(!strnicmp(buf, "INCH", 4))
				METRIC=false;
			else if(!strnicmp(buf,"METRIC",6))
				METRIC=true;
			title = strtok(buf, ",");
			p[0] = strtok(NULL, ",");
			p[1] = strtok(NULL, ",");
			for(int i = 0; i < 2; i++)
			{
				if(p[i] == NULL)
					continue;
				else if(!strnicmp(p[i], "TZ", 2))
					m_LeadTrailFlag=false;
				else if(!strnicmp(p[i], "LZ", 2))
					m_LeadTrailFlag=true;
				else if(!strnicmp(p[i], "000.000", 7))
				{
					m_ndataM = 3;
					m_ndataN = 3;
				}
				else if(!strnicmp(p[i], "00.0000", 7))
				{
					m_ndataM=2;
					m_ndataN=4;
				}
				else if(!strnicmp(p[i], "000.00", 6))
				{
					m_ndataM=3;
					m_ndataN=2;
				}
				else if(!strnicmp(p[i], "0000.00", 7))
				{
					m_ndataM=4;
					m_ndataN=2;
				}
				else if(!strnicmp(p[i], "00.000", 6))
				{
					m_ndataM=2;
					m_ndataN=3;
				}
				else if(!strnicmp(p[i], "0.00000", 7))
				{
					m_ndataM=1;
					m_ndataN=5;
				}
				else if(!strnicmp(p[i], "00000.0", 7))
				{
					m_ndataM=5;
					m_ndataN=1;
				}
				else if(!strnicmp(p[i], "0.0000", 6))
				{
					m_ndataM=1;
					m_ndataN=4;
				}
				else if(!strnicmp(p[i], "0000.0", 6))
				{
					m_ndataM=4;
					m_ndataN=1;
				}
			}
			
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "M71", 3))
		{
			//此处暂时不做操作
			METRIC=true;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "M72", 3)&& bProHead == false)
		{
			METRIC=false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "ICI", 3) && bProHead == true)
		{
			title = strtok(buf, ",");
			title = strtok(NULL, ",");
			if(strcmp(title,"OFF"))
				m_DrillEnvPara.ICI=true;
			else
				m_DrillEnvPara.ICI=false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "T", 1))
		{	
			
			if(bProHead == true)//处理打孔文件中参数配置值
				ProcessT(buf,Toolpara);
			else  //处理打孔文件正文的值
			{
				//	if(0<=TOOLNUM&&TOOLNUM<128&&DrillNum!=0)//这里是对每把刀具在孔位文件中的需求量，行程路径等参数进行设置
				if(DrillNumber!=0)//钻孔数不为0,保存至已使用刀具结构体
				{
					drillnote[TOOLNUM].ToolNum=m_toolnumber;
					drillnote[TOOLNUM].ToolDrillNum=DrillNumber;
					drillnote[TOOLNUM].ToolDrillDistance=(int)Drilllength;
					Toolpara[m_toolnumber].FileStaticPara.useflag=true;
					TOOLNUM++;
					TotalDrillNumber+=DrillNumber;
				}
				char *ch="T";
				char *buffer=strrmv( buf, ch);
				m_toolnumber=atoi(buf);
				DrillNumber=0;//每碰到一个刀具将上一个刀具的打孔数和形成清零
				Drilllength=0;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "%", 1)) && bProHead == true)//此处表示文件头配置结束
		{
			bProHead = false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "G05", 3))||(!strnicmp(buf, "G00", 3)) && bProHead == false)
		{	
			if(!strnicmp(buf, "G05", 3))
			{}//钻床开始执行标志位处理
			else
			{}//铣床开始执行标志位处理
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "P", 1) && bProHead == false)//此时默认P紧跟在M82后
		{	
			int i=0;//串当前位置
			int j=0;//串长度
			int RepeatTime=0;//保存重复块的次数
			double Xoffset=0;
			double Yoffset=0;
			char buffer[256]; //子串	
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{				
				case 'P':
					strrmv(buffer,"P");
					RepeatTime=atoi(buffer);
					i+=j;//串头后移
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset=drilllocation.Xanalyse;
					i+=j; //串头后移
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset=drilllocation.Yanalyse;
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;
				}
			}
			m_tempLocation=m_firstLocation->pnext;
			for(int k=1;k<=RepeatTime;k++ )
			{
				while(m_lastLocation!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset*k;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset*k;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset*k;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset*k;
				DrillNumber++;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				m_tempLocation=m_firstLocation->pnext;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "G93", 3)) && bProHead == false)
		{	
			int Toolform=1;//1代表原点孔位信息
			char *ch="G93";
			char *buffer=strrmv( buf, ch);
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			//drilllocation.Xoriganposition=drilllocation.Xanalyse;//程序原点
			//drilllocation.Yoriganposition=drilllocation.Yanalyse;
			specialpoints->P0.xpos=drilllocation.Xanalyse;//程序原点
			specialpoints->P0.ypos=drilllocation.Yanalyse;
			
			xylocation.XPosition[0]=drilllocation.Xanalyse;
			xylocation.YPosition[0]=drilllocation.Yanalyse;
			xylocation.XPosition[1]=0;
			xylocation.YPosition[1]=0;
			AddPosition(m_toolnumber,1,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "G04", 3)) && bProHead == false)
		{
			ProcessXY(buf);
			ProcessData(&drilllocation);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(((!strnicmp(buf, "G90", 3))||(!strnicmp(buf, "G91", 3)))&& bProHead == false)
		{
			if(!strnicmp(buf, "G90", 3))
			{
				m_FlagRelativeMod=false;//绝度模式
			}
			else
			{
				m_FlagRelativeMod=true;//相对模式
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		
		if(((!strnicmp(buf, "X", 1))||(!strnicmp(buf, "Y", 1))) && bProHead == false &&m_toolnumber!=0)
		{
			if(false==m_Flagstr&&m_FlagEightPin>1&&m_FlagDualLine>1)//非字符孔、非八角孔、非双列直插孔
			{	
				if(NULL==strstr(buf,"G85")&&NULL==strstr(buf,"G84"))//buf中不包含"G85"和"G84"
				{
					if(false==m_FlagRelativeMod)//处理绝对坐标模式
						ProcessAbsoluteMod(buf);
					else//处理相对坐标模式
						ProcessRelativeMod(buf);	
				}
				else
				{
					relatedtodia=true;//坐标与刀具直径相关
					if(NULL!=strstr(buf,"G85"))//buf中包含"G85"
						ProcessSlotPattern(buf,Toolpara);	//对线槽的处理
					if(NULL!=strstr(buf,"G84"))
						ProcessCirclePattern(buf,Toolpara);	//对圆槽的处理
				}
			}
			else if(true==m_Flagstr)//以下实现处理字符串起始坐标的功能（在调用的函数中自动区分x方向和y方向）
				ProcessCannedTextPattern(buf,Toolpara);
			else if(m_FlagEightPin<=1)//以下的代码处理八角形的坐标
				ProcessEightPinPattern(buf);
			else if(m_FlagDualLine<=1)//此处是处理双列直插的
				ProcessDualInlinePattern(buf);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if((!strnicmp(buf, "M97", 3)) && bProHead == false)
		{
			relatedtodia=true;//坐标与刀具直径相关
			tempstr=strrmv(buf,"M97,");
			TranslateStr(tempstr);
			strcpy(tempstr1,tempstr);
			m_Flagstr=true;
			m_XYdirection=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "M98", 3)) && bProHead == false)
		{
			relatedtodia=true;//坐标与刀具直径相关
			tempstr=strrmv(buf,"M98,");
			TranslateStr(tempstr);
			strcpy(tempstr1,tempstr);
			m_Flagstr=true;
			m_XYdirection=2;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "M25", 3)) && bProHead == false)
		{
			m_firstLocation=Current;
			iPos+=GotoNextLine(iLineLen);
			m_FlagSubProEnd=false;
			continue;
		}
		if(!strnicmp(buf, "M01", 3) && bProHead == false)
		{
			m_lastLocation=Current;
			m_FlagSubProEnd =true;
			M02Num=0;
			Xoffset1=0;//在出现M01的时候偏移值被置零
			Yoffset1=0;//在出现M01的时候偏移值被置零
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf,"M02",3)&&bProHead==false)//此处处理的前提是前面已经有一个子块，如果没有就会报错
		{
			int i=0;//串当前位置
			int j=0;//串长度
			int k=0;//储存重复执行的次数
			int Flag=0;//用于标识M02指令中M70 M80 M90的状态（1表示M70在最后 2 表示M80在最后 3表示M90在最后）
			int NoteNum=0;//用于存放执行M02时生成了多少个节点数
			char buffer[256]; //子串	
			char *temp;
			if(0==strcmp(buf,"M02"))
			{
				iPos += iLineLen + 2 ; 
				m_LineNum++;
				continue;
			}
			temp=strrev(buf);//将字符串进行倒序排序
			if(!strnicmp(buf, "07M", 3))//此处判断M02行中哪个是最后一个（M70 M80 M90）
			{
				Flag=1;
			}
			else if(!strnicmp(buf, "08M", 3))
			{
				Flag=2;
			}
			else if(!strnicmp(buf, "09M", 3))
			{
				Flag=3;
			}
			strrev(buf);//将字符串恢复正序
			m_tempLocation=m_firstLocation->pnext;//此段代码用于执行M02的操作，将链表中的指定孔位进行复制一遍
			while(m_lastLocation!=m_tempLocation)
			{
				NoteNum+=1;
				xylocation.XPosition[0]=m_tempLocation->position.nXs;
				xylocation.YPosition[0]=m_tempLocation->position.nYs;
				DrillNumber++;
				AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				m_tempLocation=m_tempLocation->pnext;
			}
			xylocation.XPosition[0]=m_tempLocation->position.nXs;
			xylocation.YPosition[0]=m_tempLocation->position.nYs;
			DrillNumber++;
			AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
			NoteNum+=1;
			m_tempLocation=m_lastLocation->pnext;//此段代码用于确定新生成链表的首节点
			for(int a=NoteNum*M02Num;a>0;a--)
			{
				m_tempLocation=m_tempLocation->pnext;
			}
			m_tempLocation1=m_tempLocation;
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{
					
				case 'M':
					if(NULL!=strstr(buffer,"M70"))//进行XY轴交换的操作
					{
						if(Flag==1)//此处处理M70在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;	
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;
									xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;//此处是将最后一个节点的值进行XY的变换操作
								xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
							}
							else 
							{
								//此处对没有子块进行报错处理
							}
						}
						else//此处处理M70不在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;	
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nYs;
									xylocation.YPosition[0]=m_tempLocation->position.nXs;
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs;//此处是将最后一个节点的值进行XY的变换操作
								xylocation.YPosition[0]=m_tempLocation->position.nXs;	
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else 
							{
								//此处对没有子块进行报错处理
							}
						}
					}
					else if(NULL!=strstr(buffer,"M80"))//X镜像操作
					{
						if(2==Flag)
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
									xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//此处处理M80不在最后的情况
						{
							
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=-m_tempLocation->position.nXs;
									xylocation.YPosition[0]=m_tempLocation->position.nYs;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs;
								xylocation.YPosition[0]=m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else if(NULL!=strstr(buffer,"M90"))//Y镜像操作
					{
						if(Flag==3)//此处处理M90在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
									xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//此处处理M90 不在最后的情况
						{
							if(Current!=m_firstLocation)
							{
								m_tempLocation=m_tempLocation1;
								while(Current!=m_tempLocation)
								{
									xylocation.XPosition[0]=m_tempLocation->position.nXs;
									xylocation.YPosition[0]=-m_tempLocation->position.nYs;	
									Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
									xylocation.XPosition[1]=xylocation.XPosition[0];
									xylocation.YPosition[1]=xylocation.YPosition[0];
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//					m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else 
					{
						//此处处理M02后面没有M70 M80 M90的情况
					}
					i+=j; //串头后移
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset1+=drilllocation.Xanalyse;//M02连续的时候需要将偏差值累计进行叠加
					
					i+=j; //串头后移
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset1+=drilllocation.Yanalyse;//M02连续的时候需要将偏差值累计进行叠加
					
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;		
					
				}
			}
			//			m_firstLocation=m_tempLocation1;
			
			if(NULL==strstr(buf,"M70")&&NULL==strstr(buf,"M80")&&NULL==strstr(buf,"M90"))//用于处理没有M70 M80 M90的情况
			{
				m_tempLocation=m_tempLocation1;
				while(Current!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
					m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//此步完成对新生成链表的修改
				m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
			}
			M02Num+=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == false)
		{	
			int i=0;//串当前位置
			int j=0;//串长度
			int k=0;//储存重复执行的次数
			double Xoffset=0;//储存X方向上的偏移量
			double Yoffset=0;//储存Y方向上的偏移量
			char buffer[256]; //子串	
			while( j=GetTItemStr1(&buf[i],buffer) ) //不是空串
			{
				switch( buffer[0] ) //根据子串首字符进行处理
				{
					
				case 'R':
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						strrmv(buffer,"R");
						k=atoi(buffer);
					}
					i+=j; //串头后移
					break;
				case 'X': 
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Xoffset=drilllocation.Xanalyse;
					}
					i+=j; //串头后移
					break;
				case 'Y': 
					if( j == 1 )//没有参数
					{
						//没有参数报错
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Yoffset=drilllocation.Yanalyse;
					}
					i+=j; //串头后移
					break;
				default:
					i+=j;
					break;
				}
			}
			
			if(m_FlagSubProEnd == false)
			{
				for(int num1=0;num1<k;num1++)
				{
					
					xylocation.XPosition[0]+=Xoffset;
					xylocation.YPosition[0]+=Yoffset;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				}
			}
			else
			{
				int i=1;
				for(int num2=0;num2<k-1;num2++)
				{
					
					m_tempLocation=m_firstLocation->pnext;
					while(m_lastLocation!=m_tempLocation)
					{
						xylocation.XPosition[0]=Xoffset*i+m_tempLocation->position.nXs;
						xylocation.YPosition[0]=Yoffset*i+m_tempLocation->position.nYs;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						m_tempLocation=m_tempLocation->pnext;
					}
					xylocation.XPosition[0]=Xoffset*i+m_tempLocation->position.nXs;
					xylocation.YPosition[0]=Yoffset*i+m_tempLocation->position.nYs;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					i++;
				}
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == true)
		{
			//此处不做操作
			iPos += iLineLen + 2 ; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "M08", 3) && bProHead == false)
		{
			m_firstLocation=NULL;
			m_lastLocation=NULL;
			m_FlagSubProEnd=false;
			iPos += iLineLen + 2 ; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "G82", 3) && bProHead == false)
		{
			if(NULL!=strstr(buf,"X")&&NULL!=strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=drilllocation.Xanalyse;
				xylocation3.YPosition[2]=drilllocation.Yanalyse;
			}
			else if(NULL!=strstr(buf,"X")&&NULL==strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=drilllocation.Xanalyse;
				xylocation3.YPosition[2]=7.62*1000;
			}
			else if(NULL==strstr(buf,"X")&&NULL!=strstr(buf,"Y"))
			{
				ProcessXY(buf);
				ProcessData(&drilllocation);
				xylocation3.XPosition[2]=2.54*1000;
				xylocation3.YPosition[2]=drilllocation.Yanalyse;
			}
			else if(NULL==strstr(buf,"X")&&NULL==strstr(buf,"Y"))
			{
				xylocation3.XPosition[2]=2.54*1000;
				xylocation3.YPosition[2]=7.62*1000;
			}
			else
			{
				//G82的容错机制
			}
			m_FlagDualLine=0;
			m_firstLocation=Current;//此处将前一个孔位坐标当作块的起始坐标赋予块的首地址
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "G83", 3) && bProHead == false)
		{
			m_FlagEightPin=0;
			iPos += iLineLen + 2; 
			m_LineNum++;
			continue;
		}
		if(!strnicmp(buf, "M99", 3) && bProHead == false)
		{
			//处理M99的标志位（暂时不做操作）
			iPos += iLineLen + 2; 
			m_LineNum++;
			continue;
		}		
		if((!strnicmp(buf, "M30", 3)) && bProHead == false)
		{
			char *str=NULL;
			char *ch="M30";
			char *buffer=strrmv( buf, ch);
		//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			if(DrillNumber!=0)
			{
				drillnote[TOOLNUM].ToolNum=m_toolnumber;
				drillnote[TOOLNUM].ToolDrillNum=DrillNumber;
				drillnote[TOOLNUM].ToolDrillDistance=(int)Drilllength;
				Toolpara[m_toolnumber].FileStaticPara.useflag=true;
				TOOLNUM++;
				TotalDrillNumber+=DrillNumber;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		iPos+=GotoNextLine(iLineLen); 		
	}
//------------------------------------------------------zns修改
	HoleInfoNode *curr=m_OriPosition;
	while (curr!=NULL)
	{
		curr->position.diameter=1000*(Toolpara[curr->m_ToolNum].FileStaticPara.m_Diameter);
		//	->position.diameter=Toolpara[m_OriPosition->pnext->m_ToolNum].FileStaticPara.m_Diameter;
	   // m_OriPosition->pnext=
		curr=curr->pnext;
	}
	//_________________________________________________________
	return 0;
}
/********************************************************
Function: ModifyOrigiLocation
Description: 修改原点位置，保存到原始链表原点对应结点位置，及对应在文件importfilecontent中的原点语句G93
Input:    
Output: 
Return: 
Others: 其它说明 
*********************************************************/
void CMastProgInOut::ModifyOrigiLocation()
{
}
/********************************************************
Function: ModifyOrigiLocation
Description: 修改导入的文件内容importfilecontent
Input:    
Output: 
Return: 
Others: 其它说明 
*********************************************************/
void CMastProgInOut::ModifyImportFile()
{
}
/********************************************************
Function: ExportExe
Description: 导出文件操作,输入为导出文件内容字符串
Input:   CString filestr :导出文件字符串
Output: 
Return: 
Others: 其它说明 
*********************************************************/
int CMastProgInOut::ExportExe(CString filestr)
{
	CFile file;	
	CFileException fileException;
	if(file.Open(this->ExportFileInfo,this->ExportOpenMode,&fileException))//非零：打开成功
	{
		file.Write(filestr,filestr.GetLength());
		file.Close();	
		return 0;
	}
	else
	{
		TRACE("Can't open file %s, error = %u\n",ExportFileInfo, fileException.m_cause);
		return -1;
	}
}
/********************************************************
Function: SetImportFile
Description: 设置导入文件路径信息
Input:   CString filename 
Output: 
Return: 
Others: 其它说明 
*********************************************************/
void CMastProgInOut::SetImportFile(CString filename)
{
	this->ImportFileInfo = filename;
}
/********************************************************
Function: SetExportFile
Description: 设置导出文件路径信息 
Input:   CString filename  UINT openmodeflags
Output: 
Return: 
Others: 其它说明 
*********************************************************/
void CMastProgInOut::SetExportFile(CString filename,UINT openmodeflags)
{
	this->ExportFileInfo = filename;
	this->ExportOpenMode = openmodeflags;
}
/********************************************************
Function: ProcessMirro
Description: 根据不同坐标系，转换x、y位置、值
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessMirro(int ver,HoleInfoNode *firstnode)//
{
	switch(ver)
	{
	case 1:
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=0;
		break;
	case 2:
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=1;
		break;
	case 3:
		m_DrillEnvPara.nXMirror=-1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=1;
		break;
	case 4:
		m_DrillEnvPara.nXMirror=-1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=0;
		break;
	case 5:
		m_DrillEnvPara.nXMirror=-1;
		m_DrillEnvPara.nYMirror=-1;
		m_DrillEnvPara.XYchangeFlag=1;
		break;
	case 6:
		m_DrillEnvPara.nXMirror=-1;
		m_DrillEnvPara.nYMirror=-1;
		m_DrillEnvPara.XYchangeFlag=0;
		break;
	case 7:
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=-1;
		m_DrillEnvPara.XYchangeFlag=0;
		break;
	case 8:
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=-1;
		m_DrillEnvPara.XYchangeFlag=1;
		break;
	default://若未指定坐标系，则默认为第七坐标系
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=0;	
		break;
		
	}
	if(m_DrillEnvPara.nXMirror==-1)//X镜像处理
	{
		XPositonMirro(firstnode);
	}
	if(m_DrillEnvPara.nYMirror==-1)//Y镜像处理
	{
        YPositonMirro(firstnode);
	}
	if(m_DrillEnvPara.XYchangeFlag==1)//XY坐标交换
	{
		XYPositonRevers(firstnode);
	}
	return 0;
}
/********************************************************
Function: GetNewLine1
Description: 
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::GetNewLine1( CString &ins, int ibegin, char *newline ) 
{
	int ilen=0;
	int ipos = ibegin;
	char c;	
	int k=ins.GetLength();//文件长度
	while( (c = ins.GetAt(ibegin +ilen) ) != 0Xd&&(c = ins.GetAt(ibegin +ilen) ) != 0Xa) //未到回车符
	{
		newline[ilen] = c;
		ilen++;
		
		if(ibegin +ilen==k)
		{
			break;
		}
	}
	newline[ilen] = 0;//将原来的回车符用0进行填充
	if(m_LineEndFlag==false)
	{
		return ilen;
	}
	else
	{
		return ilen-1;
	}	
}
/********************************************************
Function: GetTItemStr1
Description: 
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::GetTItemStr1( char *ins, char *outs )
{
	int i,j;
	i=0; //
	j=0;
	
	if( ins[i] != 0 )
	{
		outs[j++]=ins[i++]; //保存第一个字符到输出串
		//处理后面的字符
		while( (ins[i] >= '0' && ins[i] <= '9')  //数字
			|| (ins[i] == '.')                   //小数点
			|| (ins[i] == '+')                   //加号
			|| (ins[i] == '-')                   //减号
			)
		{
			outs[j++] = ins[i++];			
		}
	}
	outs[j] = 0 ;
	
	return j;
}
/********************************************************
Function: ProcessT
Description: c处理钻孔中静态列表1的函数
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessT(char *ins,ToolParaStruct * Toolpara)//
{
	//	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	int errCode = 0;
	int i;//串当前位置
	int j;//串长度
	int iTNum=1;  //刀具号
	int iparaid=0; //参数id
	char buf[256]; //子串
	
	int ival=0;
	double fval=0.0; 
	bool bval = 0;
	
	i=0; j=0;
	
	while( j=GetTItemStr1(&ins[i],buf) ) //不是空串
	{
		switch( buf[0] ) //根据子串首字符进行处理
		{
			//静态参数1
		case 'T'://刀具编号
			if( j == 1 ) return 1;//空串，报错，退出
			ival = atoi(&buf[1]);//从第二个字符开始转换数字
			iTNum = ival;
			if( iTNum < 1 ) iTNum = 1;
			if( iTNum > ATP_Tool_NUM ) iTNum = ATP_Tool_NUM; 
			m_DrillStatic[definetoolnum].iToolNumber = iTNum;//todo
			Toolpara[iTNum].FileStaticPara.iToolNumber=iTNum;
			i+=j; //串头后移
			break;
		case 'C': //刀具直径
			if( j == 1 )//没有参数
			{
				fval = 0.0; //默认为0.0
			}
			else
			{
				fval = atof(&buf[1]);
				if(!METRIC)
					fval=TranslateData(fval);
			}
			if(fval==0.0)
			{
				return 1;
			}
			m_DrillStatic[definetoolnum].m_Diameter = fval;
			Toolpara[iTNum].FileStaticPara.m_Diameter=fval;
			definetoolnum++;//此处自加：忽略未定义直径的刀具
			i+=j; //串头后移
			break;
		case 'M': //刀具类型
			if( j == 1 )
			{
				ival = 1; //默认为类型1，这个地方有点问题。
			}
			else
			{
				ival = atoi(&buf[1]);
			}
			m_DrillStatic[definetoolnum].ToolType = ival;
			Toolpara[iTNum].FileStaticPara.ToolType=ival;
			i+=j;
			break;
		case 'S': //主轴转速
			if( j == 1 ) 
			{
				fval = 0.0; //默认为0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_SpindleSpeed = fval;
			Toolpara[iTNum].FileStaticPara.m_SpindleSpeed=fval;		
			i+=j;
			break;
		case 'F': //进给速度
			if( j == 1 ) 
			{
				fval = 0.0; //默认为0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_RetractRate = fval;
			Toolpara[iTNum].FileStaticPara.m_RetractRate=fval;
			i+=j;
			break;
		case 'B': //回退速度
			if( j == 1 ) 
			{
				fval = 0.0; //默认为0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_PlungeRate = fval;
			Toolpara[iTNum].FileStaticPara.m_PlungeRate=fval;
			i+=j;
			break;
		case 'R': //刀盘号码
			if( j == 1 ) 
			{
				fval = 0; //默认为0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_MagazineNum = (int)fval;
			Toolpara[iTNum].FileStaticPara.m_MagazineNum = (int)fval;
			i+=j;
			break;
		case 'Z': //Z轴平面调整
			if( j == 1 ) 
			{
				fval = 0.0; //默认为0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_Compensate = fval;
			Toolpara[iTNum].FileStaticPara.m_Compensate=fval;
			i+=j;
			break;
		case 'H': //刀具寿命
			if( j == 1 )
			{
				ival = 0;
			}
			else
			{
				ival = atoi(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_ToolLife = ival;
			Toolpara[iTNum].FileStaticPara.m_ToolLife=ival;
			i+=j;
			break;
		case 'P': //分段钻
			if( j == 1 )
			{
				ival = 0;
			}
			else
			{
				ival = atoi(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_Peck = ival;
			Toolpara[iTNum].FileStaticPara.m_Peck=ival;
			i+=j;
			break;
			
		default:
			i+=j;
			break;
		}//endof switch( buf[0] ) //根据子串首字符进行处理
	}//endof while( j=GetTItemStr(&ins[i],buf) ) //不是空串
	return errCode;
}
/********************************************************
Function: ProcessXY
Description: 处理孔位信息的(函数的字符串输入是只包含有XY坐标信息的字符串)
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessXY(char *ins )//
{	
	int errCode = 0;
	int i=0;//串当前位置
	int j=0;//串长度
	int iTNum=1;  //刀具号
	int iparaid=0; //参数id
	char buf[256]; //子串
	
	
	
	while( j=GetTItemStr1(&ins[i],buf) ) //不是空串
	{
		switch( buf[0] ) //根据子串首字符进行处理
		{
			//静态参数1
		case 'X'://刀具编号
			if( j == 1 )//没有参数
			{
				//没有参数报错
				strcpy(drilllocation.x1,"0");
			}
			else
			{
				strcpy(drilllocation.x1,&buf[1]);
			}
			
			i+=j; //串头后移
			break;
		case 'Y': //刀具直径
			if( j == 1 )//没有参数
			{
				strcpy(drilllocation.y1,"0");	
			}
			else
			{
				strcpy(drilllocation.y1,&buf[1]);
			}
			
			i+=j; //串头后移
			break;
		default:
			i+=j;
			break;
		}
	}
	return 0;
}
/********************************************************
Function: strrmv
Description: 将字符串s2从字符串s1中删除，返回删除后s1的指针
Input:    
Output: 
Return: 
Others: 
*********************************************************/
char* CMastProgInOut::strrmv( char *s1, char *s2)//
{ 
	char *w=s1, *r=s1, *p;//w: 写入位置，r： 读入位置   p: 用于处理s2 
	for( p=s2; *r; *w++=*r++ )
		!(*p)&&(w-=(p-s2),p=s2), (*r!=*p)?p=s2:p+=1;
	*p ? *w='\0' : *(w-=(p-s2))='\0';//如果*p=='\0'，说明s1末尾匹配成功了。
	return s1; 
} 
/********************************************************
Function: ProcessData
Description: 
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessData(DrillLocationStruct *q)
{
	char a[50]="";
	char b[50]="";
	char c[50]="";
	if(0!=(m_ndataM+m_ndataN))//以下处理的表明几几制的代码
	{
		
		if(m_LeadTrailFlag==true)//此处表示前补零
		{
			
			if(!strnicmp(q->x1, "-", 1))//以下是对X负坐标进行判断
			{
				if(NULL==strstr(q->x1,"."))//处理没有小数点的
				{
					
					strcpy(q->x2,q->x1);
					for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
						a[i]='0';
					strcat(q->x2,a);
					c[0]='.';
					Insertdecimo(q->x2,c,m_ndataM+1);
					if(METRIC==true)
					{
						drilllocation.Xanalyse=atof(q->x2)*1000;
					}
					else
					{
						drilllocation.Xanalyse=atof(q->x2)*25.4*1000;
					}
				}
				else//此处处理的是直接有小数点的
				{
					if(METRIC==true)//此处处理的是公制的
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100;
						}
					}
					else//此处处理的是英制的
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100*25.4;
						}
					}
				}
			}
			else//以下对正坐标进行处理
			{
				if(NULL==strstr(q->x1,"."))//此处处理不包含小数点
				{
					strcpy(q->x2,q->x1);
					for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
						a[i]='0';
					strcat(q->x2,a);
					c[0]='.';
					Insertdecimo(q->x2,c,m_ndataM);
					if(METRIC==true)
					{
						drilllocation.Xanalyse=atof(q->x2)*1000;
					}
					else
					{
						drilllocation.Xanalyse=atof(q->x2)*25.4*1000;
					}
				}
				else//此处处理包含小数点的
				{
					if(METRIC==true)//此处处理的是公制的
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100;
						}
					}
					else//此处处理的是英制的
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x2)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100*25.4;
						}
					}
				}
			}
			//////////////////////////////////////////////////////////////以下是对Y坐标的实现
			
			if(!strnicmp(q->y1, "-", 1))//以下对负坐标进行处理
			{
				if(NULL==strstr(q->y1,"."))//处理字符中不带小数点的
				{
					
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);j++)
						b[j]='0';
					strcat(q->y2,b);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM+1);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else//处理字符中带小数点的
				{
					if(METRIC==true)//此处处理的是公制的
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Yanalyse=-atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=-atof(q->y2)*100;
						}
					}
					else//此处处理的是英制的
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Yanalyse=-atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=-atof(q->y2)*100*25.4;
						}
					}
				}
			}
			else//以下对y正坐标进行处理
			{
				if(NULL==strstr(q->y1,"."))//此处对没有小数点的数据操作
				{
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2));j++)
						b[j]='0';
					strcat(q->y2,b);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else//此处对有小数点的数据操作
				{
					if(METRIC==true)//此处处理的是公制的
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Yanalyse=atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=atof(q->y2)*100;
						}
					}
					else//此处处理的是英制的
					{
						char *temp=strrmv(q->y1,"-");
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Yanalyse=atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=atof(q->y2)*100*25.4;
						}
					}
				}
			}
			
		}
		else/////////////////////////////////////////////////////////////////下面的这段代码实现的是后补零
		{
			if(!_strnicmp(q->x1, "-", 1))//以下对X负坐标进行处理
			{
				if(NULL==strstr(q->x1,"."))//此处对没有小数点的数据进行处理
				{
					strcpy(q->x2,q->x1);
					for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
						a[i]='0';
					Insertdecimo(q->x2,a,1);
					c[0]='.';
					Insertdecimo(q->x2,c,m_ndataM+1);
					if(METRIC==true)
					{
						drilllocation.Xanalyse=atof(q->x2)*1000;
					}
					else
					{
						drilllocation.Xanalyse=atof(q->x2)*25.4*1000;
					}
				}
				else//此处对有小数点的数据进行处理
				{
					if(METRIC==true)//此处处理的是公制的
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100;
						}
					}
					else//此处处理的是英制的
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100*25.4;
						}
					}
				}
			}
			
			else//以下对X正坐标进行处理
			{
				if(NULL==strstr(q->x1,"."))
				{
					strcpy(q->x2,q->x1);
					for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
						a[i]='0';
					Insertdecimo(q->x2,a,0);
					c[0]='.';
					Insertdecimo(q->x2,c,m_ndataM);
					if(METRIC==true)
					{
						drilllocation.Xanalyse=atof(q->x2)*1000;
					}
					else
					{
						drilllocation.Xanalyse=atof(q->x2)*25.4*1000;
					}
				}
				else
				{
					if(METRIC==true)//此处处理的是公制的
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x2)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100;
						}
					}
					else//此处处理的是英制的
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x2)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100*25.4;
						}
					}
				}
			}//以下是对Y坐标的实现
			
			if(!_strnicmp(q->y1, "-", 1))//以下对负坐标进行处理
			{
				if(NULL==strstr(q->y1,"."))//此处对没有小数点的数据操作
				{
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);j++)
						b[j]='0';
					Insertdecimo(q->y2,b,1);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM+1);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else
				{
					if(METRIC==true)//此处处理的是公制的
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Yanalyse=-atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=-atof(q->y2)*100;
						}
					}
					else//此处处理的是英制的
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Yanalyse=-atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=-atof(q->y2)*100*25.4;
						}
					}
				}
			}
			else//以下Y对正坐标进行处理
			{
				if(NULL==strstr(q->y1,"."))//处理没有小数点
				{
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2));j++)
						b[j]='0';
					Insertdecimo(q->y2,b,0);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else//处理有小数点的
				{
					if(METRIC==true)//此处处理的是公制的
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Yanalyse=atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=atof(q->y2)*100;
						}
					}
					else//此处处理的是英制的
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Yanalyse=atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=atof(q->y2)*100*25.4;
						}
					}
				}
			}	
		}		
	}
	else//以下是前位和后位都采取默认值的情况
	{
		if(METRIC==true)//以下是公制进行处理
		{
			m_ndataM=3;
			m_ndataN=3;
			if(m_LeadTrailFlag==true)//此处表示前补零
			{
				
				if(!_strnicmp(q->x1, "-", 1))//以下是对X的负值进行测试
				{
					if(NULL==strstr(q->x1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100;
						}
						
					}
				}
				else//以下是对X的正值进行处理
				{
					if(NULL==strstr(q->x1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000;//四舍五入还没有实现
					}
					else
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100;
						}
					}
				}
				//以下是对Y坐标的处理
				if(!strnicmp(q->y1, "-", 1))//这里是负的Y坐标
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=-atof(q->y2)*100;
						}
					}
				}
				else//这里是正的Y的坐标
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Yanalyse=atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Yanalyse=atof(q->y2)*100;
						}
					}
				}
			}
			else//此处表示前补零
			{
				
				if(!strnicmp(q->x1, "-", 1))//X坐标负数
				{
					if(NULL==strstr(q->x1,"."))//没有小数点的坐标
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						Insertdecimo(q->x2,a,1);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000;//四舍五入还没有实现
					}
					else//有小数点的坐标
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100;
						}
					}
				}
				else//X坐标的正数
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						Insertdecimo(q->x2,a,0);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000;//四舍五入还没有实现
					}
					else
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x1)*1000;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100;
						}
					}
				}
				//以下是对Y坐标的实现
				if(!strnicmp(q->y1, "-", 1))//此处实现的是y负坐标
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=-atof(q->y2)*100;
						}
					}
				}
				else//对Y的正坐标进行操作
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000;//四舍五入还没有实现
					}
					else
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Xanalyse=atof(q->y1)*1000;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=atof(q->y2)*100;
						}
					}
				}
			}
		}
		else//以下是默认英制 进行处理
		{
			m_ndataM=2;
			m_ndataN=4;
			if(m_LeadTrailFlag=true)//此处表示前补零
			{
				
				if(!strnicmp(q->x1, "-", 1))//以下是对X的负坐标进行操作
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100*25.4;
						}
					}
				}
				else//以下是对X的正坐标进行操作
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100*25.4;
						}
					}
				}
				//以下是对Y坐标的处理
				if(!strnicmp(q->y1, "-", 1))//以下是对Y的负坐标进行处理
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=-atof(q->y2)*100*25.4;
						}
					}
				}
				else//以下是对Y的正坐标进行处理
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Xanalyse=atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=atof(q->y2)*100*25.4;
						}
					}
				}
			}
			else//此处表示前补零
			{
				
				if(!strnicmp(q->x1, "-", 1))//此处是X的负坐标进行处理
				{
					if(NULL==strstr(q->x1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						Insertdecimo(q->x2,a,1);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->x1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=-atof(q->x2)*100*25.4;
						}
					}
				}
				else//此处是X的正坐标进行处理
				{
					if(NULL==strstr(q->x1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						Insertdecimo(q->x2,a,0);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						if(*(q->x1)>='0'&&*(q->x1)<='9')
						{
							drilllocation.Xanalyse=atof(q->x1)*1000*25.4;
						}
						else
						{
							strcpy(q->x2,strrmv(q->x1,"."));
							drilllocation.Xanalyse=atof(q->x2)*100*25.4;
						}
					}
				}
				//以下是对Y坐标的实现
				if(!strnicmp(q->y1, "-", 1))//以下对Y的负坐标进行处理
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						char *temp=strrmv(q->y1,"-");
						if(*(temp)>='0'&&*(temp)<='9')
						{
							drilllocation.Xanalyse=-atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=-atof(q->y2)*100*25.4;
						}
					}
				}
				else//以下对Y的正坐标进行处理
				{
					if(NULL==strstr(q->y1,"."))//以下是对没有小数点进行处理
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//四舍五入还没有实现
					}
					else
					{
						if(*(q->y1)>='0'&&*(q->y1)<='9')
						{
							drilllocation.Xanalyse=atof(q->y1)*1000*25.4;
						}
						else
						{
							strcpy(q->y2,strrmv(q->y1,"."));
							drilllocation.Xanalyse=atof(q->y2)*100*25.4;
						}
					}
				}
			}
			
		}
	}
	return 0;
}
/********************************************************
Function: Insertdecimo
Description: 将str2中的字符按照指定位置插入到str1中
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::Insertdecimo(char*str1,char*str2,int n)//
{
	for(int k=0;k<=(int)strlen(str1)-n;k++)
		str1[strlen(str1)+strlen(str2)-k]=str1[strlen(str1)-k];
	for(int i=0;i<(int)strlen(str2);i++)
		str1[i+n]=str2[i];
	return 0;
}
/********************************************************
Function: Insertdecimo
Description: decimal表示四舍五入保留的位置
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::Round(double a)    //
{	
	return (a>=0? (int)(a+0.5):(int)(a-0.5));
}
/********************************************************
Function: Listamend
Description: 此函数实现的功能：将孔位数据节点中的XY坐标按照传入的修正值进行修改
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::Listamend(HoleInfoNode *q,int x,int y) //
{
	while(NULL!=q->pnext)
	{
		q->position.nXs+=x;
		q->position.nYs+=y;
	}
	return 0;
}
/********************************************************
Function: ProcessTrough
Description: 此函数功能：根据输入的精度将起始和终点坐标之间的
距离分解成多个坐标孔位信息并存入链表（利用2分法进行坐标的分解）
::传入的参数的是两圆的切线和交点之间的距离
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessTrough(double p,ToolParaStruct * Toolpara)//
{
	m_first1=NULL;
	m_first=NULL;
	int i=0;
	double XYdistance=0;
	LinkStruct *temp1=NULL;
	//CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	double diameter;
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter*1000;//得到半径 半径？
	//此处半径为加工问价中的半径，若在“刀具转换”菜单中修改刀具直径，此处需要用新的半径/直径？
	
	AddLinkNote(xylocation1.XPosition[0],xylocation1.YPosition[0]);
	AddLinkNote1(xylocation1.XPosition[0],xylocation1.YPosition[0]);
	AddLinkNote(xylocation1.XPosition[1],xylocation1.YPosition[1]);
	AddLinkNote1(xylocation1.XPosition[1],xylocation1.YPosition[1]);
	XYdistance=sqrt(diameter*diameter-(diameter-p)*(diameter-p))/2;
	while(fabs(m_first->XLocation-m_first->pnext->XLocation)>XYdistance||fabs(m_first->YLocation-m_first->pnext->YLocation)>XYdistance)
	{
		m_Current=m_first;
		while(NULL!=m_Current->pnext)
		{
			i++;
			m_Current=m_Current->pnext;
		}
		m_Current=m_first;
		while(i>0)
		{
			temp1=m_Current->pnext;
			m_temp=(LinkStruct*)malloc(sizeof(LinkStruct));
			m_temp->XLocation=(m_Current->XLocation+m_Current->pnext->XLocation)/2;
			m_temp->YLocation=(m_Current->YLocation+m_Current->pnext->YLocation)/2; 
			
			m_temp->pnext=m_Current->pnext;
			m_Current->pnext=m_temp;
			m_Current=temp1;
			i=i-1;
			if(fabs(m_first->XLocation-m_temp->XLocation)<p&&fabs(m_first->YLocation-m_temp->YLocation)<p)
				break;
			AddLinkNote1(m_temp->XLocation,m_temp->YLocation);
		}
	}
	m_Current=m_first;
	while(NULL!=m_Current->pnext)
	{
		m_Previous=m_Current;
		m_Current=m_Current->pnext;
		free(m_Previous);
		m_Previous=NULL;
	}
	m_Current1=m_first1;
	while(NULL!=m_Current1)
	{
		m_Previous1=m_Current1;
		xylocation.XPosition[0]=m_Current1->XLocation;
		xylocation.YPosition[0]=m_Current1->YLocation;
		DrillNumber++;
		Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
		xylocation.XPosition[1]=xylocation.XPosition[0];
		xylocation.YPosition[1]=xylocation.YPosition[0];
		AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
		m_Current1=m_Current1->pnext;
		free(m_Previous1);
		m_Previous1=NULL;
	}
	return 0;
}
/********************************************************
Function: ProcessEightPin
Description:函数功能：根据得到的起始点和原点坐标计算出一个八角形的孔位坐标
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessEightPin()//
{
	double EightPin[8][2];//用于八角形封装的八个坐标的临时数组(0，0存x坐标；0，1存y坐标)
	if(xylocation2.XPosition[m_FlagEightPin-1]==xylocation2.XPosition[m_FlagEightPin])
	{
		if(xylocation2.YPosition[m_FlagEightPin-1]>xylocation2.YPosition[m_FlagEightPin])
		{
			EightPin[0][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[0][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[1][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[1][1]=xylocation2.YPosition[m_FlagEightPin-1]-10.16*1000;
			
			EightPin[2][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000/2;
			EightPin[2][1]=xylocation2.YPosition[m_FlagEightPin];
			
			EightPin[3][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000/2;
			EightPin[3][1]=xylocation2.YPosition[m_FlagEightPin];
			
			EightPin[4][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[4][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[5][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[5][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[6][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[6][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
			
			EightPin[7][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[7][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
		}
		else
		{
			EightPin[0][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[0][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[1][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[1][1]=xylocation2.YPosition[m_FlagEightPin-1]+10.16*1000;
			
			EightPin[2][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000/2;
			EightPin[2][1]=xylocation2.YPosition[m_FlagEightPin];
			
			EightPin[3][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000/2;
			EightPin[3][1]=xylocation2.YPosition[m_FlagEightPin];
			
			EightPin[4][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[4][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[5][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[5][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[6][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[6][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
			
			EightPin[7][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[7][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
		}
	}
	else if(xylocation2.YPosition[m_FlagEightPin-1]==xylocation2.YPosition[m_FlagEightPin])
	{
		if(xylocation2.XPosition[m_FlagEightPin-1]>xylocation2.XPosition[m_FlagEightPin])
		{
			EightPin[0][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[0][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[1][0]=xylocation2.XPosition[m_FlagEightPin-1]-10.16*1000;
			EightPin[1][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[2][0]=xylocation2.XPosition[m_FlagEightPin];
			EightPin[2][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000/2;
			
			EightPin[3][0]=xylocation2.XPosition[m_FlagEightPin];
			EightPin[3][1]=xylocation2.YPosition[m_FlagEightPin]-10.16*1000/2;
			
			EightPin[4][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[4][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[5][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[5][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[6][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[6][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
			
			EightPin[7][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[7][1]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
		}
		else
		{
			EightPin[0][0]=xylocation2.XPosition[m_FlagEightPin-1];
			EightPin[0][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[1][0]=xylocation2.XPosition[m_FlagEightPin-1]+10.16*1000;
			EightPin[1][1]=xylocation2.YPosition[m_FlagEightPin-1];
			
			EightPin[2][0]=xylocation2.XPosition[m_FlagEightPin];
			EightPin[2][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000/2;
			
			EightPin[3][0]=xylocation2.XPosition[m_FlagEightPin];
			EightPin[3][1]=xylocation2.YPosition[m_FlagEightPin]-10.16*1000/2;
			
			EightPin[4][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[4][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[5][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[5][1]=xylocation2.YPosition[m_FlagEightPin]+10.16*1000*sin(Pi/4)/2;
			
			EightPin[6][0]=xylocation2.XPosition[m_FlagEightPin]-10.16*1000*cos(Pi/4)/2;
			EightPin[6][1]=xylocation2.YPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
			
			EightPin[7][0]=xylocation2.XPosition[m_FlagEightPin]+10.16*1000*cos(Pi/4)/2;
			EightPin[7][1]=xylocation2.YPosition[m_FlagEightPin]-10.16*1000*sin(Pi/4)/2;
		}
		
		for(int i=0;i<8;i++)		
		{	
			xylocation.XPosition[0]=EightPin[i][0];
			xylocation.YPosition[0]=EightPin[i][1];
			DrillNumber++;
			//Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
			xylocation.XPosition[1]=xylocation.XPosition[0];
			xylocation.YPosition[1]=xylocation.YPosition[0];
			AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
		}
		
	}
	return 0;
}
/********************************************************
Function: ProcessDualLine
Description:根据起点和终点坐标计算出双列直插的其他坐标并存入孔位数据链表
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessDualLine()
{
	bool DirectionFlag=true;//用于储存判断出来的XY的方向(true为延X方向)
	int tempnumX=0;//用于临时存储x方向计算出来的引脚数
	int tempnumY=0;//用于临时储存y方向计算出来的引脚数
	if(xylocation3.YPosition[2]==fabs(xylocation3.XPosition[0]-xylocation3.XPosition[1]))
	{
		DirectionFlag=false;
		tempnumY=Round(fabs(xylocation3.YPosition[0]-xylocation3.YPosition[1])/xylocation3.XPosition[2]);
	}
	else
	{
		DirectionFlag=true;
		tempnumX=Round(fabs(xylocation3.XPosition[0]-xylocation3.XPosition[1])/xylocation3.XPosition[2]);
	}
	if(DirectionFlag)//延X方向处理
	{
		if(xylocation3.XPosition[0]>xylocation3.XPosition[1])//延X负方向排列
		{
			if(fabs(xylocation3.XPosition[0]-(tempnumX*xylocation3.XPosition[2]+xylocation3.XPosition[1]))>1.27*1000)
			{
				//此处对于间距误差进行报错
				return 1;
			}
			else
			{
				for(int i=0;i<=tempnumX;i++)
				{
					xylocation.XPosition[0]=xylocation3.XPosition[0]-xylocation3.XPosition[2]*i;
					xylocation.YPosition[0]=xylocation3.YPosition[0];
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					
				}
				if(xylocation3.YPosition[0]>xylocation.YPosition[1])//延Y的负方向
				{
					xylocation3.YPosition[0]=xylocation3.YPosition[0]-xylocation3.YPosition[2];
					for(int j=0;j<=tempnumX;j++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0]-xylocation3.XPosition[2]*j;
						xylocation.YPosition[0]=xylocation3.YPosition[0];
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
				else//延Y的正方向
				{
					xylocation3.YPosition[0]=xylocation3.YPosition[0]+xylocation3.YPosition[2];
					for(int k=0;k<=tempnumX;k++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0]-xylocation3.XPosition[2]*k;
						xylocation.YPosition[0]=xylocation3.YPosition[0];
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
			}
		}
		else//延X的正方向
		{
			if(fabs(xylocation3.XPosition[1]-(tempnumX*xylocation3.XPosition[2]+xylocation3.XPosition[0]))>1.27*1000)
			{
				//此处对于间距误差进行报错
				return 1;
			}
			else
			{
				for(int i=0;i<=tempnumX;i++)
				{
					xylocation.XPosition[0]=xylocation3.XPosition[0]+xylocation3.XPosition[2]*i;
					xylocation.YPosition[0]=xylocation3.YPosition[0];
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					
				}
				if(xylocation3.YPosition[0]>xylocation3.YPosition[1])//延Y的负方向
				{
					xylocation3.YPosition[0]=xylocation3.YPosition[0]-xylocation3.YPosition[2];
					for(int j=0;j<=tempnumX;j++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0]+xylocation3.XPosition[2]*j;
						xylocation.YPosition[0]=xylocation3.YPosition[0];
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
				else//延Y的正方向
				{
					xylocation3.YPosition[0]=xylocation3.YPosition[0]+xylocation3.YPosition[2];
					for(int k=0;k<=tempnumX;k++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0]+xylocation3.XPosition[2]*k;
						xylocation.YPosition[0]=xylocation3.YPosition[0];
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					}
				}
			}
		}
	}
	else//此处处理Y方向的双列直插
	{
		if(xylocation3.YPosition[0]>xylocation3.YPosition[1])//延Y向下方向排列
		{
			if(fabs(xylocation3.YPosition[0]-(tempnumY*xylocation3.XPosition[2]+xylocation3.YPosition[1]))>1.27*1000)
			{
				//此处对于间距误差进行报错
				return 1;
			}
			else
			{
				for(int i=0;i<=tempnumY;i++)
				{
					xylocation.XPosition[0]=xylocation3.XPosition[0];
					xylocation.YPosition[0]=xylocation3.YPosition[0]-xylocation3.XPosition[2]*i;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					
				}
				if(xylocation3.XPosition[0]>xylocation.XPosition[1])//延X的负方向
				{
					xylocation3.XPosition[0]=xylocation3.XPosition[0]-xylocation3.XPosition[2];
					for(int j=0;j<=tempnumY;j++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0];
						xylocation.YPosition[0]=xylocation3.YPosition[0]-xylocation3.XPosition[2]*j;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
				else//延X的正方向
				{
					xylocation3.XPosition[0]=xylocation3.XPosition[0]+xylocation3.XPosition[2];
					for(int k=0;k<=tempnumY;k++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0];
						xylocation.YPosition[0]=xylocation3.YPosition[0]-xylocation3.XPosition[2]*k;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
			}
		}
		else//延Y向上的方向排列
		{
			if(fabs(xylocation3.YPosition[1]-(tempnumY*xylocation3.XPosition[2]+xylocation3.YPosition[0]))>1.27*1000)
			{
				//此处对于间距误差进行报错
				return 1;
			}
			else
			{
				for(int i=0;i<=tempnumY;i++)
				{
					xylocation.XPosition[0]=xylocation3.XPosition[0];
					xylocation.YPosition[0]=xylocation3.YPosition[0]+xylocation3.XPosition[2]*i;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					
				}
				if(xylocation3.XPosition[0]>xylocation3.XPosition[1])//延X轴负方向排列
				{
					xylocation3.XPosition[0]=xylocation3.XPosition[0]-xylocation3.YPosition[2];
					for(int j=0;j<=tempnumY;j++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0];
						xylocation.YPosition[0]=xylocation3.YPosition[0]+xylocation3.XPosition[2]*j;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
						
					}
				}
				else//延X轴正方向排列
				{
					xylocation3.XPosition[0]=xylocation3.XPosition[0]+xylocation3.YPosition[2];
					for(int k=0;k<=tempnumY;k++)
					{
						xylocation.XPosition[0]=xylocation3.XPosition[0];
						xylocation.YPosition[0]=xylocation3.YPosition[0]+xylocation3.XPosition[2]*k;
						DrillNumber++;
						Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
						xylocation.XPosition[1]=xylocation.XPosition[0];
						xylocation.YPosition[1]=xylocation.YPosition[0];
						AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
					}
				}
			}
		}
	}
	m_lastLocation=Current;//此处将块的最后一个坐标当作块的末尾地址
	return 0;
}
/********************************************************
Function: ProcessCircle
Description:通过传入的参数计算形成圆的每个圆心的坐标 传入的参数是圆切线和圆相交点之间的距离
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessCircle(double p,ToolParaStruct * Toolpara)
{
	//CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	double angleNum=0;//由输入的间距值计算出来的角度
	double diameter;
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter*1000;//得到半径
	xylocation4.XPosition[2]=xylocation4.XPosition[0]+xylocation4.XPosition[1];
	xylocation4.YPosition[2]=xylocation4.YPosition[0];
	angleNum=asin(sqrt(fabs(diameter*diameter-(diameter-p)*(diameter-p)))/(xylocation4.XPosition[1]/2))*2;
	for(double i=0;i<360;i+=angleNum)
	{
		xylocation.XPosition[0]=xylocation4.XPosition[2]-(xylocation4.XPosition[1]-xylocation4.XPosition[1]*cos(Pi/180*i));//计算在圆周上的位置
		xylocation.YPosition[0]=xylocation4.YPosition[2]+xylocation4.XPosition[1]*sin(Pi/180*i);
		xylocation.XPosition[0]-=(diameter/2)*cos(Pi/180*i);
		xylocation.YPosition[0]-=(diameter/2)*sin(Pi/180*i);
		DrillNumber++;
		Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
		xylocation.XPosition[1]=xylocation.XPosition[0];
		xylocation.YPosition[1]=xylocation.YPosition[0];
		AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));	
	}
	return 0;
}
/********************************************************
Function: ProcessArray
Description:根据得到相映的int型数组得到相映的坐标位置并输入链表中(默认处理的数组是7行4列)
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessArray(int *p,double a,double b,ToolParaStruct * Toolpara)//函数功能： 
{
	//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//获取指向主窗口的句柄
	//a是x的起始坐标 b是y的起始坐标
	double diameter;
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter;;//用于临时储存从atp文件中得到的相映直径
	if(m_XYdirection==1)
	{
		for(int numx=0;numx<7;numx++)
			for(int numy=0;numy<4;numy++)
			{
				if(0!=*(p+numx*4+numy))
				{
					//xylocation.XPosition[0]=a-numy*diameter*1.2*1000;
					//	xylocation.YPosition[0]=b-numx*diameter*1.2*1000;
					xylocation.XPosition[0]=a+numy*diameter*1.2*1000;
					xylocation.YPosition[0]=b+numx*diameter*1.2*1000;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));	
				}
			}
	}
	else
	{
		for(int numx=0;numx<7;numx++)
			for(int numy=0;numy<4;numy++)
			{
				
				if(0!=*(p+numx*4+numy))
				{
					//	xylocation.XPosition[0]=a-numx*diameter*1.2*1000;
					//	xylocation.YPosition[0]=b+numy*diameter*1.2*1000;
					xylocation.XPosition[0]=a-numx*diameter*1.2*1000;
					xylocation.YPosition[0]=b+numy*diameter*1.2*1000;
					DrillNumber++;
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
				}
			}
			/*		m_Current=m_first->pnext;
			while(NULL!=m_Current)
			{
			m_Current->XLocation=m_first->XLocation-m_Current->YLocation;
			m_Current->YLocation=m_first->YLocation+m_Current->XLocation;
			xylocation.XPosition[0]=m_Current->XLocation;
			xylocation.YPosition[0]=m_Current->YLocation;
			AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]+drilllocation.Xoriganposition),Round(xylocation.YPosition[0]+drilllocation.Yoriganposition));	
			m_Current=m_Current->pnext;
	}*/
	/*	m_Current=m_first;
	while(NULL!=m_Current)
	{
	m_Previous=m_Current;
	m_Current=m_Current->pnext;
	free(m_Previous);
	m_Previous=NULL;
	}*/
			
	}
	return 0;
}
/********************************************************
Function: ProcessArray1
Description:处理a[7]的一维数组，将其转换为能被ProcessArray处理的多维数组
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessArray1(char *str,double xPosition,double yPosition,ToolParaStruct * Toolpara)//函数功能：
{	
	static int k=1;
	int *tenpNum=&TempArray[0][0];
	double Xdirection=0;
	double Ydirection=0;
	
	while('\0'!=*str)
	{
		for(int i=0;i<40;i++)//此处默认所需打印的字符串最多有40个空字符
		{
			if(*str==m_character[i].m_letter)
			{
				
				for(int k=0;k<7;k++)
				{
					int a=m_character[i].a[k];
					switch(m_character[i].a[k])
					{
					case 0:
						TempArray[k][0]=0;TempArray[k][1]=0;TempArray[k][2]=0;TempArray[k][3]=0;
						break;
					case 1:
						TempArray[k][0]=0;TempArray[k][1]=0;TempArray[k][2]=0;TempArray[k][3]=1;
						break;
					case 2:
						TempArray[k][0]=0;TempArray[k][1]=0;TempArray[k][2]=1;TempArray[k][3]=0;
						break;
					case 3:
						TempArray[k][0]=0;TempArray[k][1]=0;TempArray[k][2]=1;TempArray[k][3]=1;
						break;
					case 4:
						TempArray[k][0]=0;TempArray[k][1]=1;TempArray[k][2]=0;TempArray[k][3]=0;
						break;
					case 5:
						TempArray[k][0]=0;TempArray[k][1]=1;TempArray[k][2]=0;TempArray[k][3]=1;
						break;
					case 6:
						TempArray[k][0]=0;TempArray[k][1]=1;TempArray[k][2]=1;TempArray[k][3]=0;
						break;
					case 7:
						TempArray[k][0]=0;TempArray[k][1]=1;TempArray[k][2]=1;TempArray[k][3]=1;
						break;
					case 8:
						TempArray[k][0]=1;TempArray[k][1]=0;TempArray[k][2]=0;TempArray[k][3]=0;
						break;
					case 9:
						TempArray[k][0]=1;TempArray[k][1]=0;TempArray[k][2]=0;TempArray[k][3]=1;
						break;	
					case 10:
						TempArray[k][0]=1;TempArray[k][1]=0;TempArray[k][2]=1;TempArray[k][3]=0;
						break;
					case 11:
						TempArray[k][0]=1;TempArray[k][1]=0;TempArray[k][2]=1;TempArray[k][3]=1;
						break;
					case 12:
						TempArray[k][0]=1;TempArray[k][1]=1;TempArray[k][2]=0;TempArray[k][3]=0;
						break;
					case 13:
						TempArray[k][0]=1;TempArray[k][1]=1;TempArray[k][2]=0;TempArray[k][3]=1;
						break;
					case 14:
						TempArray[k][0]=1;TempArray[k][1]=1;TempArray[k][2]=1;TempArray[k][3]=0;
						break;
					case 15:
						TempArray[k][0]=1;TempArray[k][1]=1;TempArray[k][2]=1;TempArray[k][3]=1;
						break;
					default:
						//此处是容错机制，进行报错处理
						break;
					}
					
				}
				if(1==k)
				{
					xylocation.XPosition[0]=xPosition;
					xylocation.YPosition[0]=yPosition;
					Xdirection=xylocation.XPosition[0];//X的起始点坐标
					Ydirection=xylocation.YPosition[0];//Y的起始点坐标
					k++;
				}
				else
				{
					Xdirection=xylocation.XPosition[0];//X的起始点坐标
					Ydirection=xylocation.YPosition[0];//Y的起始点坐标
				}
				ProcessArray(tenpNum,xylocation.XPosition[0],xylocation.YPosition[0],Toolpara);
				//				CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//获取指向主窗口的句柄
				double diameter;
				diameter=Toolpara[m_toolnumber].FileStaticPara.m_Diameter;//用于临时储存从atp文件中得到的相映直径
				if(m_XYdirection==1)
				{
					
					xylocation.XPosition[0]=Xdirection+diameter*5*1000*1.2;
					xylocation.YPosition[0]=Ydirection;
				}
				else
				{
					xylocation.XPosition[0]=Xdirection;
					xylocation.YPosition[0]=Ydirection+diameter*5*1000*1.2;
					
				}
				
			}
		}
		str++;
	}
	
	return 0;
}
/********************************************************
Function: AddPosition
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
bool CMastProgInOut::AddPosition(int ToolNum,
								 int Toolform,
								 int linenum,
								 int Xs,
								 int Ys)
{	
	
	Current=(HoleInfoNode*)malloc(sizeof(HoleInfoNode));
	if(m_OriPosition==NULL)
		m_OriPosition=Current;
	if(Previous!=NULL)
		Previous->pnext=Current;
	
	Current->m_LINENUM=linenum;
	Current->m_Toolform=Toolform;
	Current->m_ToolNum=ToolNum;
	Current->position.nXs=Xs;
	Current->position.nYs=Ys;
	Current->pnext=NULL;
	Previous=Current;
	return true;
	
}
/********************************************************
Function: AddLinkNote
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
bool CMastProgInOut::AddLinkNote(double x,double y)
{
	m_Current=(LinkStruct*)malloc(sizeof(LinkStruct));
	if(NULL==m_first)
		m_first=m_Current;
	if(m_Previous!=NULL)
		m_Previous->pnext=m_Current;
	m_Current->XLocation=x;
	m_Current->YLocation=y;
	m_Current->pnext=NULL;
	m_Previous=m_Current;
	return true;
	
}
/********************************************************
Function: AddLinkNote1
Description:向临时的链表中添加节点
Input:    
Output: 
Return: 
Others: 
*********************************************************/
bool CMastProgInOut::AddLinkNote1(double x,double y)
{
	m_Current1=(LinkStruct*)malloc(sizeof(LinkStruct));
	if(NULL==m_first1)
		m_first1=m_Current1;
	if(m_Previous1!=NULL)
		m_Previous1->pnext=m_Current1;
	m_Current1->XLocation=x;
	m_Current1->YLocation=y;
	m_Current1->pnext=NULL;
	m_Previous1=m_Current1;
	return true;
	
}
/********************************************************
Function: DeletePosition
Description:完成根据起始坐标删除链表节点
Input:    
Output: 
Return: 
Others: 
*********************************************************/
bool CMastProgInOut::DeletePosition(int x,int y)//
{
	Current=m_OriPosition;
	if(Current->position.nXs==x&&Current->position.nYs==y)
	{
		free(m_OriPosition);
		m_OriPosition=NULL;
	}
	else
	{
		while(Current!=NULL)
		{
			if(Current->pnext->position.nXs==x&&Current->pnext->position.nYs==y)
			{
				Previous=Current->pnext;
				Current->pnext=Current->pnext->pnext;
				free(Previous);
				Previous=NULL;//释放指针以后将指针置空 否则将成为野指针
				break;
			}
			else
				Current=Current->pnext;
		}
	}
	return true;
}
/********************************************************
Function: GetBoundryNote
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
bool CMastProgInOut::GetBoundryNote(HoleInfoNode *firstnode,CodeBoundary *codeboundary)
{
	//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//获取指向主窗口的句柄
	if(NULL==firstnode)
	{
		return false;//表示没有孔位信息报错
	}
	m_tempLocation=firstnode->pnext;	//此处要求必须要有程序原点的设定
	if(NULL!=m_tempLocation)
	{
		codeboundary->xMax=m_tempLocation->position.nXs;
		codeboundary->xMin=m_tempLocation->position.nXs;
		codeboundary->yMax=m_tempLocation->position.nYs;
		codeboundary->yMin=m_tempLocation->position.nYs;
		m_tempLocation=m_tempLocation->pnext;
		while(NULL!=m_tempLocation)
		{
			if(codeboundary->xMax<m_tempLocation->position.nXs)
			{
				codeboundary->xMax=m_tempLocation->position.nXs;
			}
			else if(codeboundary->xMin>m_tempLocation->position.nXs)
			{
				codeboundary->xMin=m_tempLocation->position.nXs;
			}
			else
			{
				//不做处理
			}
			if(codeboundary->yMax<m_tempLocation->position.nYs)
			{
				codeboundary->yMax=m_tempLocation->position.nYs;
			}
			else if(codeboundary->yMin>m_tempLocation->position.nYs)
			{
				codeboundary->yMin=m_tempLocation->position.nYs;
			}
			else
			{
				//不做处理
			}
			
			m_tempLocation=m_tempLocation->pnext;
			
		}
	}
	else
	{
		//此处处理空链表的代码
	}
	return true;
}
/********************************************************
Function: XYPositonRevers
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::XYPositonRevers(HoleInfoNode *note)
{
	HoleInfoNode *tempLocation=note;
	while(NULL!=tempLocation)
	{
		xylocation.XPosition[0]=tempLocation->position.nYs;
		xylocation.YPosition[0]=tempLocation->position.nXs;
		tempLocation->position.nXs=Round(xylocation.XPosition[0]);
		tempLocation->position.nYs=Round(xylocation.YPosition[0]);
		tempLocation=tempLocation->pnext;
	}
	/*xylocation.XPosition[0]=tempLocation->position.nYs;
	xylocation.YPosition[0]=tempLocation->position.nXs;
	tempLocation->position.nXs=Round(xylocation.XPosition[0]);
	tempLocation->position.nYs=Round(xylocation.YPosition[0]);*/
	return 0;
}
/********************************************************
Function: XPositonMirro
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::XPositonMirro(HoleInfoNode *note)
{
	HoleInfoNode *tempLocation=note;
	while(NULL!=tempLocation)
	{
		if(0==tempLocation->m_Toolform)
		{
			xylocation.XPosition[0]=-tempLocation->position.nXs;
			xylocation.YPosition[0]=tempLocation->position.nYs;
			tempLocation->position.nXs=Round(xylocation.XPosition[0]);
			tempLocation->position.nYs=Round(xylocation.YPosition[0]);
		}
		tempLocation=tempLocation->pnext;
	}
	
	return 0;
}
/********************************************************
Function: YPositonMirro
Description:
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::YPositonMirro(HoleInfoNode *note)
{
	HoleInfoNode *tempLocation=note;
	while(NULL!=tempLocation)
	{
		if(0==tempLocation->m_Toolform)
		{
			xylocation.XPosition[0]=tempLocation->position.nXs;
			xylocation.YPosition[0]=-tempLocation->position.nYs;
			tempLocation->position.nXs=Round(xylocation.XPosition[0]);
			tempLocation->position.nYs=Round(xylocation.YPosition[0]);
		}
		tempLocation=tempLocation->pnext;
	}
	
	return 0;
}

/********************************************************
Function: TranslateStr
Description:将字符串中的小写字母转化成大写字母
Input:    
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::TranslateStr(char *p)
{
	if(NULL==p)
		return;
	while('\0'!=*p)
	{
		if(*p<='z'&&*p>='a')
		{
			*p=*p-('a'-'A');
		}
		p++;
	}
}

/********************************************************
Function: translateData
Description:将英制的小数转化为公制的毫米
Input:  float data输入的英制小数;  
Output: 
Return: float 返回的公制毫米数
Others: 
*********************************************************/
double CMastProgInOut::TranslateData(double data)
{
	return data*2.54*10;
}
/********************************************************
Function: FreeDrillLink
Description:将英制的小数转化为公制的毫米
Input:  float data输入的英制小数;  
Output: 
Return: float 返回的公制毫米数
Others: 
*********************************************************/
void CMastProgInOut::FreeDrillLink(HoleInfoNode *firstnode)
{
	while(firstnode->pnext)
	{
		m_tempLocation=firstnode->pnext;
		firstnode->pnext=m_tempLocation->pnext;
		free(m_tempLocation);
	}	
	//	free(firstnode);
	//	firstnode=NULL;
	m_Previous=NULL;//释放完占用的空间后将所有指针制空
	m_first=NULL;
	m_Previous1=NULL;
	m_first1=NULL;
	m_temp=NULL;
	m_PreviousCode=NULL;
	m_CurrentCode=NULL;
	m_firstCode=NULL;
	m_Current=NULL;
	m_tempLocation=NULL;
	Previous=NULL;
	Current=NULL;
	m_pnext=NULL;
	m_tempLocation1=NULL;
	m_lastLocation=NULL;
}
/********************************************************
Function: ProcessRelativeMod
Description://处理相对坐标模式
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessRelativeMod(char *ins)
{
	ProcessXY(ins);
    ProcessData(&drilllocation);
	if(NULL!=strstr(ins,"X")&&NULL!=strstr(ins,"Y"))
	{
		//ProcessXY(ins);
		//ProcessData(&drilllocation);
		xylocation.XPosition[0]+=drilllocation.Xanalyse;
		xylocation.YPosition[0]+=drilllocation.Yanalyse;
	}
	else if(NULL!=strstr(ins,"X")&&NULL==strstr(ins,"Y"))
	{
		//	ProcessXY(ins);
		//ProcessData(&drilllocation);
		xylocation.XPosition[0]+=drilllocation.Xanalyse;
	}
	else if(NULL==strstr(ins,"X")&&NULL!=strstr(ins,"Y"))
	{
		//	ProcessXY(ins);
		//	ProcessData(&drilllocation);
		xylocation.YPosition[0]+=drilllocation.Yanalyse;
	}
	DrillNumber++;
	Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
	xylocation.XPosition[1]=xylocation.XPosition[0];
	xylocation.YPosition[1]=xylocation.YPosition[0];
	AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
}
/********************************************************
Function: ProcessAbsoluteMod
Description:处理绝度坐标模式
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessAbsoluteMod(char *ins)
{
	ProcessXY(ins);
	ProcessData(&drilllocation);
	if(NULL!=strstr(ins,"X")&&NULL!=strstr(ins,"Y"))
	{
		//	ProcessXY(ins);
		//	ProcessData(&drilllocation);
		xylocation.XPosition[0]=drilllocation.Xanalyse;
		xylocation.YPosition[0]=drilllocation.Yanalyse;
	}
	else if(NULL!=strstr(ins,"X")&&NULL==strstr(ins,"Y"))
	{
		//	ProcessXY(ins);
		//	ProcessData(&drilllocation);
		xylocation.XPosition[0]=drilllocation.Xanalyse;
	}
	else if(NULL==strstr(ins,"X")&&NULL!=strstr(ins,"Y"))
	{
		//	ProcessXY(ins);
		//	ProcessData(&drilllocation);
		xylocation.YPosition[0]=drilllocation.Yanalyse;
	}
	DrillNumber++;
	Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
	xylocation.XPosition[1]=xylocation.XPosition[0];
	xylocation.YPosition[1]=xylocation.YPosition[0];
	AddPosition(m_toolnumber,0,m_LineNum,Round(xylocation.XPosition[0]),Round(xylocation.YPosition[0]));
}
/********************************************************
Function: ProcessSlotPattern
Description:处理线槽孔
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessSlotPattern(char *ins,ToolParaStruct * Toolpara)//
{
	char *tempstr=strtok(ins,"G");
	ProcessXY(tempstr);
	ProcessData(&drilllocation);
	xylocation1.XPosition[0]=drilllocation.Xanalyse;
	xylocation1.YPosition[0]=drilllocation.Yanalyse;
	tempstr=strtok(NULL, "G");
	ProcessXY(tempstr);
	ProcessData(&drilllocation);
	xylocation1.XPosition[1]=drilllocation.Xanalyse;
	xylocation1.YPosition[1]=drilllocation.Yanalyse;
	ProcessTrough(200,Toolpara);
}
/********************************************************
Function: ProcessCirclePattern
Description:处理圆槽孔
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessCirclePattern(char *ins,ToolParaStruct * Toolpara)
{
	char *tempstr=strtok(ins,"G");
	ProcessXY(tempstr);
	ProcessData(&drilllocation);
	xylocation4.XPosition[0]=drilllocation.Xanalyse;
	xylocation4.YPosition[0]=drilllocation.Yanalyse;
	tempstr=strtok(NULL, "G");
	ProcessXY(tempstr);
	ProcessData(&drilllocation);
	xylocation4.XPosition[1]=drilllocation.Xanalyse/2;
	ProcessCircle(20,Toolpara);//此处默认交点和圆弧最外端之间的距离为10um
}
/********************************************************
Function: ProcessCannedTextPattern
Description:处理字符串孔
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessCannedTextPattern(char *ins,ToolParaStruct * Toolpara)
{
	ProcessXY(ins);
	ProcessData(&drilllocation);
	xylocation.XPosition[0]=drilllocation.Xanalyse;
	xylocation.YPosition[0]=drilllocation.Yanalyse;
	char *tempstring=tempstr1;		
	ProcessArray1(tempstring,xylocation.XPosition[0],xylocation.YPosition[0],Toolpara);	
	m_XYdirection=0;
	m_Flagstr=false;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:处理双列直插孔
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessDualInlinePattern(char *ins)
{
	ProcessXY(ins);
	ProcessData(&drilllocation);
	xylocation3.XPosition[m_FlagDualLine]=drilllocation.Xanalyse;
	xylocation3.YPosition[m_FlagDualLine]=drilllocation.Yanalyse;
	if(m_FlagDualLine>0)
	{
		ProcessDualLine();
	}
	m_FlagDualLine+=1;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:处理八角孔
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::ProcessEightPinPattern(char *ins)
{
	ProcessXY(ins);
	ProcessData(&drilllocation);
	xylocation2.XPosition[m_FlagEightPin]=drilllocation.Xanalyse;
	xylocation2.YPosition[m_FlagEightPin]=drilllocation.Yanalyse;
	if(m_FlagEightPin>0)
	{
		if(xylocation2.XPosition[m_FlagEightPin-1]==xylocation2.XPosition[m_FlagEightPin])
		{
			if(xylocation2.YPosition[m_FlagEightPin-1]>xylocation2.YPosition[m_FlagEightPin])
			{
				xylocation2.YPosition[m_FlagEightPin]=xylocation2.YPosition[m_FlagEightPin-1]-10.16*1000/2;
				ProcessEightPin();
			}
			else
			{
				xylocation2.YPosition[m_FlagEightPin]=xylocation2.YPosition[m_FlagEightPin-1]+10.16*1000/2;
				ProcessEightPin();
			}
		}
		else if(xylocation2.YPosition[m_FlagEightPin-1]==xylocation2.YPosition[m_FlagEightPin])
		{
			if(xylocation2.XPosition[m_FlagEightPin-1]>xylocation2.XPosition[m_FlagEightPin])
			{
				xylocation2.XPosition[m_FlagEightPin]=xylocation2.XPosition[m_FlagEightPin-1]-10.16*1000/2;
				ProcessEightPin();
			}
			else
			{
				xylocation2.XPosition[m_FlagEightPin]=xylocation2.XPosition[m_FlagEightPin-1]+10.16*1000/2;
				ProcessEightPin();
			}
		}
		else
		{
			//此处处理容错机制
		}
	}
	m_FlagEightPin+=1;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:解析文件跳到下一行
Input:  
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::GotoNextLine(int linelength)//
{
   	linelength= linelength + 2 ; //跳过0D0A
	m_LineNum++;
	return linelength;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:1.X路径优化,实现基于x方向的排序
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::XDrillOptProcess(HoleInfoNode * drilllink)//
{
	
	HoleInfoNode *currentnode=drilllink->pnext;//已排好序链表的最后一个节点
	HoleInfoNode *testnode=currentnode->pnext;//待插入节点
	HoleInfoNode *pnode = NULL;//当前比对结点
	HoleInfoNode *prevnode=NULL;//当前比对节点的前驱结点
	//////////////////////////////////////////////////////////////////////////
	///////以下将所有孔按X坐标从小到大排序,X相同的Y从小到大排
	while (testnode!=NULL)
	{
		prevnode=drilllink;
		pnode = drilllink->pnext;
		while (pnode!=testnode)
		{
			if(testnode->position.nXs>pnode->position.nXs)
			{	
				prevnode=pnode;
				pnode=pnode->pnext;
			}
			else if(testnode->position.nXs==pnode->position.nXs)  //待测试节点等于当前比对节点，比较y后插入	
			{
				if (testnode->position.nYs<pnode->position.nYs)
				{			
					break;
				}
				else
				{
					prevnode=pnode;
					pnode=pnode->pnext;
				}
			}
			else// //待测试节点小于当前比对节点，直接插入
			{
				break;
			}						
		}
		//if (prevnode==currentnode) 
		if (pnode==testnode)//0316改
		{
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else//插入操作
		{
			currentnode->pnext=testnode->pnext;
			testnode->pnext=prevnode->pnext;
			prevnode->pnext=testnode;
			testnode=currentnode->pnext;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/*	//打印测试
	int j = 1;
	pnode = drilllink->pnext;
	while(pnode!=NULL)
	{
	TRACE("%d:   %d,   %d\n",j, pnode->position.nXs,pnode->position.nYs);
	pnode = pnode->pnext;
	j++;
}*/
	//////////////////////////////////////////////////////////////////////////	
	pnode=drilllink->pnext;
	currentnode=drilllink->pnext;//已排好序链表的最后一个节点
    testnode=currentnode->pnext;//待插入节点
	
	HoleInfoNode *tempnode=NULL;
	bool riseflag=true;
	while (testnode!=NULL)
	{
		int ypos_cur;
		int ypos_min;
		int ypos_max;
		
		if (testnode->position.nXs==currentnode->position.nXs)
		{	
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else
		{
			//-------计算相同X坐标 的孔数
			tempnode=testnode;
			//	int i=1;
			riseflag=true;
			while (tempnode->pnext!=NULL&& tempnode->position.nXs==tempnode->pnext->position.nXs)
			{
				//	i++;
				if (tempnode->position.nYs>tempnode->pnext->position.nYs)
				{
					riseflag=false;//降序
				}//此处升序降序判断意义？0316
				tempnode=tempnode->pnext;				
			}
			//----------------
			//	if (i==1)//只有一个
			if (tempnode==testnode)
			{
				currentnode=testnode;
				testnode=testnode->pnext;
			}
			else//大于一个
			{
				ypos_cur=currentnode->position.nYs;
				if (riseflag==true)//升序
				{
					ypos_min=testnode->position.nYs;
					ypos_max=tempnode->position.nYs;
					
					if (abs(ypos_cur-ypos_min)<=abs(ypos_cur-ypos_max))//升序加入新链表 ：直接相连
					{
						//	currentnode->pnext=testnode;//此处赋值没有意义
						testnode=tempnode->pnext;
						currentnode=tempnode;
					}
					else//降序加入新链表，需要将x位置相等的部分逆置
					{
						//------逆置链表
						HoleInfoNode *pnode1=testnode;
						HoleInfoNode *pnode2=testnode->pnext;
						HoleInfoNode *pnode3=NULL;
						HoleInfoNode *savenode=tempnode->pnext;
						while (pnode2!=tempnode)
						{
							pnode3=pnode2->pnext;
							pnode2->pnext=pnode1;
							pnode1=pnode2;
							pnode2=pnode3;
						}
						tempnode->pnext=pnode1;	
						//---------
						currentnode->pnext=tempnode;
						testnode->pnext=savenode;
						currentnode=testnode;
						testnode=testnode->pnext;
					}
					
				}
				else//降序
				{
					ypos_min=tempnode->position.nYs;
					ypos_max=testnode->position.nYs;
					
					if (abs(ypos_cur-ypos_min)<=abs(ypos_cur-ypos_max))//升序加入新链表 ：需要将x位置相等的部分逆置
					{
						//------逆置链表
						HoleInfoNode *pnode1=testnode;
						HoleInfoNode *pnode2=testnode->pnext;
						HoleInfoNode *pnode3=NULL;
						HoleInfoNode *savenode=tempnode->pnext;
						while (pnode2!=tempnode)
						{
							pnode3=pnode2->pnext;
							pnode2->pnext=pnode1;
							pnode1=pnode2;
							pnode2=pnode3;
						}
						tempnode->pnext=pnode1;	
						//---------
						currentnode->pnext=tempnode;
						testnode->pnext=savenode;
						currentnode=testnode;
						testnode=testnode->pnext;
					}
					else//降序加入新链表，直接相连
					{							
						currentnode->pnext=testnode;
						testnode=tempnode->pnext;
						currentnode=tempnode;
					}		
				}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/*	//打印测试
    j = 1;
	pnode = drilllink->pnext;
	while(pnode!=NULL)
	{
	TRACE("%d:   %d,   %d\n",j, pnode->position.nXs,pnode->position.nYs);
	pnode = pnode->pnext;
	j++;
	}*/
	//////////////////////////////////////////////////////////////////////////
}
/********************************************************
Function: ProcessCannedTextPattern
Description:2.Y路径优化
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::YDrillOptProcess(HoleInfoNode * drilllink)//
{
	
	HoleInfoNode *currentnode=drilllink->pnext;//已排好序链表的最后一个节点
	HoleInfoNode *testnode=currentnode->pnext;//待插入节点
	HoleInfoNode *pnode = NULL;//当前比对结点
	HoleInfoNode *prevnode=NULL;//当前比对节点的前驱结点
	//////////////////////////////////////////////////////////////////////////
	///////以下将所有孔按X坐标从小到大排序,X相同的Y从小到大排
	while (testnode!=NULL)
	{
		prevnode=drilllink;
		pnode = drilllink->pnext;
		while (pnode!=testnode)
		{
			if(testnode->position.nYs>pnode->position.nYs)
			{	
				prevnode=pnode;
				pnode=pnode->pnext;
			}
			else if(testnode->position.nYs==pnode->position.nYs) 
			{
				if (testnode->position.nXs<pnode->position.nXs)
				{			
					break;
				}
				else
				{
					prevnode=pnode;
					pnode=pnode->pnext;
				}
			}
			else// //待测试节点小于当前比对节点，直接插入
			{
				break;
			}						
		}
		//if (prevnode==currentnode) 
		if (pnode==testnode)//0316改
		{
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else//插入操作
		{
			currentnode->pnext=testnode->pnext;
			testnode->pnext=prevnode->pnext;
			prevnode->pnext=testnode;
			testnode=currentnode->pnext;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/*	//打印测试
	int j = 1;
	pnode = drilllink->pnext;
	while(pnode!=NULL)
	{
	TRACE("%d:   %d,   %d\n",j, pnode->position.nXs,pnode->position.nYs);
	pnode = pnode->pnext;
	j++;
}*/
	//////////////////////////////////////////////////////////////////////////	
	pnode=drilllink->pnext;
	currentnode=drilllink->pnext;//已排好序链表的最后一个节点
    testnode=currentnode->pnext;//待插入节点
	
	HoleInfoNode *tempnode=NULL;
	while (testnode!=NULL)
	{
		int xpos_cur;
		int xpos_min;
		int xpos_max;
		
		if (testnode->position.nYs==currentnode->position.nYs)
		{	
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else
		{
			//-------计算相同X坐标 的孔数
			tempnode=testnode;
			while (tempnode->pnext!=NULL&& tempnode->position.nYs==tempnode->pnext->position.nYs)
				tempnode=tempnode->pnext;				
			//----------------
			if (tempnode==testnode)
			{
				currentnode=testnode;
				testnode=testnode->pnext;
			}
			else//大于一个
			{
				xpos_cur=currentnode->position.nXs;
				xpos_min=testnode->position.nXs;
				xpos_max=tempnode->position.nXs;
				
				if (abs(xpos_cur-xpos_min)<=abs(xpos_cur-xpos_max))//升序加入新链表 ：直接相连
				{
					//	currentnode->pnext=testnode;//此处赋值没有意义
					testnode=tempnode->pnext;
					currentnode=tempnode;
				}
				else//降序加入新链表，需要将x位置相等的部分逆置
				{
					//------逆置链表
					HoleInfoNode *pnode1=testnode;
					HoleInfoNode *pnode2=testnode->pnext;
					HoleInfoNode *pnode3=NULL;
					HoleInfoNode *savenode=tempnode->pnext;
					while (pnode2!=tempnode)
					{
						pnode3=pnode2->pnext;
						pnode2->pnext=pnode1;
						pnode1=pnode2;
						pnode2=pnode3;
					}
					tempnode->pnext=pnode1;	
					//---------
					currentnode->pnext=tempnode;
					testnode->pnext=savenode;
					currentnode=testnode;
					testnode=testnode->pnext;
				}
			}
		}
	}	
}
/********************************************************
Function: DistanceDrillOptProcess
Description:3.距离优化
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::DistanceDrillOptProcess(HoleInfoNode * drilllink)//
{
	HoleInfoNode *currentnode=NULL;//已排好序链表的最后一个节点
	HoleInfoNode *minnode=NULL;
	HoleInfoNode *pnode=NULL;
	HoleInfoNode *preminnode=NULL;
	HoleInfoNode *prenode=NULL;
	int prenodetoolnum;//记录上一结点的刀具号
	double orginaldistance=0;
	double processdistance=0;
	double xp=0;
	double yp=0;
	
	double x0=0;
	double y0=0;
	double x1=0;
	double y1=0;
	//打印测试---优化前
	int j = 1;	
	pnode = drilllink->pnext;
	while(pnode!=NULL)
	{
		x1=pnode->position.nXs/1000.;
		y1=pnode->position.nYs/1000.;
		orginaldistance+=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
//		TRACE("%d:%d,%d,%d\n",j,pnode->position.nXs,pnode->position.nYs,pnode->m_ToolNum);
		prenode=pnode;
		pnode = pnode->pnext;
		x0=x1;
		y0=y1;
		j++;
	}
	//******************调整每把刀具第一个结点为最小位置结点***************//
	currentnode=drilllink;//已排好序的最后一个结点  
	//	double mindis=0;
	double mindis=-1;//0318
	double dis=0;
	prenodetoolnum=-1;
	pnode=drilllink->pnext;		 
	while (pnode!=NULL)
	{		
		xp=pnode->position.nXs/1000.;
		yp=pnode->position.nYs/1000.;
		dis=xp*xp+yp*yp;
		if (pnode->m_ToolNum==prenodetoolnum)
		{
			if (dis<mindis)
			{
				mindis=dis;
				preminnode=prenode;
				minnode=pnode;
			}
		}
		else
		{
			//	if (mindis==0)//最开始刀具
			if (mindis==-1)//最开始刀具 //0318
			{
				//此处不用处理最小孔位置
				TRACE("test1");
				
			}
			else
			{
				//处理最小孔位置			 
				if (preminnode==currentnode)//最小孔本来就在此刀具最前方，不做任何处理
				{
				}
				else
				{
					preminnode->pnext=minnode->pnext;
					minnode->pnext=currentnode->pnext;
					currentnode->pnext=minnode;
				}		
				
				//更新已排好序链表最后一个结点currentnode 为上一刀具所在链表段的最后一个孔  
				if (minnode==prenode)//最小位置孔是某种刀具最后一个孔
				{
					currentnode=preminnode;//若最小位置孔是某刀具的最后一个孔，由于最小孔需要插入到原currentnode之后，
					                        //插入之后，该刀具链表段的最后一个结点变成了preminnode
				}
				else
				{
					currentnode=prenode;
				}		 
			}
			prenodetoolnum=pnode->m_ToolNum;
			minnode=pnode;
			preminnode=currentnode;
			mindis=dis;	//初始化每种刀具最小位置	
		}
		prenode=pnode;
		pnode=pnode->pnext;
	}
	//最后一种刀具处理
	//处理最小孔位置			 
	if (preminnode==currentnode)//最小孔本来就在此刀具最前方，不做任何处理
	{
	}
	else
	{
		preminnode->pnext=minnode->pnext;
		minnode->pnext=currentnode->pnext;
		currentnode->pnext=minnode;
	}
	
	//**************************************************************************//
	TRACE("不同刀具第一个点调整之后\n");
	//打印测试
	j = 1;
	pnode = drilllink->pnext;
	x0=0;
	y0=0;
	double orginaldistance1=0;
	while(pnode!=NULL)
	{
		//	TRACE("%d:%d,%d,%d\n",j,pnode->position.nXs,pnode->position.nYs,pnode->m_ToolNum);
		
		x1=pnode->position.nXs/1000.;
		y1=pnode->position.nYs/1000.;
		orginaldistance1+=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
//		TRACE("%d:%d,%d,%d\n",j,pnode->position.nXs,pnode->position.nYs,pnode->m_ToolNum);
		prenode=pnode;
		pnode = pnode->pnext;
		x0=x1;
		y0=y1;
		j++;
	}
	//**************************优化处理***************************************//
	
	pnode=drilllink->pnext;
/*	while (pnode!=NULL)
	{
		pnode->position.distance=-1;
		pnode=pnode->pnext;
	}*/
	currentnode=drilllink;//已排好序的最后一个结点  
	prenodetoolnum=-1;
	HoleInfoNode *beginnode=currentnode;//初始化beginnode
	j=1;
	mindis=-1;
//	int i=1;
	while (currentnode->pnext!=NULL)
	{	
		pnode=currentnode->pnext;//遍历从已排序链表的最后一个结点开始，前面已排好序的刀具链表段不再遍历，减少遍历次数
//		j=1;
		while (pnode!=NULL)
		{
			if (pnode->m_ToolNum!=prenodetoolnum)//刀具与上一把刀具不相同
			{	
				if (mindis==-1)
				{
					//更新beginnode
				//	beginnode=pnode;
					prenodetoolnum=pnode->m_ToolNum;
				//	currentnode=beginnode;
					currentnode=pnode;
				}
				else
				{
					//处理最小位置孔 
					if (currentnode->pnext==minnode)//最小点就是已排序结点的下一结点
					{
						
					}
					else
					{
						preminnode->pnext=minnode->pnext;
						minnode->pnext=currentnode->pnext;
						currentnode->pnext=minnode;
					}
					currentnode=currentnode->pnext;
				//	currentnode->position.distance=(int)mindis;			    
				}
				mindis=-1;
				break;
				
			}
			else//刀具与上一把刀具相同
			{
				xp=(pnode->position.nXs-currentnode->position.nXs)/1000.;// 此处需要比较currentnode与beginnode
				yp=(pnode->position.nYs-currentnode->position.nYs)/1000.;
				dis=xp*xp+yp*yp;
				if (mindis==-1)
				{
					mindis=dis;
					minnode=pnode;
					preminnode=prenode;
				}
				else
				{
					if (mindis>dis)
					{
						mindis=dis;
						minnode=pnode;
						preminnode=prenode;
					}
				}
			}			
			prenode=pnode;
			pnode=pnode->pnext;
		}
		if (mindis!=-1)
		{
			//处理最小孔
		//	prenodetoolnum=pnode->m_ToolNum;
			if (currentnode->pnext==minnode)//最小点就是已排序结点的下一结点
			{
				
			}
			else
			{
				preminnode->pnext=minnode->pnext;
				minnode->pnext=currentnode->pnext;
				currentnode->pnext=minnode;
			}
			currentnode=currentnode->pnext;
	//		currentnode->position.distance=(int)mindis;	
			mindis=-1;
			
		}
	}
	/*	while (currentnode->pnext!=NULL)
	{	
	pnode=beginnode->pnext;//遍历从当前刀具链表段开始，前面已排好序的刀具链表段不再遍历，减少遍历次数
	j=1;
	
	  while (pnode!=NULL)
	  {
	  //	TRACE("pnode%d:%d,%d,%d\n",j++,pnode->position.nXs,pnode->position.nYs,pnode->m_ToolNum);
	  if (pnode->position.distance!=-1)
	  {
	  TRACE("test");
	  }
	  else//未加入排序链表
	  {
	  if (pnode->m_ToolNum!=prenodetoolnum)//刀具与上一把刀具不相同
	  {
	  
		if (mindis==-1)
		{
		//更新beginnode
		beginnode=pnode;
		prenodetoolnum=pnode->m_ToolNum;
		currentnode=beginnode;
		}
		else
		{
		//处理最小位置孔 
		if (currentnode->pnext==minnode)//最小点就是已排序结点的下一结点
		{
		
		  }
		  else
		  {
		  preminnode->pnext=minnode->pnext;
		  minnode->pnext=currentnode->pnext;
		  currentnode->pnext=minnode;
		  }
		  currentnode=currentnode->pnext;
		  currentnode->position.distance=(int)mindis;			    
		  }
		  mindis=-1;
		  break;
		  
			}
			else//刀具与上一把刀具相同
			{
			xp=(pnode->position.nXs-currentnode->position.nXs)/1000.;// 此处需要比较currentnode与beginnode
			yp=(pnode->position.nYs-currentnode->position.nYs)/1000.;
			dis=xp*xp+yp*yp;
			if (mindis==-1)
			{
			mindis=dis;
			minnode=pnode;
			preminnode=prenode;
			}
			else
			{
			if (mindis>dis)
			{
			mindis=dis;
			minnode=pnode;
			preminnode=prenode;
			}
			}
			}
			
			  }	
			  
				prenode=pnode;
				pnode=pnode->pnext;
				}
				if (mindis!=-1)
				{
				//处理最小孔
				if (currentnode->pnext==minnode)//最小点就是已排序结点的下一结点
				{
				
				  }
				  else
				  {
				  preminnode->pnext=minnode->pnext;
				  minnode->pnext=currentnode->pnext;
				  currentnode->pnext=minnode;
				  }
				  currentnode=currentnode->pnext;
				  currentnode->position.distance=(int)mindis;	
				  mindis=-1;
				  
					}
	}*/
	TRACE("优化之后\n");
	j = 1;	
	pnode = drilllink->pnext;
	x0=0;
	y0=0;
	while(pnode!=NULL)
	{
		x1=pnode->position.nXs/1000.;
		y1=pnode->position.nYs/1000.;
		processdistance+=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0);
	//	TRACE("pnode:%d,%d\n",	pnode->position.nXs,pnode->position.nYs);
		prenode=pnode;
		pnode = pnode->pnext;
		x0=x1;
		y0=y1;
		j++;
	}
	
/*	TRACE("不使用优化  时的总距离为：%.1f\n",(float)orginaldistance);
	TRACE("使用距离优化时的总距离为：%.1f\n",(float)processdistance);*/
	
}
/********************************************************
Function: CopyHolePosNode
Description:实现对孔位数据链表的复制
Input:  
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::CopyHolePosNode()//(HoleInfoNode *inlist,HoleInfoNode *outlist)//
{
HoleInfoNode *currentnode=NULL;
HoleInfoNode *previousnode=NULL;
if(this->m_OriPosition==NULL)
return -1;//要复制的链表为空，不执行复制操作
this->m_WorkPosition->m_Toolform=this->m_OriPosition->m_Toolform;
this->m_WorkPosition->m_ToolNum=this->m_OriPosition->m_ToolNum;
this->m_WorkPosition->m_LINENUM=this->m_OriPosition->m_LINENUM;
this->m_WorkPosition->m_CurrentDrillNum=this->m_OriPosition->m_CurrentDrillNum;
this->m_WorkPosition->position.nXs=this->m_OriPosition->position.nXs;
this->m_WorkPosition->position.nYs=this->m_OriPosition->position.nYs;
this->m_WorkPosition->pnext=NULL;
previousnode=this->m_WorkPosition;//保留新链表的头结点指针outlist。用previousnode执行指向下一结点操作
this->m_OriPosition=this->m_OriPosition->pnext;
while(this->m_OriPosition)
{
currentnode=(HoleInfoNode *)malloc(sizeof(HoleInfoNode));//当前操作结点
previousnode->pnext=currentnode;
currentnode->m_Toolform=this->m_OriPosition->m_Toolform;
currentnode->m_ToolNum=this->m_OriPosition->m_ToolNum;
currentnode->m_LINENUM=this->m_OriPosition->m_LINENUM;
currentnode->m_CurrentDrillNum=this->m_OriPosition->m_CurrentDrillNum;
currentnode->position.nXs=this->m_OriPosition->position.nXs;
currentnode->position.nYs=this->m_OriPosition->position.nYs;
currentnode->pnext=NULL;
previousnode=currentnode;
this->m_OriPosition=this->m_OriPosition->pnext;
}

  return 0;
	
	//0207todo
	if(m_OriPosition==NULL)
		return -1;
	if (m_WorkPosition==NULL)
		return -1;
	HoleInfoNode *tempnod_ori=m_OriPosition;
	HoleInfoNode *tempnod_work=m_WorkPosition;
	while(tempnod_ori)
	{
		tempnod_work->m_Toolform=tempnod_ori->m_Toolform;
		tempnod_work->m_ToolNum=tempnod_ori->m_ToolNum;
		tempnod_work->m_LINENUM=tempnod_ori->m_LINENUM;
		tempnod_work->m_CurrentDrillNum=tempnod_ori->m_CurrentDrillNum;
		tempnod_work->position.nXs=tempnod_ori->position.nXs;
		tempnod_work->position.nYs=tempnod_ori->position.nYs;
		tempnod_ori=tempnod_ori->pnext;
		tempnod_work=tempnod_work->pnext;
	}
	free(currentnode);
	return 0;
}


int CMastProgInOut::CreateAndCopyHolePosNode(HoleInfoNode *outlist)//实现对孔位数据链表的复制
{
	
/*	HolePosNode *currentnode=NULL;
HolePosNode *previousnode=NULL;
if(inlist==NULL)
return -1;//要复制的链表为空，不执行复制操作
if (outlist==NULL)
return -1;//链表头结点为空，不执行复制操作
outlist->m_Toolform=inlist->m_Toolform;
outlist->m_ToolNum=inlist->m_ToolNum;
outlist->m_LINENUM=inlist->m_LINENUM;
outlist->m_CurrentDrillNum=inlist->m_CurrentDrillNum;
outlist->position.nXs=inlist->position.nXs;
outlist->position.nYs=inlist->position.nYs;
outlist->pnext=NULL;
previousnode=outlist;//保留新链表的头结点指针outlist。用previousnode执行指向下一结点操作
inlist=inlist->pnext;
while(inlist)
{
currentnode=(HolePosNode *)malloc(sizeof(HolePosNode));//当前操作结点
previousnode->pnext=currentnode;
currentnode->m_Toolform=inlist->m_Toolform;
currentnode->m_ToolNum=inlist->m_ToolNum;
currentnode->m_LINENUM=inlist->m_LINENUM;
currentnode->m_CurrentDrillNum=inlist->m_CurrentDrillNum;
currentnode->position.nXs=inlist->position.nXs;
currentnode->position.nYs=inlist->position.nYs;
currentnode->pnext=NULL;
previousnode=currentnode;
inlist=inlist->pnext;
}

	return 0;*/
	HoleInfoNode *currentnode=NULL;
	HoleInfoNode *previousnode=NULL;
	HoleInfoNode *tempnode=NULL;
	if(this->m_OriPosition==NULL)
		return -1;//要复制的链表为空，不执行复制操作
	tempnode=m_OriPosition;
	outlist->m_Toolform=this->m_OriPosition->m_Toolform;
	outlist->m_ToolNum=this->m_OriPosition->m_ToolNum;
	outlist->m_LINENUM=this->m_OriPosition->m_LINENUM;
	outlist->m_CurrentDrillNum=this->m_OriPosition->m_CurrentDrillNum;
	outlist->position.nXs=this->m_OriPosition->position.nXs;
	outlist->position.nYs=this->m_OriPosition->position.nYs;
	outlist->pnext=NULL;
	previousnode=outlist;//保留新链表的头结点指针outlist。用previousnode执行指向下一结点操作
	//	this->m_OriPosition=this->m_OriPosition->pnext;
	tempnode=tempnode->pnext;//0316改
	//	while(this->m_OriPosition)
	while(tempnode)
	{
		currentnode=(HoleInfoNode *)malloc(sizeof(HoleInfoNode));//当前操作结点
		previousnode->pnext=currentnode;
		currentnode->m_Toolform=tempnode->m_Toolform;
		currentnode->m_ToolNum=tempnode->m_ToolNum;
		currentnode->m_LINENUM=tempnode->m_LINENUM;
		currentnode->m_CurrentDrillNum=tempnode->m_CurrentDrillNum;
		currentnode->position.nXs=tempnode->position.nXs;
		currentnode->position.nYs=tempnode->position.nYs;
		currentnode->pnext=NULL;
		previousnode=currentnode;
		//	this->m_OriPosition=this->m_OriPosition->pnext;
		tempnode=tempnode->pnext;//0316改
	}
	free(currentnode);
	return 0;
}
