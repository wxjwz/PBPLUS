// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#if _MSC_VER < 1600
#define nullptr  NULL
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息



// TODO: 在此处引用程序需要的其他头文件

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <atlbase.h>
#include <atlstr.h>
#include <atlwin.h>
//#include <ATLComTime.h>
#include <vector>
#include <sstream>
#include "pbext.h"


#define NAMESPACE namespace
#define APP_NAMSPACE WXJ_LIB

#ifdef USINGUSERNAMESPACE
#define BEGIN_PBPLUS_NASPACE \
	NAMESPACE APP_NAMSPACE{

#define END_PBPLUS_NASPACE\
	}

#define USING_APP_NAMESPACE\
	using namespace APP_NAMSPACE;
#else
#define BEGIN_PBPLUS_NASPACE 
#define END_PBPLUS_NASPACE
#define USING_APP_NAMESPACE
#endif

#define IFDEFSTATEMENT #ifdef
#define UNDEFSTATEMENT #undef
#define ENDIFSTATEMENT #endif
#define DEFINESTATEMENT #define
#define ELSESTATEMENT #else
#define LF _T("\n")
//禁用宏展开
#define DISABLE_PPEPROCESSOR(name) \
IFDEFSTATEMENT name \
	\
UNDEFSTATEMENT name \
ENDIFSTATEMENT

//回复宏展开
#define RESTORE_PPEPROCESSOR(name) \
IFDEFSTATEMENT UNICODE \
	DEFINESTATEMENT name  name##W \
ELSESTATEMENT \
	DEFINESTATEMENT name  name##A \
ENDIFSTATEMENT 

//#include "PBPlusLib.h"
//#define BEGIN_PBPLUS_NASPACE \
//	namespace PBPlus \
//	{
//
//#define END_PBPLUS_NASPACE }