/*
* PBHost.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "PBPlusLib.h"
BEGIN_PBPLUS_NASPACE
class PBHost
{
public:
	PBHost(void);
	~PBHost(void);
	operator HINSTANCE()
	{
		return hinst;
	}
	IPB_Session* PBPointer()
	{
		return session;
	}
	BOOL EnablePrivilege(HANDLE hToken,LPCTSTR szPrivName);//提升权限
	bool GetCurrentProcessDirectory(TCHAR dir[]);
	void SetPBEnvitentPath(HINSTANCE hInstance);
	bool CreatePBHost(tstring& dir);//创建PB对象宿主
	//bool AddToLibraryList(tstring& libList);//添加PBL(PBD)
	//void GetLibraryList(tstring& list);
	DECLAREPBPROPERTY(tstring,LibraryList)
private:
	IPB_Session* session;
	IPB_VM* pbvm;
	HINSTANCE hinst;
	tstring pbdFile;
};
END_PBPLUS_NASPACE
