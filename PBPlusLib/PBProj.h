#pragma once
#include "PBPlusLib.h"
BEGIN_PBPLUS_NASPACE
class CPBProj
{
private:
	IPB_Session* session;
	IPB_VM* pbvm;
	HINSTANCE hinst;
	//pbclass container;//容器：容纳PowerBuilder的可视对象
	//pbobject containerObj;
public:	
	//PBSystem* system;
	PBWindow* win;
	PBDataWindow *dw;
	PBTransAction *trans;
public:
	CPBProj(tstring& dir);
	~CPBProj(void);
	operator HINSTANCE()
	{
		return hinst;
	}
	//Session
	IPB_Session* Session()
	{
		return session;
	}
	HWND CreateDataWindow(tstring& dataobject,int width,int height);
	void CreateTrans();
	void ResizeDataWindow(int width,int height);
	HWND GetCanvas();
	void AcceptText();
	void ShowCanvas(bool show);
};
END_PBPLUS_NASPACE