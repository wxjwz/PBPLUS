#include "stdafx.h"
#include "PBHost.h"
#include "Psapi.h"  
#pragma comment (lib,"Psapi.lib") 

BEGIN_PBPLUS_NASPACE
typedef PBXEXPORT PBXRESULT (*P_PB_GetVM)(IPB_VM** vm);
PBHost::PBHost(void)
	:session(nullptr),pbvm(nullptr),hinst(NULL),pbdFile(_T("libjmsvcrt.dll"))
{
}
PBHost::~PBHost(void)
{
	if(session != nullptr)
	{
		session->Release();
		session = nullptr;
	}
	if(hinst != NULL)
		FreeLibrary(hinst);
}
BOOL PBHost::EnablePrivilege(HANDLE hToken,LPCTSTR szPrivName)
{
	TOKEN_PRIVILEGES tkp;  
	LookupPrivilegeValue( NULL,szPrivName,&tkp.Privileges[0].Luid );//修改进程权限  
	tkp.PrivilegeCount=1;  
	tkp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;  
	AdjustTokenPrivileges( hToken,FALSE,&tkp,sizeof tkp,NULL,NULL );//通知系统修改进程权限  
	return( (GetLastError()==ERROR_SUCCESS) ); 
}
bool PBHost::GetCurrentProcessDirectory(TCHAR dir[])
{
	HANDLE  hToken;
	//提升程序权限  
	OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&hToken);  
	EnablePrivilege(hToken,SE_DEBUG_NAME);  
	HANDLE h_Process=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,GetCurrentProcessId());  
	if (!h_Process)  
		return false;
	::GetModuleFileNameEx(h_Process,NULL,dir,MAX_PATH+1); 
	//_splitpath(
	return true;
}
void PBHost::SetPBEnvitentPath(HINSTANCE hInstance)
{
		TCHAR szPath[MAX_PATH];
		TCHAR  buffer[MAX_PATH]=TEXT(""); 
		TCHAR** lppPart={NULL};
		tstring aa;
		tstring dir;
		int iLength;
		if( GetModuleFileName( hInstance, szPath, MAX_PATH ) )
		{
		aa.assign(szPath);
		}
		dir = aa.substr(0,aa.rfind(_T("\\")));
		
		LPCTSTR pathName=_T("Path");
		iLength = GetEnvironmentVariable (pathName, NULL, 0) ; 
		TCHAR* vBuffer=new TCHAR[iLength+1];
		GetEnvironmentVariable (pathName,vBuffer,iLength+1);
		tstring tPath(vBuffer);
		tPath.append(_T(";"));
		tPath.append(dir);
		SetEnvironmentVariable(pathName,tPath.c_str());
		//::MessageBox(NULL,dir.c_str(),_T("aaaa"),MB_OK);
}
bool PBHost::CreatePBHost(tstring& t)
{
	
	tstring dir;
	if(t.length()>0)
		dir.assign(t + _T("\\"));
	else
		dir.assign(_T(""));
	
	hinst = LoadLibrary((dir+ _T("PBVM125.DLL")).c_str());
	if(hinst == NULL)
	{
		return false;
	}
	P_PB_GetVM getvm = (P_PB_GetVM)GetProcAddress(hinst,"PB_GetVM");
	if (getvm == NULL)
	{
		return false;
	}
	getvm(&pbvm);
	if (pbvm == nullptr)
	{
		return false;
	}
	tstring tmpList =(dir + pbdFile).c_str();
	LPCTSTR liblist[]={tmpList.c_str()};
	PBXRESULT pbxC;

	pbxC = pbvm->CreateSession(_T("libjmsvcrt"), liblist, 1,&session);

	if ( pbxC != PBX_OK )
	{
		return false;
	}
	return true;
}
void PBHost::SetLibraryList(tstring libList)
{
	tstring list(_T(""));
	if(libList.length()>0)
	{
		list = pbdFile+_T(",");
		list = list + libList;
	}
	else
		list = pbdFile;
	//::MessageBox(NULL,list.c_str(),_T("aa"),MB_OK);
	SHORT val=PBSystem::SetLibraryList(session,list);
	/*if(val == 1)
		;
	else
		::MessageBox(NULL,list.c_str(),_T(""),MB_OK);*/
	//return val == 1 ? true :false;
}
tstring PBHost::GetLibraryList()
{
	tstring list= PBSystem::GetLibraryList(session);
	tstring old(pbdFile);
	if(list.find(_T(",")) != list.npos)
		old = old +_T(",");
	tstring pblList = ReplaceString(list,old,_T(""));
	return pblList;
}
END_PBPLUS_NASPACE