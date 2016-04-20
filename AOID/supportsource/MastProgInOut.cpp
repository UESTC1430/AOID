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
	
	m_toolnumber=0;//��ǰ�ļ�����ʱ��ŵ��ߺŵ�ȫ�ֱ�����0��ʾ��ǰ��λû��ѡ����ǣ�������Ȼ�����ʾ��Ӧ�ĵ��ţ�
	DrillNumber=0;//���浶���д�׵�����  ÿ�ѵ��߶�Ӧ�Ŀ���
	Drilllength=0;//���浶���п�λ֮����ܾ���
	TotalDrillNumber=0;//�����ܵĿ���  add by su
	relatedtodia=false;//�ļ������뵶��ֱ���йر�־ true���йأ��ۿס��ַ��ף�add by su
	m_LineNum=0;//�����¼��ǰָ�����ڴ���ļ��ĵڼ���
	TOOLNUM=0;//������¼����ļ���ʹ���˼��ѵ�
	definetoolnum=0;//��¼�ļ��ж���ĵ������� 
	METRIC=true;//�������ݵı�ʾ��true��ʾ���ƣ�
	m_ndataM=0;//��ʾ���Ƶ�ǰ��λ
	m_ndataN=0;//��ʾ���Ƶĺ�λ
	m_LeadTrailFlag;//ǰ������жϱ�־λ��ture��ʾ��ǰ���㣩
	m_LineEndFlag;//��ʾÿ�н���ʱʱ���ǡ�/n������������false��ʾ���� true��ʾ�ǣ�
	m_FlagSubProEnd=false;//��ʾ�����ӳ���������־λ
	m_FlagRelativeMod=false;//���ģʽ���жϱ�־λ��false��ʾ���ھ���ģʽ��true��ʾ�������ģʽ��
	m_FlagEightPin=2;//�˽��ε��жϱ�־λ����m_FlagEighPin<2ʱ��ʾ���µ��������궼���ڰ˽��εĶ�λ���꣩
	m_FlagDualLine=2;//˫��ֱ��ʽ�жϱ�־λ����m_FlagDualLine<2ʱ��ʾ���µ��������궼����˫��ֱ��ʽ�������յ�����꣩
	m_Flagstr=false;//��ʾ�������Ƿ������ַ�����ӡ����ʼ����
	m_XYdirection=0;//��1��ʾ��x�����ӡ��2��ʾ��y�����ӡ��
	tempstr=NULL;//���ڷָ��ַ�������ʱָ��
	//tempstr1[256]={0};//���ڷָ��ַ�������ʱ����
	//a[7][4]={0};//������ʱ����ַ�ת���ɵ��м����
	//TempArray[7][4]={0};//������ʱ�洢�ַ�ת�������ĵ���
	m_OriPosition=NULL;
	Previous=NULL;
	Current=NULL;
	m_pnext=NULL;
	m_tempLocation=NULL;//������ʱ������п�λ�����ָ��ֵ
	m_tempLocation1=NULL;//������ʱ������п�λ�����ָ��ֵ(����ִ��M02�ڶ��ο�λ������׵�ַ)
	m_firstLocation=NULL;//���ܵ���ָ��ʱ���ڴ���������׵�ַ��ǰһ����ַ
	m_lastLocation=NULL;//���ܵ���ָ��ʱ���ڴ��������ĩβ��ַ
	m_WorkPosition=NULL;
	m_DrillXOptPosition=NULL;//x�Ż�����
	m_DrillYOptPosition=NULL;//y�Ż�����

	m_DrillDisOptPosition=NULL;//�����Ż�����
	
	m_Previous=NULL;
	m_Current=NULL;
	m_first=NULL;//���ϵ�ָ�������ڼ���ۿ�����ʱ���������ָ��
	m_Previous1=NULL;
	m_Current1=NULL;
	m_first1=NULL;//���ϵ�ָ���������������մ������ʱ���õ�ָ��
	m_temp=NULL;//������ʱ���ɽڵ�
	
	m_PreviousCode=NULL;
	m_CurrentCode=NULL;
	m_firstCode=NULL;
	
	
	M02Num=0;//���ڴ��M02�Ѿ�ִ�еĴ���
	Xoffset1=0;//����X�����ϵ�ƫ����
	Yoffset1=0;//����Y�����ϵ�ƫ����
}

CMastProgInOut::~CMastProgInOut()
{
}
/********************************************************
Function: ImportExe
Description: �����ļ��������ļ��򿪣���ȡ�����ļ����ݵ�importfilecontent��
Input: CString *pfilecontent    
Output: 
Return: 
Others: ����˵�� 
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
			
			if(-1==importfilecontent.Find("\r\n",0))//���ļ����������������滻�ɻس�����
			{
				importfilecontent.Replace("\n","\r\n");
			}
			
			//ȥ�����һ�����з���
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
			//	pwnd->m_pOpPaneWnd->m_pF2SubItem21View->m_outfilecontentstr=m_filecontentstr;//��������
			//	UpdateData(false);
		}
		delete pfilestr;
		pfilestr=NULL;
		file.Close();
	}
}
/********************************************************
Function: ParseAnly
Description: �������������importfilecontent�����õ�ԭʼ��������
Input: CString  filestr    
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
/*int CMastProgInOut::ParseAnly(CString &ins,DrillNote * drillnote,SpecialPoints * specialpoints )
{
	if (ins.IsEmpty())
	{
		return -1;
	}
	int errcode = 0;
	//	int iLen = 0;  //�ܳ���
	int iLen =ins.GetLength();  //�ܳ���
	int iPos = 0;  //��¼���������ַ����е���ʼλ��
	int iLineLen=0; //�еĳ���
	char buf[256]="";//ÿһ�е���ʱָ��
	char *title;//�ֶε�ʱ����ʱ��ָ��
	bool bProHead = true;//��ͷ�ļ�����֮ǰ
	int ilen=0;//ÿһ�еĶ�ָ��
	
	m_LineEndFlag=true;	
	int flagBegin = 0; //0: δ��ʼ��1����ʼ��2������
	
	char *p = (LPSTR)(LPCTSTR)ins;//�˴������ж��Ƿ�ÿһ���ǡ�/n��
	for(int i=0; i<iLen; i++)
	{
		if( 0x0d == p[i] && 0x0a == p[i+1])
        {
			m_LineEndFlag=false;
			break;
		}
	} 
	//---------------------------------------------------------------------------------------
	//ÿ�ε��ô˴���ʱ��Ӧ�ý���һ���������Ĳ���
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
	m_ndataM=0;//��ʾ���Ƶ�ǰ��λ
	m_ndataN=0;//��ʾ���Ƶĺ�λ
	m_LineNum=0;//�ļ��ӵ�0�п�ʼ
	definetoolnum=0;//�ļ��ж���ĵ�������
	TOOLNUM=0;//�ļ������˼��ѵ�
	DrillNumber=0;//���������Ϊ0
	relatedtodia=false;
	TotalDrillNumber=0;
	//-----------------------------------------zns�޸�
	/*char *m_filecontentstr2=ins.GetBuffer(0);
	ToolParaStruct * Toolpara=NULL;
	ProcessT(m_filecontentstr2,Toolpara);
	//for(int i=1;i<ATP_Tool_NUM;i++)
	//	memset(&Toolpara[i].FileStaticPara,0,sizeof(Toolpara[i].FileStaticPara));
	//-------------------------------------------------------------------------------------------
	
	char *tempstrstr=(LPSTR)(LPCTSTR)ins;
	if(NULL==strstr(tempstrstr,"G93"))//�˴��Ĵ������趨����ļ�û�г�������ֵʱ��Ԥ��ֵ
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
			iPos += iLineLen + 2 ; //����0D0A
			continue;
		}
		if(!_strnicmp(buf, "M48", 3) && bProHead == true)
		{		
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "BLKD", 4) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "SBK", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "SG", 2) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "TCST", 4) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "OSTOP", 5) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "RSB", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "ATC", 3) && bProHead == true)
		{
			//�˴���ʱ�����������Զ���������û�ж�Ӧ�����ݽṹ��
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "FSB", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "M47", 3) && bProHead == false)
		{
			//�˴���ʱ������������ָͣ���ʾ������ַ���
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
			//�˴���ʱ��������
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
			
			if(bProHead == true)//�������ļ��в�������ֵ
			ProcessT(buf,Toolpara);
			else  //�������ļ����ĵ�ֵ
			{
				//	if(0<=TOOLNUM&&TOOLNUM<128&&DrillNum!=0)//�����Ƕ�ÿ�ѵ����ڿ�λ�ļ��е����������г�·���Ȳ�����������
				if(DrillNumber!=0)//�������Ϊ0,��������ʹ�õ��߽ṹ��
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
				DrillNumber=0;//ÿ����һ�����߽���һ�����ߵĴ�������γ�����
				Drilllength=0;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "%", 1)) && bProHead == true)//�˴���ʾ�ļ�ͷ���ý���
		{
			bProHead = false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!_strnicmp(buf, "G05", 3))||(!_strnicmp(buf, "G00", 3)) && bProHead == false)
		{	
			if(!_strnicmp(buf, "G05", 3))
			{}//�괲��ʼִ�б�־λ����
			else
			{}//ϳ����ʼִ�б�־λ����
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf, "P", 1) && bProHead == false)//��ʱĬ��P������M82��
		{	
			int i=0;//����ǰλ��
			int j=0;//������
			int RepeatTime=0;//�����ظ���Ĵ���
			double Xoffset=0;
			double Yoffset=0;
			char buffer[256]; //�Ӵ�	
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{				
				case 'P':
					strrmv(buffer,"P");
					RepeatTime=atoi(buffer);
					i+=j;//��ͷ����
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset=drilllocation.Xanalyse;
					i+=j; //��ͷ����
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset=drilllocation.Yanalyse;
					i+=j; //��ͷ����
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
			int Toolform=1;//1����ԭ���λ��Ϣ
			char *ch="G93";
			char *buffer=strrmv( buf, ch);
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			//drilllocation.Xoriganposition=drilllocation.Xanalyse;//����ԭ��
			//drilllocation.Yoriganposition=drilllocation.Yanalyse;
			specialpoints->P0.xpos=drilllocation.Xanalyse;//����ԭ��
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
				m_FlagRelativeMod=false;//����ģʽ
			}
			else
			{
				m_FlagRelativeMod=true;//���ģʽ
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		
		if(((!_strnicmp(buf, "X", 1))||(!_strnicmp(buf, "Y", 1))) && bProHead == false &&m_toolnumber!=0)
		{
			if(false==m_Flagstr&&m_FlagEightPin>1&&m_FlagDualLine>1)//���ַ��ס��ǰ˽ǿס���˫��ֱ���
			{	
				if(NULL==strstr(buf,"G85")&&NULL==strstr(buf,"G84"))//buf�в�����"G85"��"G84"
				{
					if(false==m_FlagRelativeMod)//�����������ģʽ
						ProcessAbsoluteMod(buf);
					else//�����������ģʽ
						ProcessRelativeMod(buf);	
				}
				else
				{
					relatedtodia=true;//�����뵶��ֱ�����
				//	if(NULL!=strstr(buf,"G85"))//buf�а���"G85"
//						ProcessSlotPattern(buf,Toolpara);	//���߲۵Ĵ���
			//		if(NULL!=strstr(buf,"G84"))
	//					ProcessCirclePattern(buf,Toolpara);	//��Բ�۵Ĵ���
				}
			}
			//else if(true==m_Flagstr)//����ʵ�ִ����ַ�����ʼ����Ĺ��ܣ��ڵ��õĺ������Զ�����x�����y����
				//ProcessCannedTextPattern(buf,Toolpara);
			//else if(m_FlagEightPin<=1)//���µĴ��봦��˽��ε�����
			//	ProcessEightPinPattern(buf);
			//else if(m_FlagDualLine<=1)//�˴��Ǵ���˫��ֱ���
			//	ProcessDualInlinePattern(buf);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if((!_strnicmp(buf, "M97", 3)) && bProHead == false)
		{
			relatedtodia=true;//�����뵶��ֱ�����
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
			relatedtodia=true;//�����뵶��ֱ�����
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
			Xoffset1=0;//�ڳ���M01��ʱ��ƫ��ֵ������
			Yoffset1=0;//�ڳ���M01��ʱ��ƫ��ֵ������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!_strnicmp(buf,"M02",3)&&bProHead==false)//�˴������ǰ����ǰ���Ѿ���һ���ӿ飬���û�оͻᱨ��
		{
			int i=0;//����ǰλ��
			int j=0;//������
			int k=0;//�����ظ�ִ�еĴ���
			int Flag=0;//���ڱ�ʶM02ָ����M70 M80 M90��״̬��1��ʾM70����� 2 ��ʾM80����� 3��ʾM90�����
			int NoteNum=0;//���ڴ��ִ��M02ʱ�����˶��ٸ��ڵ���
			char buffer[256]; //�Ӵ�	
			char *temp;
			if(0==strcmp(buf,"M02"))
			{
				iPos += iLineLen + 2 ; 
				m_LineNum++;
				continue;
			}
			temp=strrev(buf);//���ַ������е�������
			if(!strnicmp(buf, "07M", 3))//�˴��ж�M02�����ĸ������һ����M70 M80 M90��
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
			strrev(buf);//���ַ����ָ�����
			m_tempLocation=m_firstLocation->pnext;//�˶δ�������ִ��M02�Ĳ������������е�ָ����λ���и���һ��
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
			m_tempLocation=m_lastLocation->pnext;//�˶δ�������ȷ��������������׽ڵ�
			for(int a=NoteNum*M02Num;a>0;a--)
			{
				m_tempLocation=m_tempLocation->pnext;
			}
			m_tempLocation1=m_tempLocation;
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{
					
				case 'M':
					if(NULL!=strstr(buffer,"M70"))//����XY�ύ���Ĳ���
					{
						if(Flag==1)//�˴�����M70���������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;//�˴��ǽ����һ���ڵ��ֵ����XY�ı任����
								xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
							}
							else 
							{
								//�˴���û���ӿ���б�����
							}
						}
						else//�˴�����M70�����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs;//�˴��ǽ����һ���ڵ��ֵ����XY�ı任����
								xylocation.YPosition[0]=m_tempLocation->position.nXs;	
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else 
							{
								//�˴���û���ӿ���б�����
							}
						}
					}
					else if(NULL!=strstr(buffer,"M80"))//X�������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//�˴�����M80�����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs;
								xylocation.YPosition[0]=m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else if(NULL!=strstr(buffer,"M90"))//Y�������
					{
						if(Flag==3)//�˴�����M90���������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//�˴�����M90 �����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
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
						//�˴�����M02����û��M70 M80 M90�����
					}
					i+=j; //��ͷ����
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset1+=drilllocation.Xanalyse;//M02������ʱ����Ҫ��ƫ��ֵ�ۼƽ��е���
					
					i+=j; //��ͷ����
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset1+=drilllocation.Yanalyse;//M02������ʱ����Ҫ��ƫ��ֵ�ۼƽ��е���
					
					i+=j; //��ͷ����
					break;
				default:
					i+=j;
					break;		
					
				}
			}
			//			m_firstLocation=m_tempLocation1;
			
			if(NULL==strstr(buf,"M70")&&NULL==strstr(buf,"M80")&&NULL==strstr(buf,"M90"))//���ڴ���û��M70 M80 M90�����
			{
				m_tempLocation=m_tempLocation1;
				while(Current!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
					m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
				m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
			}
			M02Num+=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == false)
		{	
			int i=0;//����ǰλ��
			int j=0;//������
			int k=0;//�����ظ�ִ�еĴ���
			double Xoffset=0;//����X�����ϵ�ƫ����
			double Yoffset=0;//����Y�����ϵ�ƫ����
			char buffer[256]; //�Ӵ�	
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{
					
				case 'R':
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						strrmv(buffer,"R");
						k=atoi(buffer);
					}
					i+=j; //��ͷ����
					break;
				case 'X': 
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Xoffset=drilllocation.Xanalyse;
					}
					i+=j; //��ͷ����
					break;
				case 'Y': 
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Yoffset=drilllocation.Yanalyse;
					}
					i+=j; //��ͷ����
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
			//�˴���������
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
				//G82���ݴ����
			}
			m_FlagDualLine=0;
			m_firstLocation=Current;//�˴���ǰһ����λ���굱�������ʼ���긳�����׵�ַ
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
			//����M99�ı�־λ����ʱ����������
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
	//	int iLen = 0;  //�ܳ���
	int iLen =ins.GetLength();  //�ܳ���
	int iPos = 0;  //��¼���������ַ����е���ʼλ��
	int iLineLen=0; //�еĳ���
	char buf[256]="";//ÿһ�е���ʱָ��
	char *title;//�ֶε�ʱ����ʱ��ָ��
	bool bProHead = true;//��ͷ�ļ�����֮ǰ
	int ilen=0;//ÿһ�еĶ�ָ��

	m_LineEndFlag=true;	
	int flagBegin = 0; //0: δ��ʼ��1����ʼ��2������
	
	char *p = (LPSTR)(LPCTSTR)ins;//�˴������ж��Ƿ�ÿһ���ǡ�/n��
	for(int i=0; i<iLen; i++)
	{
		if( 0x0d == p[i] && 0x0a == p[i+1])
        {
			m_LineEndFlag=false;
			break;
		}
	} 
	//---------------------------------------------------------------------------------------
	//ÿ�ε��ô˴���ʱ��Ӧ�ý���һ���������Ĳ���
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
	m_ndataM=0;//��ʾ���Ƶ�ǰ��λ
	m_ndataN=0;//��ʾ���Ƶĺ�λ
	m_LineNum=0;//�ļ��ӵ�0�п�ʼ
	definetoolnum=0;//�ļ��ж���ĵ�������
	TOOLNUM=0;//�ļ������˼��ѵ�
	DrillNumber=0;//���������Ϊ0
	relatedtodia=false;
	TotalDrillNumber=0;
	for(int i=1;i<ATP_Tool_NUM;i++)  //ATP_Tool_NUM   -------------------------------------------------------------------------------------------====
		memset(&(Toolpara[i].FileStaticPara),0,sizeof(Toolpara[i].FileStaticPara));
	//-------------------------------------------------------------------------------------------
	
	char *tempstrstr=(LPSTR)(LPCTSTR)ins;
	if(NULL==strstr(tempstrstr,"G93"))//�˴��Ĵ������趨����ļ�û�г�������ֵʱ��Ԥ��ֵ
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
			iPos += iLineLen + 2 ; //����0D0A
			continue;
		}
		if(!strnicmp(buf, "M48", 3) && bProHead == true)
		{		
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "BLKD", 4) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "SBK", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "SG", 2) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "TCST", 4) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "OSTOP", 5) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "RSB", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "ATC", 3) && bProHead == true)
		{
			//�˴���ʱ�����������Զ���������û�ж�Ӧ�����ݽṹ��
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "FSB", 3) && bProHead == true)
		{
			//�˴���ʱ��������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "M47", 3) && bProHead == false)
		{
			//�˴���ʱ������������ָͣ���ʾ������ַ���
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
			//�˴���ʱ��������
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
			
			if(bProHead == true)//�������ļ��в�������ֵ
				ProcessT(buf,Toolpara);
			else  //�������ļ����ĵ�ֵ
			{
				//	if(0<=TOOLNUM&&TOOLNUM<128&&DrillNum!=0)//�����Ƕ�ÿ�ѵ����ڿ�λ�ļ��е����������г�·���Ȳ�����������
				if(DrillNumber!=0)//�������Ϊ0,��������ʹ�õ��߽ṹ��
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
				DrillNumber=0;//ÿ����һ�����߽���һ�����ߵĴ�������γ�����
				Drilllength=0;
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "%", 1)) && bProHead == true)//�˴���ʾ�ļ�ͷ���ý���
		{
			bProHead = false;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if((!strnicmp(buf, "G05", 3))||(!strnicmp(buf, "G00", 3)) && bProHead == false)
		{	
			if(!strnicmp(buf, "G05", 3))
			{}//�괲��ʼִ�б�־λ����
			else
			{}//ϳ����ʼִ�б�־λ����
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "P", 1) && bProHead == false)//��ʱĬ��P������M82��
		{	
			int i=0;//����ǰλ��
			int j=0;//������
			int RepeatTime=0;//�����ظ���Ĵ���
			double Xoffset=0;
			double Yoffset=0;
			char buffer[256]; //�Ӵ�	
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{				
				case 'P':
					strrmv(buffer,"P");
					RepeatTime=atoi(buffer);
					i+=j;//��ͷ����
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset=drilllocation.Xanalyse;
					i+=j; //��ͷ����
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset=drilllocation.Yanalyse;
					i+=j; //��ͷ����
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
			int Toolform=1;//1����ԭ���λ��Ϣ
			char *ch="G93";
			char *buffer=strrmv( buf, ch);
			ProcessXY(buffer);
			ProcessData(&drilllocation);
			//drilllocation.Xoriganposition=drilllocation.Xanalyse;//����ԭ��
			//drilllocation.Yoriganposition=drilllocation.Yanalyse;
			specialpoints->P0.xpos=drilllocation.Xanalyse;//����ԭ��
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
				m_FlagRelativeMod=false;//����ģʽ
			}
			else
			{
				m_FlagRelativeMod=true;//���ģʽ
			}
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		
		if(((!strnicmp(buf, "X", 1))||(!strnicmp(buf, "Y", 1))) && bProHead == false &&m_toolnumber!=0)
		{
			if(false==m_Flagstr&&m_FlagEightPin>1&&m_FlagDualLine>1)//���ַ��ס��ǰ˽ǿס���˫��ֱ���
			{	
				if(NULL==strstr(buf,"G85")&&NULL==strstr(buf,"G84"))//buf�в�����"G85"��"G84"
				{
					if(false==m_FlagRelativeMod)//�����������ģʽ
						ProcessAbsoluteMod(buf);
					else//�����������ģʽ
						ProcessRelativeMod(buf);	
				}
				else
				{
					relatedtodia=true;//�����뵶��ֱ�����
					if(NULL!=strstr(buf,"G85"))//buf�а���"G85"
						ProcessSlotPattern(buf,Toolpara);	//���߲۵Ĵ���
					if(NULL!=strstr(buf,"G84"))
						ProcessCirclePattern(buf,Toolpara);	//��Բ�۵Ĵ���
				}
			}
			else if(true==m_Flagstr)//����ʵ�ִ����ַ�����ʼ����Ĺ��ܣ��ڵ��õĺ������Զ�����x�����y����
				ProcessCannedTextPattern(buf,Toolpara);
			else if(m_FlagEightPin<=1)//���µĴ��봦��˽��ε�����
				ProcessEightPinPattern(buf);
			else if(m_FlagDualLine<=1)//�˴��Ǵ���˫��ֱ���
				ProcessDualInlinePattern(buf);
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		
		if((!strnicmp(buf, "M97", 3)) && bProHead == false)
		{
			relatedtodia=true;//�����뵶��ֱ�����
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
			relatedtodia=true;//�����뵶��ֱ�����
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
			Xoffset1=0;//�ڳ���M01��ʱ��ƫ��ֵ������
			Yoffset1=0;//�ڳ���M01��ʱ��ƫ��ֵ������
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf,"M02",3)&&bProHead==false)//�˴������ǰ����ǰ���Ѿ���һ���ӿ飬���û�оͻᱨ��
		{
			int i=0;//����ǰλ��
			int j=0;//������
			int k=0;//�����ظ�ִ�еĴ���
			int Flag=0;//���ڱ�ʶM02ָ����M70 M80 M90��״̬��1��ʾM70����� 2 ��ʾM80����� 3��ʾM90�����
			int NoteNum=0;//���ڴ��ִ��M02ʱ�����˶��ٸ��ڵ���
			char buffer[256]; //�Ӵ�	
			char *temp;
			if(0==strcmp(buf,"M02"))
			{
				iPos += iLineLen + 2 ; 
				m_LineNum++;
				continue;
			}
			temp=strrev(buf);//���ַ������е�������
			if(!strnicmp(buf, "07M", 3))//�˴��ж�M02�����ĸ������һ����M70 M80 M90��
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
			strrev(buf);//���ַ����ָ�����
			m_tempLocation=m_firstLocation->pnext;//�˶δ�������ִ��M02�Ĳ������������е�ָ����λ���и���һ��
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
			m_tempLocation=m_lastLocation->pnext;//�˶δ�������ȷ��������������׽ڵ�
			for(int a=NoteNum*M02Num;a>0;a--)
			{
				m_tempLocation=m_tempLocation->pnext;
			}
			m_tempLocation1=m_tempLocation;
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{
					
				case 'M':
					if(NULL!=strstr(buffer,"M70"))//����XY�ύ���Ĳ���
					{
						if(Flag==1)//�˴�����M70���������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs+Xoffset1;//�˴��ǽ����һ���ڵ��ֵ����XY�ı任����
								xylocation.YPosition[0]=m_tempLocation->position.nXs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
							}
							else 
							{
								//�˴���û���ӿ���б�����
							}
						}
						else//�˴�����M70�����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nYs;//�˴��ǽ����һ���ڵ��ֵ����XY�ı任����
								xylocation.YPosition[0]=m_tempLocation->position.nXs;	
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else 
							{
								//�˴���û���ӿ���б�����
							}
						}
					}
					else if(NULL!=strstr(buffer,"M80"))//X�������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								//								m_lastLocation=Current;
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//�˴�����M80�����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=-m_tempLocation->position.nXs;
								xylocation.YPosition[0]=m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
					}
					else if(NULL!=strstr(buffer,"M90"))//Y�������
					{
						if(Flag==3)//�˴�����M90���������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs+Yoffset1;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
								m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
								
							}
							else
							{
								AfxMessageBox("No Code!");
							}
						}
						else//�˴�����M90 �����������
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
									m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
									m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
									m_tempLocation=m_tempLocation->pnext;
								}
								xylocation.XPosition[0]=m_tempLocation->position.nXs;
								xylocation.YPosition[0]=-m_tempLocation->position.nYs;
								Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
								xylocation.XPosition[1]=xylocation.XPosition[0];
								xylocation.YPosition[1]=xylocation.YPosition[0];
								m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
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
						//�˴�����M02����û��M70 M80 M90�����
					}
					i+=j; //��ͷ����
					break;
				case 'X': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Xoffset1+=drilllocation.Xanalyse;//M02������ʱ����Ҫ��ƫ��ֵ�ۼƽ��е���
					
					i+=j; //��ͷ����
					break;
				case 'Y': 
					ProcessXY(buf);
					ProcessData(&drilllocation);
					Yoffset1+=drilllocation.Yanalyse;//M02������ʱ����Ҫ��ƫ��ֵ�ۼƽ��е���
					
					i+=j; //��ͷ����
					break;
				default:
					i+=j;
					break;		
					
				}
			}
			//			m_firstLocation=m_tempLocation1;
			
			if(NULL==strstr(buf,"M70")&&NULL==strstr(buf,"M80")&&NULL==strstr(buf,"M90"))//���ڴ���û��M70 M80 M90�����
			{
				m_tempLocation=m_tempLocation1;
				while(Current!=m_tempLocation)
				{
					xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
					xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;	
					Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
					xylocation.XPosition[1]=xylocation.XPosition[0];
					xylocation.YPosition[1]=xylocation.YPosition[0];
					m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
					m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
					m_tempLocation=m_tempLocation->pnext;
				}
				xylocation.XPosition[0]=m_tempLocation->position.nXs+Xoffset1;
				xylocation.YPosition[0]=m_tempLocation->position.nYs+Yoffset1;
				Drilllength+=Round(sqrt((xylocation.XPosition[0]-xylocation.XPosition[1])*(xylocation.XPosition[0]-xylocation.XPosition[1])+(xylocation.YPosition[0]-xylocation.YPosition[1])*(xylocation.YPosition[0]-xylocation.YPosition[1])));
				xylocation.XPosition[1]=xylocation.XPosition[0];
				xylocation.YPosition[1]=xylocation.YPosition[0];
				m_tempLocation->position.nXs=Round(xylocation.XPosition[0]);//�˲���ɶ�������������޸�
				m_tempLocation->position.nYs=Round(xylocation.YPosition[0]);
			}
			M02Num+=1;
			iPos+=GotoNextLine(iLineLen); 
			continue;
		}
		if(!strnicmp(buf, "R", 1) && bProHead == false)
		{	
			int i=0;//����ǰλ��
			int j=0;//������
			int k=0;//�����ظ�ִ�еĴ���
			double Xoffset=0;//����X�����ϵ�ƫ����
			double Yoffset=0;//����Y�����ϵ�ƫ����
			char buffer[256]; //�Ӵ�	
			while( j=GetTItemStr1(&buf[i],buffer) ) //���ǿմ�
			{
				switch( buffer[0] ) //�����Ӵ����ַ����д���
				{
					
				case 'R':
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						strrmv(buffer,"R");
						k=atoi(buffer);
					}
					i+=j; //��ͷ����
					break;
				case 'X': 
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Xoffset=drilllocation.Xanalyse;
					}
					i+=j; //��ͷ����
					break;
				case 'Y': 
					if( j == 1 )//û�в���
					{
						//û�в�������
					}
					else
					{
						ProcessXY(buf);
						ProcessData(&drilllocation);
						Yoffset=drilllocation.Yanalyse;
					}
					i+=j; //��ͷ����
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
			//�˴���������
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
				//G82���ݴ����
			}
			m_FlagDualLine=0;
			m_firstLocation=Current;//�˴���ǰһ����λ���굱�������ʼ���긳�����׵�ַ
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
			//����M99�ı�־λ����ʱ����������
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
//------------------------------------------------------zns�޸�
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
Description: �޸�ԭ��λ�ã����浽ԭʼ����ԭ���Ӧ���λ�ã�����Ӧ���ļ�importfilecontent�е�ԭ�����G93
Input:    
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
void CMastProgInOut::ModifyOrigiLocation()
{
}
/********************************************************
Function: ModifyOrigiLocation
Description: �޸ĵ�����ļ�����importfilecontent
Input:    
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
void CMastProgInOut::ModifyImportFile()
{
}
/********************************************************
Function: ExportExe
Description: �����ļ�����,����Ϊ�����ļ������ַ���
Input:   CString filestr :�����ļ��ַ���
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
int CMastProgInOut::ExportExe(CString filestr)
{
	CFile file;	
	CFileException fileException;
	if(file.Open(this->ExportFileInfo,this->ExportOpenMode,&fileException))//���㣺�򿪳ɹ�
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
Description: ���õ����ļ�·����Ϣ
Input:   CString filename 
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
void CMastProgInOut::SetImportFile(CString filename)
{
	this->ImportFileInfo = filename;
}
/********************************************************
Function: SetExportFile
Description: ���õ����ļ�·����Ϣ 
Input:   CString filename  UINT openmodeflags
Output: 
Return: 
Others: ����˵�� 
*********************************************************/
void CMastProgInOut::SetExportFile(CString filename,UINT openmodeflags)
{
	this->ExportFileInfo = filename;
	this->ExportOpenMode = openmodeflags;
}
/********************************************************
Function: ProcessMirro
Description: ���ݲ�ͬ����ϵ��ת��x��yλ�á�ֵ
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
	default://��δָ������ϵ����Ĭ��Ϊ��������ϵ
		m_DrillEnvPara.nXMirror=1;
		m_DrillEnvPara.nYMirror=1;
		m_DrillEnvPara.XYchangeFlag=0;	
		break;
		
	}
	if(m_DrillEnvPara.nXMirror==-1)//X������
	{
		XPositonMirro(firstnode);
	}
	if(m_DrillEnvPara.nYMirror==-1)//Y������
	{
        YPositonMirro(firstnode);
	}
	if(m_DrillEnvPara.XYchangeFlag==1)//XY���꽻��
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
	int k=ins.GetLength();//�ļ�����
	while( (c = ins.GetAt(ibegin +ilen) ) != 0Xd&&(c = ins.GetAt(ibegin +ilen) ) != 0Xa) //δ���س���
	{
		newline[ilen] = c;
		ilen++;
		
		if(ibegin +ilen==k)
		{
			break;
		}
	}
	newline[ilen] = 0;//��ԭ���Ļس�����0�������
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
		outs[j++]=ins[i++]; //�����һ���ַ��������
		//���������ַ�
		while( (ins[i] >= '0' && ins[i] <= '9')  //����
			|| (ins[i] == '.')                   //С����
			|| (ins[i] == '+')                   //�Ӻ�
			|| (ins[i] == '-')                   //����
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
Description: c��������о�̬�б�1�ĺ���
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessT(char *ins,ToolParaStruct * Toolpara)//
{
	//	CMainFrame *pwnd=(CMainFrame *)AfxGetMainWnd();
	int errCode = 0;
	int i;//����ǰλ��
	int j;//������
	int iTNum=1;  //���ߺ�
	int iparaid=0; //����id
	char buf[256]; //�Ӵ�
	
	int ival=0;
	double fval=0.0; 
	bool bval = 0;
	
	i=0; j=0;
	
	while( j=GetTItemStr1(&ins[i],buf) ) //���ǿմ�
	{
		switch( buf[0] ) //�����Ӵ����ַ����д���
		{
			//��̬����1
		case 'T'://���߱��
			if( j == 1 ) return 1;//�մ��������˳�
			ival = atoi(&buf[1]);//�ӵڶ����ַ���ʼת������
			iTNum = ival;
			if( iTNum < 1 ) iTNum = 1;
			if( iTNum > ATP_Tool_NUM ) iTNum = ATP_Tool_NUM; 
			m_DrillStatic[definetoolnum].iToolNumber = iTNum;//todo
			Toolpara[iTNum].FileStaticPara.iToolNumber=iTNum;
			i+=j; //��ͷ����
			break;
		case 'C': //����ֱ��
			if( j == 1 )//û�в���
			{
				fval = 0.0; //Ĭ��Ϊ0.0
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
			definetoolnum++;//�˴��Լӣ�����δ����ֱ���ĵ���
			i+=j; //��ͷ����
			break;
		case 'M': //��������
			if( j == 1 )
			{
				ival = 1; //Ĭ��Ϊ����1������ط��е����⡣
			}
			else
			{
				ival = atoi(&buf[1]);
			}
			m_DrillStatic[definetoolnum].ToolType = ival;
			Toolpara[iTNum].FileStaticPara.ToolType=ival;
			i+=j;
			break;
		case 'S': //����ת��
			if( j == 1 ) 
			{
				fval = 0.0; //Ĭ��Ϊ0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_SpindleSpeed = fval;
			Toolpara[iTNum].FileStaticPara.m_SpindleSpeed=fval;		
			i+=j;
			break;
		case 'F': //�����ٶ�
			if( j == 1 ) 
			{
				fval = 0.0; //Ĭ��Ϊ0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_RetractRate = fval;
			Toolpara[iTNum].FileStaticPara.m_RetractRate=fval;
			i+=j;
			break;
		case 'B': //�����ٶ�
			if( j == 1 ) 
			{
				fval = 0.0; //Ĭ��Ϊ0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_PlungeRate = fval;
			Toolpara[iTNum].FileStaticPara.m_PlungeRate=fval;
			i+=j;
			break;
		case 'R': //���̺���
			if( j == 1 ) 
			{
				fval = 0; //Ĭ��Ϊ0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_MagazineNum = (int)fval;
			Toolpara[iTNum].FileStaticPara.m_MagazineNum = (int)fval;
			i+=j;
			break;
		case 'Z': //Z��ƽ�����
			if( j == 1 ) 
			{
				fval = 0.0; //Ĭ��Ϊ0.0
			}
			else
			{
				fval = atof(&buf[1]);
			}
			m_DrillStatic[definetoolnum].m_Compensate = fval;
			Toolpara[iTNum].FileStaticPara.m_Compensate=fval;
			i+=j;
			break;
		case 'H': //��������
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
		case 'P': //�ֶ���
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
		}//endof switch( buf[0] ) //�����Ӵ����ַ����д���
	}//endof while( j=GetTItemStr(&ins[i],buf) ) //���ǿմ�
	return errCode;
}
/********************************************************
Function: ProcessXY
Description: �����λ��Ϣ��(�������ַ���������ֻ������XY������Ϣ���ַ���)
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessXY(char *ins )//
{	
	int errCode = 0;
	int i=0;//����ǰλ��
	int j=0;//������
	int iTNum=1;  //���ߺ�
	int iparaid=0; //����id
	char buf[256]; //�Ӵ�
	
	
	
	while( j=GetTItemStr1(&ins[i],buf) ) //���ǿմ�
	{
		switch( buf[0] ) //�����Ӵ����ַ����д���
		{
			//��̬����1
		case 'X'://���߱��
			if( j == 1 )//û�в���
			{
				//û�в�������
				strcpy(drilllocation.x1,"0");
			}
			else
			{
				strcpy(drilllocation.x1,&buf[1]);
			}
			
			i+=j; //��ͷ����
			break;
		case 'Y': //����ֱ��
			if( j == 1 )//û�в���
			{
				strcpy(drilllocation.y1,"0");	
			}
			else
			{
				strcpy(drilllocation.y1,&buf[1]);
			}
			
			i+=j; //��ͷ����
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
Description: ���ַ���s2���ַ���s1��ɾ��������ɾ����s1��ָ��
Input:    
Output: 
Return: 
Others: 
*********************************************************/
char* CMastProgInOut::strrmv( char *s1, char *s2)//
{ 
	char *w=s1, *r=s1, *p;//w: д��λ�ã�r�� ����λ��   p: ���ڴ���s2 
	for( p=s2; *r; *w++=*r++ )
		!(*p)&&(w-=(p-s2),p=s2), (*r!=*p)?p=s2:p+=1;
	*p ? *w='\0' : *(w-=(p-s2))='\0';//���*p=='\0'��˵��s1ĩβƥ��ɹ��ˡ�
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
	if(0!=(m_ndataM+m_ndataN))//���´���ı��������ƵĴ���
	{
		
		if(m_LeadTrailFlag==true)//�˴���ʾǰ����
		{
			
			if(!strnicmp(q->x1, "-", 1))//�����Ƕ�X����������ж�
			{
				if(NULL==strstr(q->x1,"."))//����û��С�����
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
				else//�˴��������ֱ����С�����
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			else//���¶���������д���
			{
				if(NULL==strstr(q->x1,"."))//�˴���������С����
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
				else//�˴��������С�����
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			//////////////////////////////////////////////////////////////�����Ƕ�Y�����ʵ��
			
			if(!strnicmp(q->y1, "-", 1))//���¶Ը�������д���
			{
				if(NULL==strstr(q->y1,"."))//�����ַ��в���С�����
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
				else//�����ַ��д�С�����
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			else//���¶�y��������д���
			{
				if(NULL==strstr(q->y1,"."))//�˴���û��С��������ݲ���
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
				else//�˴�����С��������ݲ���
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
		else/////////////////////////////////////////////////////////////////�������δ���ʵ�ֵ��Ǻ���
		{
			if(!_strnicmp(q->x1, "-", 1))//���¶�X��������д���
			{
				if(NULL==strstr(q->x1,"."))//�˴���û��С��������ݽ��д���
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
				else//�˴�����С��������ݽ��д���
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			
			else//���¶�X��������д���
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
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			}//�����Ƕ�Y�����ʵ��
			
			if(!_strnicmp(q->y1, "-", 1))//���¶Ը�������д���
			{
				if(NULL==strstr(q->y1,"."))//�˴���û��С��������ݲ���
				{
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);j++)
						b[j]='0';
					Insertdecimo(q->y2,b,1);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM+1);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
			else//����Y����������д���
			{
				if(NULL==strstr(q->y1,"."))//����û��С����
				{
					strcpy(q->y2,q->y1);
					for(int j=0;j<((m_ndataM+m_ndataN)-(int)strlen(q->y2));j++)
						b[j]='0';
					Insertdecimo(q->y2,b,0);
					c[0]='.';
					Insertdecimo(q->y2,c,m_ndataM);
					if(METRIC==true)
					{
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
					}
					else
					{
						drilllocation.Yanalyse=atof(q->y2)*25.4*1000;
					}
				}
				else//������С�����
				{
					if(METRIC==true)//�˴�������ǹ��Ƶ�
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
					else//�˴��������Ӣ�Ƶ�
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
	else//������ǰλ�ͺ�λ����ȡĬ��ֵ�����
	{
		if(METRIC==true)//�����ǹ��ƽ��д���
		{
			m_ndataM=3;
			m_ndataN=3;
			if(m_LeadTrailFlag==true)//�˴���ʾǰ����
			{
				
				if(!_strnicmp(q->x1, "-", 1))//�����Ƕ�X�ĸ�ֵ���в���
				{
					if(NULL==strstr(q->x1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000;//�������뻹û��ʵ��
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
				else//�����Ƕ�X����ֵ���д���
				{
					if(NULL==strstr(q->x1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000;//�������뻹û��ʵ��
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
				//�����Ƕ�Y����Ĵ���
				if(!strnicmp(q->y1, "-", 1))//�����Ǹ���Y����
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
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
				else//����������Y������
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
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
			else//�˴���ʾǰ����
			{
				
				if(!strnicmp(q->x1, "-", 1))//X���긺��
				{
					if(NULL==strstr(q->x1,"."))//û��С���������
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						Insertdecimo(q->x2,a,1);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000;//�������뻹û��ʵ��
					}
					else//��С���������
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
				else//X���������
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						Insertdecimo(q->x2,a,0);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000;//�������뻹û��ʵ��
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
				//�����Ƕ�Y�����ʵ��
				if(!strnicmp(q->y1, "-", 1))//�˴�ʵ�ֵ���y������
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
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
				else//��Y����������в���
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000;//�������뻹û��ʵ��
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
		else//������Ĭ��Ӣ�� ���д���
		{
			m_ndataM=2;
			m_ndataN=4;
			if(m_LeadTrailFlag=true)//�˴���ʾǰ����
			{
				
				if(!strnicmp(q->x1, "-", 1))//�����Ƕ�X�ĸ�������в���
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000*25.4;//�������뻹û��ʵ��
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
				else//�����Ƕ�X����������в���
				{
					if(NULL==strstr(q->x1,"."))
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						strcat(q->x2,a);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000*25.4;//�������뻹û��ʵ��
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
				//�����Ƕ�Y����Ĵ���
				if(!strnicmp(q->y1, "-", 1))//�����Ƕ�Y�ĸ�������д���
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//�������뻹û��ʵ��
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
				else//�����Ƕ�Y����������д���
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//�������뻹û��ʵ��
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
			else//�˴���ʾǰ����
			{
				
				if(!strnicmp(q->x1, "-", 1))//�˴���X�ĸ�������д���
				{
					if(NULL==strstr(q->x1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2)+1);i++)
							a[i]='0';
						Insertdecimo(q->x2,a,1);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->x2)*1000*25.4;//�������뻹û��ʵ��
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
				else//�˴���X����������д���
				{
					if(NULL==strstr(q->x1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->x2,q->x1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->x2));i++)
							a[i]='0';
						Insertdecimo(q->x2,a,0);
						c[0]='.';
						Insertdecimo(q->x2,c,m_ndataM);
						drilllocation.Xanalyse=atof(q->x2)*1000*25.4;//�������뻹û��ʵ��
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
				//�����Ƕ�Y�����ʵ��
				if(!strnicmp(q->y1, "-", 1))//���¶�Y�ĸ�������д���
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2)+1);i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM+1);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//�������뻹û��ʵ��
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
				else//���¶�Y����������д���
				{
					if(NULL==strstr(q->y1,"."))//�����Ƕ�û��С������д���
					{
						strcpy(q->y2,q->y1);
						for(int i=0;i<((m_ndataM+m_ndataN)-(int)strlen(q->y2));i++)
							b[i]='0';
						strcat(q->y2,b);
						c[0]='.';
						Insertdecimo(q->y2,c,m_ndataM);
						drilllocation.Yanalyse=atof(q->y2)*1000*25.4;//�������뻹û��ʵ��
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
Description: ��str2�е��ַ�����ָ��λ�ò��뵽str1��
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
Description: decimal��ʾ�������뱣����λ��
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
Description: �˺���ʵ�ֵĹ��ܣ�����λ���ݽڵ��е�XY���갴�մ��������ֵ�����޸�
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
Description: �˺������ܣ���������ľ��Ƚ���ʼ���յ�����֮���
����ֽ�ɶ�������λ��Ϣ��������������2�ַ���������ķֽ⣩
::����Ĳ���������Բ�����ߺͽ���֮��ľ���
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
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter*1000;//�õ��뾶 �뾶��
	//�˴��뾶Ϊ�ӹ��ʼ��еİ뾶�����ڡ�����ת�����˵����޸ĵ���ֱ�����˴���Ҫ���µİ뾶/ֱ����
	
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
Description:�������ܣ����ݵõ�����ʼ���ԭ����������һ���˽��εĿ�λ����
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessEightPin()//
{
	double EightPin[8][2];//���ڰ˽��η�װ�İ˸��������ʱ����(0��0��x���ꣻ0��1��y����)
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
Description:���������յ���������˫��ֱ����������겢�����λ��������
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessDualLine()
{
	bool DirectionFlag=true;//���ڴ����жϳ�����XY�ķ���(trueΪ��X����)
	int tempnumX=0;//������ʱ�洢x������������������
	int tempnumY=0;//������ʱ����y������������������
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
	if(DirectionFlag)//��X������
	{
		if(xylocation3.XPosition[0]>xylocation3.XPosition[1])//��X����������
		{
			if(fabs(xylocation3.XPosition[0]-(tempnumX*xylocation3.XPosition[2]+xylocation3.XPosition[1]))>1.27*1000)
			{
				//�˴����ڼ�������б���
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
				if(xylocation3.YPosition[0]>xylocation.YPosition[1])//��Y�ĸ�����
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
				else//��Y��������
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
		else//��X��������
		{
			if(fabs(xylocation3.XPosition[1]-(tempnumX*xylocation3.XPosition[2]+xylocation3.XPosition[0]))>1.27*1000)
			{
				//�˴����ڼ�������б���
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
				if(xylocation3.YPosition[0]>xylocation3.YPosition[1])//��Y�ĸ�����
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
				else//��Y��������
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
	else//�˴�����Y�����˫��ֱ��
	{
		if(xylocation3.YPosition[0]>xylocation3.YPosition[1])//��Y���·�������
		{
			if(fabs(xylocation3.YPosition[0]-(tempnumY*xylocation3.XPosition[2]+xylocation3.YPosition[1]))>1.27*1000)
			{
				//�˴����ڼ�������б���
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
				if(xylocation3.XPosition[0]>xylocation.XPosition[1])//��X�ĸ�����
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
				else//��X��������
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
		else//��Y���ϵķ�������
		{
			if(fabs(xylocation3.YPosition[1]-(tempnumY*xylocation3.XPosition[2]+xylocation3.YPosition[0]))>1.27*1000)
			{
				//�˴����ڼ�������б���
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
				if(xylocation3.XPosition[0]>xylocation3.XPosition[1])//��X�Ḻ��������
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
				else//��X������������
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
	m_lastLocation=Current;//�˴���������һ�����굱�����ĩβ��ַ
	return 0;
}
/********************************************************
Function: ProcessCircle
Description:ͨ������Ĳ��������γ�Բ��ÿ��Բ�ĵ����� ����Ĳ�����Բ���ߺ�Բ�ཻ��֮��ľ���
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessCircle(double p,ToolParaStruct * Toolpara)
{
	//CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();
	double angleNum=0;//������ļ��ֵ��������ĽǶ�
	double diameter;
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter*1000;//�õ��뾶
	xylocation4.XPosition[2]=xylocation4.XPosition[0]+xylocation4.XPosition[1];
	xylocation4.YPosition[2]=xylocation4.YPosition[0];
	angleNum=asin(sqrt(fabs(diameter*diameter-(diameter-p)*(diameter-p)))/(xylocation4.XPosition[1]/2))*2;
	for(double i=0;i<360;i+=angleNum)
	{
		xylocation.XPosition[0]=xylocation4.XPosition[2]-(xylocation4.XPosition[1]-xylocation4.XPosition[1]*cos(Pi/180*i));//������Բ���ϵ�λ��
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
Description:���ݵõ���ӳ��int������õ���ӳ������λ�ò�����������(Ĭ�ϴ����������7��4��)
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessArray(int *p,double a,double b,ToolParaStruct * Toolpara)//�������ܣ� 
{
	//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//��ȡָ�������ڵľ��
	//a��x����ʼ���� b��y����ʼ����
	double diameter;
	diameter = Toolpara[m_toolnumber].FileStaticPara.m_Diameter;;//������ʱ�����atp�ļ��еõ�����ӳֱ��
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
Description:����a[7]��һά���飬����ת��Ϊ�ܱ�ProcessArray����Ķ�ά����
Input:    
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::ProcessArray1(char *str,double xPosition,double yPosition,ToolParaStruct * Toolpara)//�������ܣ�
{	
	static int k=1;
	int *tenpNum=&TempArray[0][0];
	double Xdirection=0;
	double Ydirection=0;
	
	while('\0'!=*str)
	{
		for(int i=0;i<40;i++)//�˴�Ĭ�������ӡ���ַ��������40�����ַ�
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
						//�˴����ݴ���ƣ����б�����
						break;
					}
					
				}
				if(1==k)
				{
					xylocation.XPosition[0]=xPosition;
					xylocation.YPosition[0]=yPosition;
					Xdirection=xylocation.XPosition[0];//X����ʼ������
					Ydirection=xylocation.YPosition[0];//Y����ʼ������
					k++;
				}
				else
				{
					Xdirection=xylocation.XPosition[0];//X����ʼ������
					Ydirection=xylocation.YPosition[0];//Y����ʼ������
				}
				ProcessArray(tenpNum,xylocation.XPosition[0],xylocation.YPosition[0],Toolpara);
				//				CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//��ȡָ�������ڵľ��
				double diameter;
				diameter=Toolpara[m_toolnumber].FileStaticPara.m_Diameter;//������ʱ�����atp�ļ��еõ�����ӳֱ��
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
Description:����ʱ����������ӽڵ�
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
Description:��ɸ�����ʼ����ɾ������ڵ�
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
				Previous=NULL;//�ͷ�ָ���Ժ�ָ���ÿ� ���򽫳�ΪҰָ��
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
	//	CMainFrame * pwnd = (CMainFrame *)AfxGetMainWnd();//��ȡָ�������ڵľ��
	if(NULL==firstnode)
	{
		return false;//��ʾû�п�λ��Ϣ����
	}
	m_tempLocation=firstnode->pnext;	//�˴�Ҫ�����Ҫ�г���ԭ����趨
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
				//��������
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
				//��������
			}
			
			m_tempLocation=m_tempLocation->pnext;
			
		}
	}
	else
	{
		//�˴����������Ĵ���
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
Description:���ַ����е�Сд��ĸת���ɴ�д��ĸ
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
Description:��Ӣ�Ƶ�С��ת��Ϊ���Ƶĺ���
Input:  float data�����Ӣ��С��;  
Output: 
Return: float ���صĹ��ƺ�����
Others: 
*********************************************************/
double CMastProgInOut::TranslateData(double data)
{
	return data*2.54*10;
}
/********************************************************
Function: FreeDrillLink
Description:��Ӣ�Ƶ�С��ת��Ϊ���Ƶĺ���
Input:  float data�����Ӣ��С��;  
Output: 
Return: float ���صĹ��ƺ�����
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
	m_Previous=NULL;//�ͷ���ռ�õĿռ������ָ���ƿ�
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
Description://�����������ģʽ
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
Description:�����������ģʽ
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
Description:�����߲ۿ�
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
Description:����Բ�ۿ�
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
	ProcessCircle(20,Toolpara);//�˴�Ĭ�Ͻ����Բ�������֮��ľ���Ϊ10um
}
/********************************************************
Function: ProcessCannedTextPattern
Description:�����ַ�����
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
Description:����˫��ֱ���
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
Description:����˽ǿ�
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
			//�˴������ݴ����
		}
	}
	m_FlagEightPin+=1;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:�����ļ�������һ��
Input:  
Output: 
Return: 
Others: 
*********************************************************/
int CMastProgInOut::GotoNextLine(int linelength)//
{
   	linelength= linelength + 2 ; //����0D0A
	m_LineNum++;
	return linelength;
}
/********************************************************
Function: ProcessCannedTextPattern
Description:1.X·���Ż�,ʵ�ֻ���x���������
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::XDrillOptProcess(HoleInfoNode * drilllink)//
{
	
	HoleInfoNode *currentnode=drilllink->pnext;//���ź�����������һ���ڵ�
	HoleInfoNode *testnode=currentnode->pnext;//������ڵ�
	HoleInfoNode *pnode = NULL;//��ǰ�ȶԽ��
	HoleInfoNode *prevnode=NULL;//��ǰ�ȶԽڵ��ǰ�����
	//////////////////////////////////////////////////////////////////////////
	///////���½����пװ�X�����С��������,X��ͬ��Y��С������
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
			else if(testnode->position.nXs==pnode->position.nXs)  //�����Խڵ���ڵ�ǰ�ȶԽڵ㣬�Ƚ�y�����	
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
			else// //�����Խڵ�С�ڵ�ǰ�ȶԽڵ㣬ֱ�Ӳ���
			{
				break;
			}						
		}
		//if (prevnode==currentnode) 
		if (pnode==testnode)//0316��
		{
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else//�������
		{
			currentnode->pnext=testnode->pnext;
			testnode->pnext=prevnode->pnext;
			prevnode->pnext=testnode;
			testnode=currentnode->pnext;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/*	//��ӡ����
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
	currentnode=drilllink->pnext;//���ź�����������һ���ڵ�
    testnode=currentnode->pnext;//������ڵ�
	
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
			//-------������ͬX���� �Ŀ���
			tempnode=testnode;
			//	int i=1;
			riseflag=true;
			while (tempnode->pnext!=NULL&& tempnode->position.nXs==tempnode->pnext->position.nXs)
			{
				//	i++;
				if (tempnode->position.nYs>tempnode->pnext->position.nYs)
				{
					riseflag=false;//����
				}//�˴��������ж����壿0316
				tempnode=tempnode->pnext;				
			}
			//----------------
			//	if (i==1)//ֻ��һ��
			if (tempnode==testnode)
			{
				currentnode=testnode;
				testnode=testnode->pnext;
			}
			else//����һ��
			{
				ypos_cur=currentnode->position.nYs;
				if (riseflag==true)//����
				{
					ypos_min=testnode->position.nYs;
					ypos_max=tempnode->position.nYs;
					
					if (abs(ypos_cur-ypos_min)<=abs(ypos_cur-ypos_max))//������������� ��ֱ������
					{
						//	currentnode->pnext=testnode;//�˴���ֵû������
						testnode=tempnode->pnext;
						currentnode=tempnode;
					}
					else//���������������Ҫ��xλ����ȵĲ�������
					{
						//------��������
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
				else//����
				{
					ypos_min=tempnode->position.nYs;
					ypos_max=testnode->position.nYs;
					
					if (abs(ypos_cur-ypos_min)<=abs(ypos_cur-ypos_max))//������������� ����Ҫ��xλ����ȵĲ�������
					{
						//------��������
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
					else//�������������ֱ������
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
	/*	//��ӡ����
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
Description:2.Y·���Ż�
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::YDrillOptProcess(HoleInfoNode * drilllink)//
{
	
	HoleInfoNode *currentnode=drilllink->pnext;//���ź�����������һ���ڵ�
	HoleInfoNode *testnode=currentnode->pnext;//������ڵ�
	HoleInfoNode *pnode = NULL;//��ǰ�ȶԽ��
	HoleInfoNode *prevnode=NULL;//��ǰ�ȶԽڵ��ǰ�����
	//////////////////////////////////////////////////////////////////////////
	///////���½����пװ�X�����С��������,X��ͬ��Y��С������
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
			else// //�����Խڵ�С�ڵ�ǰ�ȶԽڵ㣬ֱ�Ӳ���
			{
				break;
			}						
		}
		//if (prevnode==currentnode) 
		if (pnode==testnode)//0316��
		{
			currentnode=testnode;
			testnode=testnode->pnext;
		}
		else//�������
		{
			currentnode->pnext=testnode->pnext;
			testnode->pnext=prevnode->pnext;
			prevnode->pnext=testnode;
			testnode=currentnode->pnext;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	/*	//��ӡ����
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
	currentnode=drilllink->pnext;//���ź�����������һ���ڵ�
    testnode=currentnode->pnext;//������ڵ�
	
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
			//-------������ͬX���� �Ŀ���
			tempnode=testnode;
			while (tempnode->pnext!=NULL&& tempnode->position.nYs==tempnode->pnext->position.nYs)
				tempnode=tempnode->pnext;				
			//----------------
			if (tempnode==testnode)
			{
				currentnode=testnode;
				testnode=testnode->pnext;
			}
			else//����һ��
			{
				xpos_cur=currentnode->position.nXs;
				xpos_min=testnode->position.nXs;
				xpos_max=tempnode->position.nXs;
				
				if (abs(xpos_cur-xpos_min)<=abs(xpos_cur-xpos_max))//������������� ��ֱ������
				{
					//	currentnode->pnext=testnode;//�˴���ֵû������
					testnode=tempnode->pnext;
					currentnode=tempnode;
				}
				else//���������������Ҫ��xλ����ȵĲ�������
				{
					//------��������
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
Description:3.�����Ż�
Input:  
Output: 
Return: 
Others: 
*********************************************************/
void CMastProgInOut::DistanceDrillOptProcess(HoleInfoNode * drilllink)//
{
	HoleInfoNode *currentnode=NULL;//���ź�����������һ���ڵ�
	HoleInfoNode *minnode=NULL;
	HoleInfoNode *pnode=NULL;
	HoleInfoNode *preminnode=NULL;
	HoleInfoNode *prenode=NULL;
	int prenodetoolnum;//��¼��һ���ĵ��ߺ�
	double orginaldistance=0;
	double processdistance=0;
	double xp=0;
	double yp=0;
	
	double x0=0;
	double y0=0;
	double x1=0;
	double y1=0;
	//��ӡ����---�Ż�ǰ
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
	//******************����ÿ�ѵ��ߵ�һ�����Ϊ��Сλ�ý��***************//
	currentnode=drilllink;//���ź�������һ�����  
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
			//	if (mindis==0)//�ʼ����
			if (mindis==-1)//�ʼ���� //0318
			{
				//�˴����ô�����С��λ��
				TRACE("test1");
				
			}
			else
			{
				//������С��λ��			 
				if (preminnode==currentnode)//��С�ױ������ڴ˵�����ǰ���������κδ���
				{
				}
				else
				{
					preminnode->pnext=minnode->pnext;
					minnode->pnext=currentnode->pnext;
					currentnode->pnext=minnode;
				}		
				
				//�������ź����������һ�����currentnode Ϊ��һ������������ε����һ����  
				if (minnode==prenode)//��Сλ�ÿ���ĳ�ֵ������һ����
				{
					currentnode=preminnode;//����Сλ�ÿ���ĳ���ߵ����һ���ף�������С����Ҫ���뵽ԭcurrentnode֮��
					                        //����֮�󣬸õ�������ε����һ���������preminnode
				}
				else
				{
					currentnode=prenode;
				}		 
			}
			prenodetoolnum=pnode->m_ToolNum;
			minnode=pnode;
			preminnode=currentnode;
			mindis=dis;	//��ʼ��ÿ�ֵ�����Сλ��	
		}
		prenode=pnode;
		pnode=pnode->pnext;
	}
	//���һ�ֵ��ߴ���
	//������С��λ��			 
	if (preminnode==currentnode)//��С�ױ������ڴ˵�����ǰ���������κδ���
	{
	}
	else
	{
		preminnode->pnext=minnode->pnext;
		minnode->pnext=currentnode->pnext;
		currentnode->pnext=minnode;
	}
	
	//**************************************************************************//
	TRACE("��ͬ���ߵ�һ�������֮��\n");
	//��ӡ����
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
	//**************************�Ż�����***************************************//
	
	pnode=drilllink->pnext;
/*	while (pnode!=NULL)
	{
		pnode->position.distance=-1;
		pnode=pnode->pnext;
	}*/
	currentnode=drilllink;//���ź�������һ�����  
	prenodetoolnum=-1;
	HoleInfoNode *beginnode=currentnode;//��ʼ��beginnode
	j=1;
	mindis=-1;
//	int i=1;
	while (currentnode->pnext!=NULL)
	{	
		pnode=currentnode->pnext;//��������������������һ����㿪ʼ��ǰ�����ź���ĵ�������β��ٱ��������ٱ�������
//		j=1;
		while (pnode!=NULL)
		{
			if (pnode->m_ToolNum!=prenodetoolnum)//��������һ�ѵ��߲���ͬ
			{	
				if (mindis==-1)
				{
					//����beginnode
				//	beginnode=pnode;
					prenodetoolnum=pnode->m_ToolNum;
				//	currentnode=beginnode;
					currentnode=pnode;
				}
				else
				{
					//������Сλ�ÿ� 
					if (currentnode->pnext==minnode)//��С����������������һ���
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
			else//��������һ�ѵ�����ͬ
			{
				xp=(pnode->position.nXs-currentnode->position.nXs)/1000.;// �˴���Ҫ�Ƚ�currentnode��beginnode
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
			//������С��
		//	prenodetoolnum=pnode->m_ToolNum;
			if (currentnode->pnext==minnode)//��С����������������һ���
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
	pnode=beginnode->pnext;//�����ӵ�ǰ��������ο�ʼ��ǰ�����ź���ĵ�������β��ٱ��������ٱ�������
	j=1;
	
	  while (pnode!=NULL)
	  {
	  //	TRACE("pnode%d:%d,%d,%d\n",j++,pnode->position.nXs,pnode->position.nYs,pnode->m_ToolNum);
	  if (pnode->position.distance!=-1)
	  {
	  TRACE("test");
	  }
	  else//δ������������
	  {
	  if (pnode->m_ToolNum!=prenodetoolnum)//��������һ�ѵ��߲���ͬ
	  {
	  
		if (mindis==-1)
		{
		//����beginnode
		beginnode=pnode;
		prenodetoolnum=pnode->m_ToolNum;
		currentnode=beginnode;
		}
		else
		{
		//������Сλ�ÿ� 
		if (currentnode->pnext==minnode)//��С����������������һ���
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
			else//��������һ�ѵ�����ͬ
			{
			xp=(pnode->position.nXs-currentnode->position.nXs)/1000.;// �˴���Ҫ�Ƚ�currentnode��beginnode
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
				//������С��
				if (currentnode->pnext==minnode)//��С����������������һ���
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
	TRACE("�Ż�֮��\n");
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
	
/*	TRACE("��ʹ���Ż�  ʱ���ܾ���Ϊ��%.1f\n",(float)orginaldistance);
	TRACE("ʹ�þ����Ż�ʱ���ܾ���Ϊ��%.1f\n",(float)processdistance);*/
	
}
/********************************************************
Function: CopyHolePosNode
Description:ʵ�ֶԿ�λ��������ĸ���
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
return -1;//Ҫ���Ƶ�����Ϊ�գ���ִ�и��Ʋ���
this->m_WorkPosition->m_Toolform=this->m_OriPosition->m_Toolform;
this->m_WorkPosition->m_ToolNum=this->m_OriPosition->m_ToolNum;
this->m_WorkPosition->m_LINENUM=this->m_OriPosition->m_LINENUM;
this->m_WorkPosition->m_CurrentDrillNum=this->m_OriPosition->m_CurrentDrillNum;
this->m_WorkPosition->position.nXs=this->m_OriPosition->position.nXs;
this->m_WorkPosition->position.nYs=this->m_OriPosition->position.nYs;
this->m_WorkPosition->pnext=NULL;
previousnode=this->m_WorkPosition;//�����������ͷ���ָ��outlist����previousnodeִ��ָ����һ������
this->m_OriPosition=this->m_OriPosition->pnext;
while(this->m_OriPosition)
{
currentnode=(HoleInfoNode *)malloc(sizeof(HoleInfoNode));//��ǰ�������
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


int CMastProgInOut::CreateAndCopyHolePosNode(HoleInfoNode *outlist)//ʵ�ֶԿ�λ��������ĸ���
{
	
/*	HolePosNode *currentnode=NULL;
HolePosNode *previousnode=NULL;
if(inlist==NULL)
return -1;//Ҫ���Ƶ�����Ϊ�գ���ִ�и��Ʋ���
if (outlist==NULL)
return -1;//����ͷ���Ϊ�գ���ִ�и��Ʋ���
outlist->m_Toolform=inlist->m_Toolform;
outlist->m_ToolNum=inlist->m_ToolNum;
outlist->m_LINENUM=inlist->m_LINENUM;
outlist->m_CurrentDrillNum=inlist->m_CurrentDrillNum;
outlist->position.nXs=inlist->position.nXs;
outlist->position.nYs=inlist->position.nYs;
outlist->pnext=NULL;
previousnode=outlist;//�����������ͷ���ָ��outlist����previousnodeִ��ָ����һ������
inlist=inlist->pnext;
while(inlist)
{
currentnode=(HolePosNode *)malloc(sizeof(HolePosNode));//��ǰ�������
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
		return -1;//Ҫ���Ƶ�����Ϊ�գ���ִ�и��Ʋ���
	tempnode=m_OriPosition;
	outlist->m_Toolform=this->m_OriPosition->m_Toolform;
	outlist->m_ToolNum=this->m_OriPosition->m_ToolNum;
	outlist->m_LINENUM=this->m_OriPosition->m_LINENUM;
	outlist->m_CurrentDrillNum=this->m_OriPosition->m_CurrentDrillNum;
	outlist->position.nXs=this->m_OriPosition->position.nXs;
	outlist->position.nYs=this->m_OriPosition->position.nYs;
	outlist->pnext=NULL;
	previousnode=outlist;//�����������ͷ���ָ��outlist����previousnodeִ��ָ����һ������
	//	this->m_OriPosition=this->m_OriPosition->pnext;
	tempnode=tempnode->pnext;//0316��
	//	while(this->m_OriPosition)
	while(tempnode)
	{
		currentnode=(HoleInfoNode *)malloc(sizeof(HoleInfoNode));//��ǰ�������
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
		tempnode=tempnode->pnext;//0316��
	}
	free(currentnode);
	return 0;
}
