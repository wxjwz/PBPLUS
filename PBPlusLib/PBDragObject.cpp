#include "StdAfx.h"
#include "PBDragObject.h"
#include "PBSystem.h"
BEGIN_PBPLUS_NASPACE
PBDragObject::PBDragObject(IPB_Session* s)
	:PBWindowObject(s)
{
}


PBDragObject::~PBDragObject(void)
{
	//UnhookWindowsHookEx(hhook);
}
WNDPROC OldDragMsgProc;
LRESULT CALLBACK CustDragMsgProc(HWND hwnd,UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_RBUTTONDOWN:
		::MessageBox(NULL,_T("WM_RBUTTONDOWN!"),_T("drag"),MB_OK);
		break;
	case WM_LBUTTONDOWN:
		::MessageBox(NULL,_T("click!"),_T("drag"),MB_OK);
		break;
	}
	//调用控件原来的消息处理函数
	return CallWindowProc(OldDragMsgProc,hwnd,message,wParam,lParam);
	//return OldMsgProc(hwnd,message,wParam,lParam);
	//return NULL;
}
//LRESULT WINAPI CallMyWndProc(int nCode, WPARAM wParam, LPARAM lParam) 
//{
//	if (nCode < 0) // 
//          return CallNextHookEx(hhook, nCode, wParam, lParam); 
//	switch (nCode) 
//    {
//		case HC_ACTION:
//			CWPSTRUCT* p = (CWPSTRUCT*)lParam;
//			switch(p->message)
//			{
//			case WM_PARENTNOTIFY:
//				if(p->wParam == WM_LBUTTONDOWN )
//				{
//					/*HDC hdc=::GetDC(p->hwnd);
//					::TextOut(hdc,5,20,_T("单击\0"),2);
//					::ReleaseDC(p->hwnd,hdc);
//					::MessageBeep(0xFFFFFFFF);*/
//					::MessageBox(NULL,_T("pbdw125"),_T("clicked"),MB_OK);
//					return 1;
//				}
//			}
//			return CallNextHookEx(hhook, nCode, wParam, lParam);
//	}
//	return CallNextHookEx(hhook, nCode, wParam, lParam);
//}
//AccessibleRole
PBAccessibleRole PBDragObject::GetAccessibleRole()
{
	PBAccessibleRole style;
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("AccessibleRole"),value);
	style = (PBAccessibleRole)value;
	return style;
}
void PBDragObject::SetAccessibleRole(PBAccessibleRole style)
{
	SHORT value = style;
	PBSetPropertyValue(session,this->cls,this->obj,_T("AccessibleRole"),value);
}

//BringToTop
bool PBDragObject::GetBringToTop()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("bringtotop"),value);
	return value;
}
void PBDragObject::SetBringToTop(bool toTop)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("bringtotop"),toTop);
}

//DragAuto
bool PBDragObject::GetDragAuto()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("dragauto"),value);
	return value;
}
void PBDragObject::SetDragAuto(bool dragAuto)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("dragauto"),dragAuto);
}

//Height
SHORT PBDragObject::GetHeight()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("height"),value);
	return value;
}
void PBDragObject::SetHeight(SHORT h)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("height"),h);
}

//TabOrder
SHORT PBDragObject::GetTabOrder()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("taborder"),value);
	return value;
}
void PBDragObject::SetTabOrder(SHORT order)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("taborder"),order);
}

//Transparency
SHORT PBDragObject::GetTransparency()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("transparency"),value);
	return value;
}
void PBDragObject::SetTransparency(SHORT transParency)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("transparency"),transParency);
}

//Width
SHORT PBDragObject::GetWidth()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("width"),value);
	return value;
}
void PBDragObject::SetWidth(SHORT w)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("width"),w);
}

//X
SHORT PBDragObject::GetX()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("x"),value);
	return value;
}
void PBDragObject::SetX(SHORT x)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("x"),x);
}

//Y
SHORT PBDragObject::GetY()
{
	SHORT value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("y"),value);
	return value;
}
void PBDragObject::SetY(SHORT y)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("y"),y);
}

//AccessibleDescription
tstring PBDragObject::GetAccessibleDescription()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("accessibledescription"),value);
	return value;
}
void PBDragObject::SetAccessibleDescription(tstring v)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("accessibledescription"),v);
}

//AccessibleName
tstring PBDragObject::GetAccessibleName()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("accessiblename"),value);
	return value;
}
void PBDragObject::SetAccessibleName(tstring v)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("accessiblename"),v);
}

//Dragicon
tstring PBDragObject::GetDragIcon()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("dragicon"),value);
	return value;
}
void PBDragObject::SetDragIcon(tstring v)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("dragicon"),v);
}
////XHandle:句柄
//HWND PBDragObject::GetXHandle()
//{
//	return handle;
//}
//void PBDragObject::SetXHandle(HWND hwnd)
//{
//	handle = hwnd;
//}
//函数
SHORT PBDragObject::PointerX(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("PointerX"),_T("I"));
}
SHORT PBDragObject::PointerY(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("PointerY"),_T("I"));
}
SHORT PBDragObject::Print(long j,SHORT x, SHORT y)
{
	return PBXInvokeFunc<SHORT,long,SHORT,SHORT>(session,this->cls,this->obj,_T("Print"),_T("ILII"),j,x,y);
}
SHORT PBDragObject::Print(long j,SHORT x, SHORT y,SHORT w,SHORT h)
{
	return PBXInvokeFunc<SHORT,long,SHORT,SHORT,SHORT,SHORT>(session,this->cls,this->obj,_T("Print"),_T("ILIIII"),j,x,y,w,h);
}
SHORT PBDragObject::SetActionCode(long c)
{
	return PBXInvokeFunc<SHORT,long>(session,this->cls,this->obj,_T("SetActionCode"),_T("IL"),c);
}
SHORT PBDragObject::Setfocus(void)
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Setfocus"),_T("I"));
}
SHORT PBDragObject::SetRedraw(bool f)
{
	return PBXInvokeFunc<SHORT,bool>(session,this->cls,this->obj,_T("SetRedraw"),_T("IB"),f);
}

bool PBDragObject::SetWxjOwnerProc()
{
	////事件直接用triggerevent处理
	///*OldMsgProc = (WNDPROC) SetWindowLongPtr (handle, GWLP_WNDPROC,(LONG_PTR)CustMsgProc);
	//SetWindowLongPtr(handle,GWLP_USERDATA,reinterpret_cast<LONG_PTR>(OldMsgProc));*/

	////hhook = SetWindowsHookEx(WH_CALLWNDPROC,CallMyWndProc,(HINSTANCE)NULL, GetCurrentThreadId()); 
	//HWND hWnd = PBSystem::Handle(session,this->obj);
	//OldDragMsgProc= (WNDPROC) SetWindowLongPtr (hWnd, GWLP_WNDPROC,(LONG_PTR)CustDragMsgProc);
	return true;
}

END_PBPLUS_NASPACE