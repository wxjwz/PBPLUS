#pragma once
//#include "pbext.h"
#include "PBWindowObject.h"
//#include "PBSystem.h"
////记录原来处理函数
//	static WNDPROC OldMsgProc;
//	//新消息处理函数
//	static LRESULT CALLBACK CustMsgProc(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam);
//	static HHOOK hhook;
BEGIN_PBPLUS_NASPACE
class PBDragObject:public PBWindowObject
{

public:
	PBDragObject(IPB_Session* s);
	~PBDragObject(void);
private:
	HWND handle;
	//WNDPROC OldMsgProc1;
	
//属性
public:
	DECLAREPBPROPERTY(PBAccessibleRole,AccessibleRole)
	DECLAREPBPROPERTY(bool,BringToTop)
	DECLAREPBPROPERTY(bool,DragAuto)
	DECLAREPBPROPERTY(SHORT,Height)
	DECLAREPBPROPERTY(SHORT,TabOrder)
	//透明度0-不透明，100完全透明
	DECLAREPBPROPERTY(SHORT,Transparency)
	DECLAREPBPROPERTY(SHORT,Width)
	DECLAREPBPROPERTY(SHORT,X)
	DECLAREPBPROPERTY(SHORT,Y)
	DECLAREPBPROPERTY(tstring,AccessibleDescription)
	DECLAREPBPROPERTY(tstring,AccessibleName)
	DECLAREPBPROPERTY(tstring,DragIcon)
	////以下是自己扩展的
	////句柄
	//DECLAREPBPROPERTY(HWND,XHandle)
//函数
public:
	//Drag dragmodes未知，暂时未实现
	SHORT PointerX(void);
	SHORT PointerY(void);
	SHORT Print(long j,SHORT x, SHORT y); 
	SHORT Print(long j,SHORT x, SHORT y,SHORT w,SHORT h); 
	SHORT SetActionCode(long c);
	SHORT Setfocus(void);
	//setposition ( setpostype p )  returns integer 未实现
	//setposition ( setpostype p, dragobject a )  returns integer
	SHORT SetRedraw(bool f);
	//以下是自己扩展
	virtual bool SetWxjOwnerProc();
};
END_PBPLUS_NASPACE