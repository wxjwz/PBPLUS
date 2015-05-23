/*
* PBSystem.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbext.h"
//#include "PBObject.h"
#include "PBWindow.h"
#include "PBConstants.h"
#include "PBUtil.h"
BEGIN_PBPLUS_NASPACE
class PBObject;
class PBWindow;

//对应PowerBuilder的System and Environment Functions
class PBSystem 
{
public:
	PBSystem(IPB_Session* s);
	~PBSystem(void);
	static SHORT AddToLibraryList(IPB_Session* session ,tstring filelist);
	static SHORT SetLibraryList(IPB_Session* session ,tstring filelist);
	static tstring GetLibraryList(IPB_Session* session);
	static SHORT Open(IPB_Session* session,LPCTSTR windowtype,PBWindow *win);
	static SHORT CreateWindowObject(IPB_Session* session,PBWindow *win);
	//判断操作系统是否为64位
	static bool IsWow64(); 
	//获取枚举的值
	static long GetEnumValue(IPB_Session* s,LPCTSTR enumType,LPCTSTR enumName);
	static int CreateObject(IPB_Session* s,pbclass& cls,pbobject& obj,LPCTSTR funcName,LPCTSTR signature);
	static bool GetInnerFuncObject(IPB_Session* session,LPCTSTR funcName);
	inline static bool ExeInnerFunc(IPB_Session* session,LPCTSTR funcName,LPCTSTR signature);
	static HWND Handle(IPB_Session* session,pbobject& obj);
	static bool SetObject(IPB_Session* session,PBObject& pobj,pbobject objInstance);
	static long Send(IPB_Session* session,long hWnd,ULONG mess,long wParm,long lParm);
	static SHORT PixelsToUnits(IPB_Session* session,SHORT pixels, PBConvertType type );
	static SHORT UnitsToPixels(IPB_Session* session,SHORT units, PBConvertType type );
	static long Sizeof(IPB_Session* session,pbobject& obj);
};

END_PBPLUS_NASPACE