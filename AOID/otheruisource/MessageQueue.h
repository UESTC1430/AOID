// MessageQueue.h: interface for the CMessageQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MESSAGEQUEUE_H_       //���û�ж��������  
#define _MESSAGEQUEUE_H_       //���������  

enum MSGID{HOMESTR,DataInMastProg,DataOutMastProg,DRILL,DATAINATP,DATAOUTATP,BOUNDARY,ClearMastProg,ModefyMastProg,CONNECT,QIC,};

int MessageDisplay();
int MessageProcess(int id);

#endif // 

