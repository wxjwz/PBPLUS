#include "StdAfx.h"
#include "PBWindow.h"
BEGIN_PBPLUS_NASPACE
PBWindow* PBWindow::pThis=nullptr;

PBWindow::PBWindow(IPB_Session* s)
	:PBGraphicObject(s)
{
}

PBWindow::~PBWindow(void)
{
}

//XHandle:句柄
HWND PBWindow::GetXHandle()
{
	return handle;
}
void PBWindow::SetXHandle(HWND hwnd)
{
	handle = hwnd;
}

//-----------------------
SHORT PBWindow::CloseUserObject(PBDragObject& dragObject)
{
	pbobject dr=nullptr;
	PBSystem::SetObject(session,(PBObject&)dragObject,dr);
	return PBXInvokeFunc<SHORT,pbobject>(session,this->cls,this->obj,_T("CloseUserObject"),_T("ICdragobject."),dr);
}
int PBWindow::OpenUserObject(LPCTSTR objName,PBDragObject& dragObject, SHORT xPos,SHORT yPos)
{
	pbobject dw=nullptr;
	int refParm = 1;//第1个参数不传入参数
	PBCallInfo ci;
	PBXExcuteFunc<pbobject,tstring,SHORT,SHORT>(session,this->cls,this->obj,_T("openuserobject"),_T("IRCdragobject.SII"),dw,objName,xPos,yPos,ci,refParm);
	PBXGetDataFromCallInfo<pbobject>(session,&ci,(pbint)0,dw);
	PBSystem::SetObject(session,(PBObject&)dragObject,dw);
	return 1;
}
int PBWindow::CreateDataWindowObject(PBDataWindow& dw, SHORT xPos,SHORT yPos)
{
	return OpenUserObject(_T("nwxj230506011ab87"),(PBDragObject&)dw,xPos,yPos);
}
SHORT PBWindow::Resize(SHORT w,SHORT h)
{
	SHORT pbwidth = PBSystem::PixelsToUnits(session,w,XPixelsToUnits);
	SHORT pbheight = PBSystem::PixelsToUnits(session,h,YPixelsToUnits);
	return PBXInvokeFunc<SHORT,SHORT,SHORT>(session,this->cls,this->obj,_T("Resize"),_T("III"),pbwidth,pbheight);
}

END_PBPLUS_NASPACE