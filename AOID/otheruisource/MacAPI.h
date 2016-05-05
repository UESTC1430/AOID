#ifndef MAC_API_DLL_H
#define MAC_API_DLL_H

#ifdef MACAPI_EXPORTS
#define _MACAPI extern "C" __declspec(dllexport)
#else
#define _MACAPI extern "C" __declspec(dllimport)
#endif

//variables
#ifndef ELMO_MAC_PUBLIC_VAR_DEF
#define ELMO_MAC_PUBLIC_VAR_DEF

//multi-axes controller communication handle
//define device connection instance 
typedef DWORD COMMUNICATION_HANDLE;

//motion object type
typedef DWORD MOTION_OBJECT_TYPE;
#define	MOT_NONE			0x00
#define	MOT_NODE			0x01
#define	MOT_IO				0x02
#define	MOT_AXIS			0x04
#define	MOT_VECTOR			0x08
#define	MOT_GROUP			0x10
#define	MOT_3DVECTOR		0x20
#define	MOT_STATIC			0x30
#define MOT_EIP_DEV			0x40
#define MOT_EIP_ASSEM		0x50
#define MOT_EIP_ADAPTERTAG	0x60

#define TYPE_INT			0x00
#define TYPE_FLOAT			0x01

//COM initialization parameter
//When COM is initialized, you choose whether to initialize it
//as apartment-threaded or multi-threaded. This designates how
//incoming calls to any object created by that thread are handled,
//that is, the object's concurrency.
#define COM_INIT_DISABLE		0xFFFFFFFF
#define COM_INIT_SINGLETHREADED	0x2
#define COM_INIT_MULTITHREADED	0x0

//motion object data
typedef struct _MOTION_OBJECT
{
	BYTE				btBusID;	//CAN Bus ID for object
	BYTE				btNodeID;	//CAN Node ID for object
	TCHAR				szName[32];	//Motion object name
	MOTION_OBJECT_TYPE	moType;		//Motion object type
}	MOTION_OBJECT;

//On-close-connection case user's callback prototype
typedef void (*MAC_ONCLOSE_CALLBACK)(LPCTSTR);

//On-user-message callback prototype
typedef void (*MAC_ONUSER_MESSAGE)(DWORD, DWORD, DWORD, DWORD);

#endif//ELMO_MAC_PUBLIC_VAR_DEF

//This function enables the user to initialize MAC API Library
//
//Input parameters:
//DWORD dwComInitialize  - Initialize COM Mechanism Parameter:
//						   determines the concurrency model used for
//						   incoming calls to objects created by this thread.
//						   This parameter can be one of the following:
//								COM_INIT_DISABLE        - disable inner COM initialization,
//								COM_INIT_SINGLETHREADED - single-threaded model,
//								COM_INIT_MULTITHREADED  - multi-threaded model.
//BOOL  bEventInitialize - Initialize MAC Event Mechanism
//
//Return value:
//int - initialization status:
//			0 - OK;
//			1 - The API library is already initialized;
//			2 - The COM library is already initialized on this thread;
//			3 - A previous COM initialization specified a different apartment model for this thread;
//			4 - The COM library initialization failed;
//			5 - The MAC Events mechanism initialization failed;
//
//Sample:
//int nOk = MACInitialize( COM_INIT_SINGLETHREADED, FALSE );
//
_MACAPI int MACInitialize( DWORD dwComInitialize, BOOL bEventInitialize );

//This function enables the user to uninitialize MAC API Library
//
//Sample:
//MAC_Uninitialize();
//
_MACAPI void MACUninitialize();

//This function enables the user to get last error 
//
//Input parameters:
//WORD   wErrorSize - Size of string for error receiving.
//
//Output parameter:
//LPTSTR szError - Last error message.
//
//Return value:
//int - Error value:
//		 >= 0 - OK,	
//		 <  0 - the string for reception of the error is too small,
//			    value is the necessary size of a string (with a minus).
//
//Sample:
//int retVal = MACGetLastError( szErrorCom, 1024 );
//
_MACAPI int MACGetLastError( LPTSTR szError, WORD wErrorSize );

//This function enables the user to initiate TCP/IP communication with the
//multi-axes controller.
//
//Input parameters:
//LPCTSTR cszIP     - IP Address of controller
//DWORD	  dwTimeout - Max time for communication establishment
//WORD    wPort     - Communication port
//
//Return value:
//COMMUNICATION_HANDLE - Multi-axes controller communication handle,
//						 if connection failed - NULL.
//
//Sample:
//COMMUNICATION_HANDLE hCon = MACCreateTCPConnection( _T("10.10.10.112"), 5000, 23 );
//
_MACAPI COMMUNICATION_HANDLE MACCreateTCPConnection( LPCTSTR cszIP,
													 DWORD   dwTimeout/*=5000*/,
													 WORD    wPort/*=23*/ );

//This function enables the user to close communication
//
//Input parameter:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//
//
//Return value:
//int - Close connection status:
//			0 - OK;
//			1 - The API library is not initialized;
//			2 - Zero Communication handle;
//			3 - Bad Communication handle;
//
//Sample:
//if( !MACCloseConnection( hCon ) ) return FALSE;
//
_MACAPI int MACCloseConnection( COMMUNICATION_HANDLE hCommunication );

//This function enables the user to send commands to and receive responses
//from the connected multi-axes controller.
//
//Input parameters:
//COMMUNICATION_HANDLE	hCommunication - Multi-axes controller communication handle.
//LPCTSTR				cszCmd		   - Input string to be sent to controller.
//										 This is an Elmo command or expression.
//WORD                  wOutSize       - Size of string for response receiving.
//DWORD					dwTimeout      - The maximum wait time for receiving
//										 a response from the drive, in milliseconds.
//
//Output parameter:
//LPTSTR                szOut          - String for response receiving.
//
//Return value:
//int - Error value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Send command failed;
//		 < 0 - the string for reception of the answer is too small,
//			   value is the necessary size of a string (with a minus).
//
//Sample:
//retVal = MACSendCommand( hCon, _T("axis1.px=0"), szOut, 256, 1000 );
//
_MACAPI int	MACSendCommand( COMMUNICATION_HANDLE hCommunication,
							LPCTSTR              cszCmd,
							LPTSTR               szOut,
							WORD                 wOutSize /*=1024*/, 
							DWORD                dwTimeout/*=1000*/ );

//This function enables the user to find multi-axes controllers
//
//Return value:
//int - number of controllers, 
//		 if < 0 - error code:
//		 -1 - The API library is not initialized;
//		 -2 - Unable to create interface CLSID_MaestroLocator;
//		 -3 - The MAC Locator failed;
//		 -4 - The MAC Locator: unable to get device IP address;
//		 -5 - The MAC Locator: unable to get device name;
//
//Sample:
//int number = MACLocateDevices();
//
_MACAPI int MACLocateDevices();

//This function enables the user to get multi-axes controller parameters
//
//Input parameters:
//UINT	 uNum - Device number in this search results
//
//Output parameters:
//LPTSTR szIP    - IP address of controller (string with length 16 bytes minimum).
//LPTSTR szName  - Name of controller (string with length 32 bytes minimum).
//
//Return value:
//int - command status: if 0 - OK,
//						else - error code:
//						1 - The API library is not initialized;
//						2 - The device is not found;
//
//Sample:
//int retVal = MACGetDevice( 0, szIP, szName );
//
_MACAPI int MACGetDevice( UINT uNum, LPTSTR szIP, LPTSTR szName );

//This function enables the user to get multi-axes controller IP address by name
//
//Input parameter:
//LPCTSTR cszName - Name of controller (string with length 32 bytes minimum).
//
//Output parameter:
//LPTSTR szIP     - IP address of controller (string with length 16 bytes minimum).
//
//Return value:
//int - command status: if 0 - OK,
//						else - error code:
//						1 - The API library is not initialized;
//						2 - The device is not found;
//
//Sample:
//int retVal = MACGetIpByName( _T("MAC_1"), szIP );
//
_MACAPI int MACGetIpByName( LPCTSTR cszName, LPTSTR szIP );

//This function enables the user to check multi-axes controller IP address
//
//Input parameter:
//LPCTSTR cszHost - Host name or IP Address of controller.
//
//Output parameter:
//DWORD* pdwIP    - IP address of controller (NULL, if is Host not found).
//
//Return value:
//int - command status: if 0 - OK,
//						else - error code:
//						1 - The API library is not initialized;
//						2 - Invalid input parameter: zero pointer;
//						3 - Unable to create interface CLSID_MaestroLocator;
//						4 - The MAC Locator failed;
//						5 - The device is not found;
//
//Sample:
//int retVal = MACIsDevicePresent( _T("10.10.10.52"), &dwIP );
//
_MACAPI int MACIsDevicePresent( LPCTSTR cszHost, DWORD* pdwIP );

//This function enables the user to start motion objects search
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//MOTION_OBJECT_TYPE   moType		  - motion object type mask for current search
//										NULL - all motion objects
//
//Return value:
//int - number of objects, 
//		if < 0 - error code:
//		-1 - The API library is not initialized;
//		-2 - Zero Communication handle;
//		-3 - Bad Communication handle;
//		-4 - Unable to create interface ITNElmoPublic;
//		-5 - Send command failed;
//		-6 - Command 'list' failed;
//
//Sample:
//MOTION_OBJECT_TYPE moMask = MOT_AXIS|MOT_VECTOR;
//int                nObjs  = MACLocateObjects( hCom, dwMask );
//
_MACAPI int MACLocateObjects( COMMUNICATION_HANDLE hCommunication,
					          MOTION_OBJECT_TYPE   moType );

//This function enables the user to get motion object parameters
//
//Input parameters:
//UINT	         uNum - Object number in this search results
//
//Output parameters:
//MOTION_OBJECT* pObj - Pointer to motion object data structure
//
//Return value:
//int - Command status: if 0 - OK,
//						else - error code:
//						1 - The API library is not initialized;
//						2 - Invalid input parameter;
//						3 - The device is not found;
//
//Sample:
//int retVal = MACGetObject( 0, &moData );
//
_MACAPI int MACGetObject( UINT uNum, MOTION_OBJECT* pObj );

//This function enables the user to download trajectory to multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszLocalPath   - Path to trajectory file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Download Trajectory failed;
//
//Sample:
//int retVal = MACDownloadTrajectory( hCom, szPath );
//
_MACAPI int MACDownloadTrajectory( COMMUNICATION_HANDLE hCommunication, LPCTSTR cszLocalPath );

//This function enables the user to remove trajectory from multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszName        - Trajectory name, if * - remove all.
//
//Return value:
//int - Error value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Remove Trajectory failed;
//
//Sample:
//int retVal = MACRemoveTrajectory( hCom, _T("MyTrj") );
//
_MACAPI int MACRemoveTrajectory( COMMUNICATION_HANDLE hCommunication, LPCTSTR cszName );

//This function enables the user to download program to multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszLocalPath   - Path to program file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Download Program failed;
//
//Sample:
//int retVal = MACDownloadProgram( hCom, szPath );
//
_MACAPI int MACDownloadProgram( COMMUNICATION_HANDLE hCommunication, LPCTSTR cszLocalPath );

//This function enables the user to remove program from multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszName        - Program name, if * - remove all.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Remove Program failed;
//
//Sample:
//int retVal = MACRemoveProgram( hCom, _T("*") );
//
_MACAPI int MACRemoveProgram( COMMUNICATION_HANDLE hCommunication, LPCTSTR cszName );

//This function enables the user to define new resources and workspace information
//for multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication  - Multi-axes controller communication handle.
//LPCTSTR              cszMrsLocalPath - Path to resources file on desktop computer.
//LPCTSTR              cszMwdLocalPath - Path to workspace information file on desktop computer.
//BOOL	               bRestart        - Restart controller with new resources.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Download Workspace information failed;
//				6 - Download Resources failed;
//				7 - Restart failed;
//
//Sample:
//int retVal = MACDownloadResourcesEx( hCom, szMrsPath, szMwdPath, FALSE );
//
_MACAPI int MACDownloadResourcesEx( COMMUNICATION_HANDLE hCommunication,
									LPCTSTR              cszMrsLocalPath,
									LPCTSTR              cszMwdLocalPath,
									BOOL                 bRestart );

//This function enables the user to define new resources for multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszLocalPath   - Path to resources file on desktop computer.
//BOOL	               bRestart       - Restart controller with new resources.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Download Resources failed;
//
//Sample:
//int retVal = MACDownloadResources( hCom, szPath, FALSE );
//
_MACAPI int MACDownloadResources( COMMUNICATION_HANDLE hCommunication,
								  LPCTSTR              cszLocalPath,
								  BOOL                 bRestart );

//This function enables the user to upload log file from multi-axes controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszLocalPath   - Path to log file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Upload Log failed;
//
//Sample:
//int retVal = MACUploadLog( hCom, szPath );
//
_MACAPI int MACUploadLog( COMMUNICATION_HANDLE hCommunication, LPCTSTR cszLocalPath );

//This function enables the user to initialize MAC Event mechanism
//
//Return value:
//int - initialization status:
//			0 - OK;
//			1 - The ATL Module initialization failed;
//			2 - Unable to create event listener thread;
//
//Sample:
//int nOk = MACInitEvents();
//
_MACAPI int MACInitEvents();

//This function enables the user to close MAC Event mechanism
//
//Sample:
//MACDeinitEvents();
//
_MACAPI void MACDeinitEvents();

//This function enables the user to advise/anadvise
//on-close-connection case user's callback
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//MAC_ONCLOSE_CALLBACK ptrCB          - close-connection case user's callback.
//
//Return value:
//int - initialization status:
//			0 - OK;
//			1 - The API library is not initialized;
//			2 - Zero Communication handle;
//			3 - Bad Communication handle;
//			4 - Unable to create interface ITNElmoPublic;
//			5 - TNElmo server: Dispatch event failed;
//
//Sample:
//int nOk = MACRegCloseCallback( hComm, MyCloseCallback );
//
_MACAPI int MACRegCloseCallback( COMMUNICATION_HANDLE hCommunication,
								 MAC_ONCLOSE_CALLBACK ptrCB);

//This function enables the user to advise/anadvise
//on-user-interrupt case user's callback
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//MAC_ONUSER_INTERRUPT ptrCB          - user-interrupt case user's callback.
//
//Return value:
//int - initialization status:
//			0 - OK;
//			1 - The API library is not initialized;
//			2 - Zero Communication handle;
//			3 - Bad Communication handle;
//			4 - Unable to create interface ITNElmoPublic;
//			5 - TNElmo server: Dispatch event failed;
//			6 - The Event Mechanism was not initialized
//
//Sample:
//int nRes = MACRegMessageCallback( hComm, MyMsgCallback );
//
_MACAPI int MACRegMessageCallback( COMMUNICATION_HANDLE hCommunication,
								   MAC_ONUSER_MESSAGE   ptrCB);

//This function enables the user to download firmware to SimpleIQ controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszObjects     - Motion objects.
//										Format:
//											"name1 name2 ... nameN" - object names with space delimiter;
//											"*" - change firmware for all Elmo nodes;
//LPCTSTR              cszLocalPath   - Path to firmware file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Firmware file downloading failed;
//				6 - Unable to start firmware update process;
//
//Sample:
//int retVal = MACDownloadSimpleIQFirmware( hCom, _T("a1 a2 a3"), _T("d:\\SimplIQ 2.02.05.06 28Feb2005Eng.abs") );
//
_MACAPI int MACDownloadSimpleIQFirmware( COMMUNICATION_HANDLE hCommunication,
										 LPCTSTR              cszObjects,
										 LPCTSTR              cszLocalPath );

//This function enables the user to download program to Simple-IQ controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszObjName	  - Motion object name.
//LPCTSTR              cszLocalPath   - Path to SimpleIQ program image file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Unable to open image file;
//				6 - Invalid image file;
//				7 - Invalid image file table;
//				8 - Unable to read image file;
//				9 - Unable to clear program for SimpleIQ device;
//			   10 - Unable to send image file;
//			   11 - Unable to send image file checksum;
//
//Sample:
//int retVal = MACDownloadSimpleIQProgram( hCom, _T("a1"), _T("c:\\SimpleIQ\\prj1.img") );
//
_MACAPI int MACDownloadSimpleIQProgram( COMMUNICATION_HANDLE hCommunication,
										LPCTSTR              cszObjName,
										LPCTSTR              cszLocalPath );

//This function enables the user to download application parameters to Simple-IQ controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszObjName     - Motion object name.
//LPCTSTR              cszLocalPath   - Path to SimpleIQ application file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Unable to open SimpleIQ application file;
//				6 - Application file is empty;
//				7 - Unable to read application file;
//				8 - Unable to find version;
//				9 - Unable to read version;
//			   10 - Unable to find parameters;
//			   11 - Unable to read parameters;
//			   12 - Unable to verify versioning capability;
//			   13 - Incompatible versions;
//			   14 - Difference versions: need to call Application Editor;
//			   15 - Unable to load application;
//			  2xx - Download SimpleIQ device parameters failed:
//			  201 -		Unable to get TOC;
//			  202 -		Unable to clear parameters - step 1 failed;
//			  203 -		Unable to clear parameters - step 2 failed;
//			  204 -		Unable to clear parameters - step 3 failed;
//			  205 -		Unable to clear parameters - step 4 failed;
//			  206 -		Unable to download header of parameters;
//			  207 -		Unable to download portion of parameters;
//
//Sample:
//int retVal = MACDownloadSimpleIQParams( hCom, _T("a1"), _T("c:\\SimpleIQ\\app1.dat") );
//
_MACAPI int MACDownloadSimpleIQParams( COMMUNICATION_HANDLE hCommunication,
									   LPCTSTR              cszObjName,
									   LPCTSTR              cszLocalPath );

//This function enables the user to download application - program and parameters
//(from new Compositor application file format only) to Simple-IQ controller
//
//Input parameters:
//COMMUNICATION_HANDLE hCommunication - Multi-axes controller communication handle.
//LPCTSTR              cszObjName     - Motion object name.
//LPCTSTR              cszLocalPath   - Path to SimpleIQ application file on desktop computer.
//
//Return value:
//		 0 - OK,
//		 > 0 - communication error codes:	
//				1 - The API library is not initialized;
//				2 - Zero Communication handle;
//				3 - Bad Communication handle;
//				4 - Unable to create interface ITNElmoPublic;
//				5 - Unable to open SimpleIQ application file;
//				6 - Application file is empty;
//				7 - Unable to read application file;
//				8 - Unable to find version;
//				9 - Unable to read version;
//			   10 - Unable to find parameters;
//			   11 - Unable to read parameters;
//			   12 - Unable to find program image;
//			   13 - Unable to read program image;
//			   14 - Unable to read program checksum;
//			   15 - Invalid program checksum;
//			   16 - Unable to verify versioning capability;
//			   17 - Incompatible versions;
//			   18 - Difference versions: need to call Application Editor;
//			   19 - Unable to load application;
//			  1xx - Download SimpleIQ program failed:
//			  109 -		Unable to clear program for SimpleIQ device;
//			  110 -		Unable to send image file;
//			  111 -		Unable to send image file checksum;
//			  2xx -	Download SimpleIQ device parameters failed:
//			  201 -		Unable to get TOC;
//			  202 -		Unable to clear parameters - step 1 failed;
//			  203 -		Unable to clear parameters - step 2 failed;
//			  204 -		Unable to clear parameters - step 3 failed;
//			  205 -		Unable to clear parameters - step 4 failed;
//			  206 -		Unable to download header of parameters;
//			  207 -		Unable to download portion of parameters;
//
//Sample:
//int retVal = MACDownloadSimpleIQApp( hCom, _T("a1"), _T("c:\\SimpleIQ\\app1.dat") );
//
_MACAPI int MACDownloadSimpleIQApp( COMMUNICATION_HANDLE hCommunication,
									LPCTSTR              cszObjName,
									LPCTSTR              cszLocalPath );

#endif//MAC_API_DLL_H
