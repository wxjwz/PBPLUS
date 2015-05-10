#pragma once
//#include "pbext.h"
#include "PBSystem.h"
//#include "PBObject.h"
//#include "PBDragObject.h"
#include "PBGraphicObject.h"
//#include "PBDataWindow.h"
BEGIN_PBPLUS_NASPACE
class PBDragObject;
class PBDataWindow;
class PBWindow :public PBGraphicObject
{
private:
	HWND handle;
	static PBWindow* pThis;
	static LRESULT CALLBACK CustMsgProc1(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam);
public:
	//以下是自己扩展的
	//句柄
	DECLAREPBPROPERTY(HWND,XHandle)
public:
	PBWindow(IPB_Session* s);
	~PBWindow(void);
	SHORT CloseUserObject(PBDragObject& dragObject);
	int OpenUserObject(LPCTSTR objName,PBDragObject& dragObject, SHORT xPos=0,SHORT yPos =0);
	int CreateDataWindowObject(PBDataWindow& dw, SHORT xPos=0,SHORT yPos =0);
	SHORT Resize(SHORT w,SHORT h);
};
END_PBPLUS_NASPACE
