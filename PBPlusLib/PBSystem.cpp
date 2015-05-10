#include "StdAfx.h"
#include "PBSystem.h"
BEGIN_PBPLUS_NASPACE
PBSystem::PBSystem(IPB_Session* s)
{
}

PBSystem::~PBSystem(void)
{
}
SHORT PBSystem::AddToLibraryList(IPB_Session* session,tstring filelist)
{
	return PBXInvokeFunc<SHORT>(session,PBSystemFunctions,_T("AddToLibraryList"),_T("IS"),filelist);
}
SHORT PBSystem::SetLibraryList(IPB_Session* session ,tstring filelist)
{
	return PBXInvokeFunc<SHORT>(session,PBSystemFunctions,_T("SetLibraryList"),_T("IS"),filelist);
}
tstring PBSystem::GetLibraryList(IPB_Session* session)
{
	return PBXInvokeFunc<tstring>(session,PBSystemFunctions,_T("GetLibraryList"),_T("S"));
}
SHORT PBSystem::Open(IPB_Session* session,LPCTSTR windowtype,PBWindow *win)
{
	if(win == nullptr)
		win = new PBWindow(session);
	int refParm = 1;//第1个参数不传入参数
	PBCallInfo ci;
	PBXExcuteFunc<pbobject,tstring>(session,PBSystemFunctions,_T("open"),_T("IRCwindow.S"),win->obj,windowtype,ci,refParm);
	win->obj = ci.pArgs->GetAt(0)->GetObject();
	win->cls=session->GetClass(win->obj);
	SHORT rVal = ci.returnValue->GetInt();
	return rVal;
}
SHORT PBSystem::CreateWindowObject(IPB_Session* session,PBWindow *win)
{
	return Open(session,_T("nwxj230506011bc87"),win);
}

bool PBSystem::IsWow64() 
{ 
    //typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL); 
    //LPFN_ISWOW64PROCESS fnIsWow64Process; 
    BOOL bIsWow64 = FALSE; 
 /*   fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle(_T("kernel32")),"IsWow64Process"); 
    if (NULL != fnIsWow64Process) 
    { 
        fnIsWow64Process(GetCurrentProcess(),&bIsWow64);
    } */
	::IsWow64Process(GetCurrentProcess(),&bIsWow64);
    return bIsWow64==TRUE; 
} 
long PBSystem::GetEnumValue(IPB_Session* s,LPCTSTR enumType,LPCTSTR enumName)
{
	pblong enumvalue = s->GetEnumItemValue ( enumType, enumName ) ;
	if ( enumvalue < 0 )
	{
		return PBX_E_INVALID_ARGUMENT ;
	}
	else
	{
		return (long)enumvalue;
	}
}
//创建对象，调用 return pbobject f_createXXX()
int PBSystem::CreateObject(IPB_Session* s,pbclass& cls,pbobject& obj,LPCTSTR funcName,LPCTSTR signature)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,PBUserDefineFuctions,funcName,signature,ci);
	obj = ci.returnValue->GetObject();
	cls=s->GetClass(obj);
	return 1;
}
//返回内部全局函数的class
bool GetInnerFuncObject(IPB_Session* session,LPCTSTR funcName,pbclass& FuncCls)
{
	if(session == NULL) return false;
	pbgroup group = session->FindGroup(funcName,pbgroup_function);
	if (group == NULL) return false;
	FuncCls = session->FindClass(group,funcName);
	if (FuncCls == NULL) return false;
	return true;
}
//执行预先定义的，主要是一些不好在C++实现，而PB很容易实现的函数，如connect,把这些包含在PB的全局函数来执行
inline bool PBSystem::ExeInnerFunc(IPB_Session* session,LPCTSTR funcName,LPCTSTR signature)
{
	return PBXInvokeFunc<bool>(session,PBUserDefineFuctions,funcName,signature);
}
HWND PBSystem::Handle(IPB_Session* session,pbobject& obj)
{
	return PBXInvokeFunc<HWND,pbobject>(session,PBSystemFunctions,_T("handle"),_T("LCpowerobject."),obj);
}
bool PBSystem::SetObject(IPB_Session* session,PBObject& pobj,pbobject objInstance)
{
	pbclass clsInstance;
	clsInstance = session->GetClass(objInstance);
	pobj.obj = objInstance;
	pobj.cls = clsInstance;
	return true;
}
long PBSystem::Send(IPB_Session* session,long hWnd,ULONG mess,long wParm,long lParm)
{
	return PBXInvokeFunc<long,long,ULONG,long,long>(session,PBSystemFunctions,_T("send"),_T("LLNLL"),hWnd,mess,wParm,lParm);
}
SHORT PBSystem::PixelsToUnits(IPB_Session* session,SHORT pixels, PBConvertType type )
{
	//对于枚举的注意先强制转换，不然会失败
	return PBXInvokeFunc<SHORT,SHORT,long>(session,PBSystemFunctions,_T("PixelsToUnits"),_T("IICconverttype."),pixels,(long)type);
}
SHORT PBSystem::UnitsToPixels(IPB_Session* session,SHORT units, PBConvertType type )
{
	return PBXInvokeFunc<SHORT,SHORT,long>(session,PBSystemFunctions,_T("UnitsToPixels"),_T("IICconverttype."),units,(long)type);
}
long PBSystem::Sizeof(IPB_Session* session,pbobject& obj)
{
	return PBXInvokeFunc<long,pbobject>(session,PBUserDefineFuctions,_T("nwxj230606001sizeof"),_T("LXCpowerobject."),obj);
}
END_PBPLUS_NASPACE