#include "StdAfx.h"
#include "PBWindowObject.h"
#include "PBSystem.h"
BEGIN_PBPLUS_NASPACE
PBWindowObject::PBWindowObject(IPB_Session* s)
	:PBGraphicObject(s)
{
}


PBWindowObject::~PBWindowObject(void)
{
}
//ÊôÐÔ£¨ÎÞ£©
//º¯Êý
SHORT PBWindowObject::Move(SHORT x,SHORT y)
{
	return PBXInvokeFunc<SHORT,SHORT,SHORT>(session,this->cls,this->obj,_T("Move"),_T("III"),x,y);
}
SHORT PBWindowObject::Resize(SHORT w,SHORT h)
{
	SHORT pbwidth = PBSystem::PixelsToUnits(session,w,XPixelsToUnits);
	SHORT pbheight = PBSystem::PixelsToUnits(session,h,YPixelsToUnits);
	return PBXInvokeFunc<SHORT,SHORT,SHORT>(session,this->cls,this->obj,_T("Resize"),_T("III"),pbwidth,pbheight);
}

END_PBPLUS_NASPACE