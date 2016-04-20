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
}DrillEnvParaStruct;
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
}DrillKnifeStruct;
//������ݽṹ
/*typedef struct
{	
	HoleEnvParaStruct m_DrillEnvPara;//��׻�������
	structDrillStatic m_DrillStatic[DRILL_Tool_NUM];//������Ϣ����
}structDrill;*/

//��λ��
typedef struct 
{
	int nXs;//��ͨ�׵�x����ֵ
	int nYs;//��ͨ�׵�y����ֵ
	float diameter;
}HolePositionStruct;
//��λ���ṹ
typedef struct HOLEINFONODE
{	
	int m_ToolNum;//������ǰ��λ������һ������
	int m_Toolform;//�ж�������Ƿ�����Ͽ׻�����ԭ��ף�0������ͨ�Ŀ�λ��Ϣ��1��������ԭ���λ��Ϣ 2��������ǲۿ� 3����������ַ���Ϣ 5:������Ͽ� ����
	int m_LINENUM;//��ʾ�˿�λ���ڴ���ļ��ĵڼ���
	int m_CurrentDrillNum;//����������ڵ�ǰ����ļ��д��ڵڼ�����
	HolePositionStruct position; //��λ��
	struct HOLEINFONODE *pnext;//ָ����һ���׽��
}HoleInfoNode;


typedef struct
{
	char x1[20];//ָ��x������ַ���ָ��
	char y1[20];//ָ��y������ַ���ָ��
	char x2[20];//ָ��x������ַ���ָ�루��������ͼ�С����Ĵ���
	char y2[20];//ָ��y������ַ���ָ�루��������ͼ�С����Ĵ���
	double  Xanalyse;//���������X�����꣨�˴����ڲۿ���Ҫ��¼��ʼ������յ����꣬������Ҫ�����׵�λ������ţ�������λֻ���õ�Xanalyse[0]���ɣ�
	double  Yanalyse;//���������Y������
	double  Xoriganposition;
	double  Yoriganposition;
}DrillLocationStruct;

typedef struct LINK
{
	double XLocation;
	double YLocation;
	struct LINK *pnext;
}LinkStruct;//���ڴ���ۿ׺��ַ�������ʱ����
typedef struct INSTRUCT
{
	char m_instruct[256];
	struct INSTRUCT *pnext;
}InLinkStruct;//���ڴ���ۿ׺��ַ�������ʱ����


typedef struct
{
	bool flagNeedCallback; //�ص����
	int  messageid;		//��Ϣid
	char *messagecode;//[4096]; //���
	unsigned long imilisecond;//��ʱ����ֵ	
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
	CString ImportFileInfo;//�����ļ���Ϣ���ļ���ȫ·��
	CString ExportFileInfo;//�����ļ���Ϣ���ļ���ȫ·��
	UINT	ExportOpenMode;
	CString importfilecontent;//�����ļ���Ϣ�ַ�������ԭʼ���ļ�����

	int m_toolnumber;//��ǰ�ļ�����ʱ��ŵ��ߺŵ�ȫ�ֱ�����0��ʾ��ǰ��λû��ѡ����ǣ�������Ȼ�����ʾ��Ӧ�ĵ��ţ�
	int DrillNumber;//���浶���д�׵�����  ÿ�ѵ��߶�Ӧ�Ŀ���
	int Drilllength;//���浶���п�λ֮����ܾ���
	

	int m_LineNum;//�����¼��ǰָ�����ڴ���ļ��ĵڼ���

	
	



	bool m_LineEndFlag;//��ʾÿ�н���ʱʱ���ǡ�/n������������false��ʾ���� true��ʾ�ǣ�
	bool m_FlagSubProEnd;//��ʾ�����ӳ���������־λ

	int m_FlagEightPin;//�˽��ε��жϱ�־λ����m_FlagEighPin<2ʱ��ʾ���µ��������궼���ڰ˽��εĶ�λ���꣩
	int m_FlagDualLine;//˫��ֱ��ʽ�жϱ�־λ����m_FlagDualLine<2ʱ��ʾ���µ��������궼����˫��ֱ��ʽ�������յ�����꣩
	bool m_Flagstr;//��ʾ�������Ƿ������ַ�����ӡ����ʼ����
	int m_XYdirection;//��1��ʾ��x�����ӡ��2��ʾ��y�����ӡ��
	char *tempstr;//���ڷָ��ַ�������ʱָ��
	char tempstr1[256];//���ڷָ��ַ�������ʱ����
	int a[7][4];//������ʱ����ַ�ת���ɵ��м����
	int TempArray[7][4];//������ʱ�洢�ַ�ת�������ĵ���
	char csCmd[256];	//��Ҫ���͵������ַ���
	int M02Num;//���ڴ��M02�Ѿ�ִ�еĴ���
	double Xoffset1;//����X�����ϵ�ƫ����
	double Yoffset1;//����Y�����ϵ�ƫ����

	
	
	XYLocationStruct xylocation;//�������λ���ݽṹ�е������ݵ����ݽṹʵ��(XPosition[0]��YPosition[0]���浱ǰ��λ������;XPosition[1]��YPosition[1]����ǰһ���������)
	XYLocationStruct xylocation1;//���ڴ�Ųۿ׵���ʼ�������ֹ����Ľṹʵ��
	XYLocationStruct xylocation2;//���ڴ�Ű˽���(ԭ��)����ʼ�������ֹ����Ľṹʵ�壨XPosition[0],YPosition[0]��ŵ�һ��������� XPosition[1],XPosition[1]��ż��������ԭ�����꣩
	XYLocationStruct xylocation3;//���ڴ��˫��ֱ��ʽ�����ͶԽ�������Ľṹʵ�壨XPosition[0],YPosition[0]��ŵ�һ��������� XPosition[1],XPosition[1]��Խ������꣬XPosition[2],XPosition[2]�������ڶ����Ļ�Ĭ�ϵ�XY���
	XYLocationStruct xylocation4;//���ڴ��Բ�����ĵ�����(XPosition[0],YPosition[0])��Բ�İ뾶(XPosition[1]) ��һ�����������ԭ������(XPosition[2],YPosition[2])

	LinkStruct        *m_Previous;
	LinkStruct        *m_Current;
	LinkStruct        *m_first;//���ϵ�ָ�������ڼ���ۿ�����ʱ���������ָ��
	LinkStruct        *m_Previous1;
	LinkStruct        *m_Current1;
	LinkStruct        *m_first1;//���ϵ�ָ���������������մ������ʱ���õ�ָ��
	LinkStruct        *m_temp;//������ʱ���ɽڵ�

	InLinkStruct	*m_PreviousCode;
	InLinkStruct	*m_CurrentCode;
	InLinkStruct	*m_firstCode;

	//HoleInfoNode *m_OriPosition;
	HoleInfoNode *Previous;
	HoleInfoNode *Current;
	HoleInfoNode *m_pnext;

	HoleInfoNode *m_tempLocation1;//������ʱ������п�λ�����ָ��ֵ(����ִ��M02�ڶ��ο�λ������׵�ַ)
	HoleInfoNode *m_firstLocation;//���ܵ���ָ��ʱ���ڴ���������׵�ַ��ǰһ����ַ
	HoleInfoNode *m_lastLocation;//���ܵ���ָ��ʱ���ڴ��������ĩβ��ַ
	//HoleInfoNode *m_WorkPosition;
	
	
	public:
	MastProgMessageNode *phead;//���캯���и���ֵNULL������ʱ�ͷ�
	HoleInfoNode *m_OriPosition;
	HoleInfoNode *m_WorkPosition;
	DrillEnvParaStruct m_DrillEnvPara;//��׻�������
	DrillKnifeStruct m_DrillStatic[DRILL_Tool_NUM];//������Ϣ����
	int TOOLNUM;//������¼����ļ���ʹ���˼��ѵ�
	DrillLocationStruct drilllocation;//�м���ɵ����ݽṹʵ��(��������XY�����ƫ��ֵ)
	HoleInfoNode *m_tempLocation;//������ʱ������п�λ�����ָ��ֵ
	XYLocationStruct StrarDrillLocation;//���ڴ洢��һ�����ʱ��ŵ���ʼ������
	int definetoolnum;//��¼�ļ��ж���ĵ������� 
	structDrill structdrill;
	HoleInfoNode *m_DrillXOptPosition;//x�Ż�����
	HoleInfoNode *m_DrillYOptPosition;//y�Ż�����

	bool relatedtodia;//�ļ������뵶��ֱ���йر�־ true���йأ��ۿס��ַ��ף�add by su
	HoleInfoNode *m_DrillDisOptPosition;//�����Ż�����
	int TotalDrillNumber;//�����ܵĿ���  add by su
	int m_ndataN;//��ʾ���Ƶĺ�λ
	int m_ndataM;//��ʾ���Ƶ�ǰ��λ
	bool m_LeadTrailFlag;//ǰ������жϱ�־λ��ture��ʾ��ǰ���㣩
	bool METRIC;//�������ݵı�ʾ��true��ʾ���ƣ�
	bool m_FlagRelativeMod;//���ģʽ���жϱ�־λ��false��ʾ���ھ���ģʽ��true��ʾ�������ģʽ��


	public:
	void ImportExe(CString *pfilecontent);//�����ļ��������ļ��򿪣���ȡ�����ļ����ݵ�importfilecontent��
	//---------------zns
	int ParseAnly(CString &ins,ToolParaStruct * Toolpara,DrillNote * drillnote,SpecialPoints * specialpoints);//�������������importfilecontent�����õ�ԭʼ��������
	//--------------zns
	void ModifyOrigiLocation ();//�޸�ԭ��λ�ã����浽ԭʼ����ԭ���Ӧ���λ�ã�����Ӧ���ļ�importfilecontent�е�ԭ�����G93
	void ModifyImportFile();//�޸ĵ�����ļ�����importfilecontent
	int ExportExe(CString filestr);//�����ļ�����,����Ϊ�����ļ������ַ���
	void SetImportFile(CString filename);//���õ����ļ�·����Ϣ,
	void SetExportFile(CString filename,UINT openmode);//���õ����ļ�·����Ϣ
	bool GetBoundryNote(HoleInfoNode *firstnode,CodeBoundary *codeboundary);//��ȡ�����е�XY�������Сֵ
	int CopyHolePosNode();//HoleInfoNode *inlist,HoleInfoNode *outlist);//���������Ѵ��ڣ�ֱ�Ӹ��ƿ�λ��Ϣ
	int CreateAndCopyHolePosNode(HoleInfoNode *outlist);//�����������ڣ���Ҫ��������������Ϣ
	void XDrillOptProcess(HoleInfoNode * drilllink);//1.X·���Ż�
	void YDrillOptProcess(HoleInfoNode * drilllink);//2.Y·���Ż�
	void DistanceDrillOptProcess(HoleInfoNode * drilllink);//3.�����Ż�
	void FreeDrillLink(HoleInfoNode *firstnode);
	int ProcessArray1(char *str,double xPosition,double yPosition,ToolParaStruct * Toolpara);//�������ܣ�����a[7]��һά���飬����ת��Ϊ�ܱ�ProcessArray����Ķ�Ϊ����
	bool AddPosition(int Toolnum ,int toolform ,int linenum,int x, int y);//�������ܣ����λ������������ӿ�λ��������
    int ProcessT(char *ins,ToolParaStruct * FileStaticPara );//��׾�̬�����Ĵ�����

	private:
	int GetNewLine1( CString &ins, int ibegin, char *newline );//����µ�һ��
	int GetTItemStr1( char *ins, char *outs );//����Ӵ����䳤��
	
	char* strrmv( char *s1, char *s2);//��s2�Ӵ���s1��ɾ��
	int ProcessXY(char *ins );//���λ��Ϣ��(�������ַ���������ֻ������XY������Ϣ���ַ���)
	int ProcessData(DrillLocationStruct *q);//��������:�����������Ϣ�Ľṹ���ڳ�Ա���������ⲿ��Ϣת��Ϊ��ȷ�Ĺ�����Ϣ����λum��
	int ProcessTrough( double p,ToolParaStruct * Toolpara);//�������ܣ�ͨ����ʼ���������ֹ������������ÿ����λ������(�������Ϊ������֮������С���)-�ۿ׺���
	int ProcessCircle(double p,ToolParaStruct * Toolpara);//�������ܣ�ͨ������Ĳ��������γ�Բ��ÿ��Բ�ĵ����� ����Ĳ����ǽǶ�
	int Insertdecimo(char*str1,char*str2,int n);//��һ���ַ�����ָ��λ���в���С����
	int Round(double a);//decimal��ʾ�������뱣����λ�ã�1-ʮλ��0-��λ��-1ʮ��λ�������Դ�����
	int Listamend(HoleInfoNode *q,int x,int y);//�˺���ʵ�ֵĹ��ܣ�����λ���ݽڵ��е�XY���갴�մ��������ֵ�����޸�
	int ProcessEightPin();//�������ܣ����ݵõ�����ʼ���ԭ����������һ���˽��εĿ�λ����
	int ProcessDualLine();//�������ܣ����������յ���������˫��ֱ����������겢�����λ��������
	int ProcessArray(int *p,double a,double b,ToolParaStruct * Toolpara);//�������ܣ� ���ݵõ���ӳ��int������õ���ӳ������λ�ò�����������


	bool AddLinkNote(double x,double y);//����ʱ����������ӽڵ�
	bool AddLinkNote1(double x,double y);//����ʱ����������ӽڵ�
	bool DeletePosition(int x,int y);//��ɸ�����ʼ����ɾ������ڵ�

	int XYPositonRevers(HoleInfoNode *note);//�������������ϵ�����XY�������XY����
	int XPositonMirro(HoleInfoNode *note);//�������������ϵ�����XY�������X�᾵��
	int YPositonMirro(HoleInfoNode *note);//�������������ϵ�����XY�������Y�᾵��
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
	int ProcessMirro(int ver,HoleInfoNode *firstnode);//���ݲ�ͬ����ϵ��ת��x��yλ��
	//int CopyHolePosNode(HoleInfoNode *inlist,HoleInfoNode *outlist);
	



};