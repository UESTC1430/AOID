// MessageQueue.h: interface for the CMessageQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MESSAGEQUEUE_H_       //如果没有定义这个宏  
#define _MESSAGEQUEUE_H_       //定义这个宏  

enum MSGID{HOMESTR,DataInMastProg,DataOutMastProg,DRILL,DATAINATP,DATAOUTATP,BOUNDARY,ClearMastProg,ModefyMastProg,CONNECT,QIC,};

int MessageDisplay();
int MessageProcess(int id);

#endif // 

