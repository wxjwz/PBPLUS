#include "StdAfx.h"
#include "PBGraphicObject.h"

BEGIN_PBPLUS_NASPACE
PBGraphicObject::PBGraphicObject(IPB_Session* s)
	:PBObject(s)
{
}

PBGraphicObject::~PBGraphicObject(void)
{
}

//Visible
bool PBGraphicObject::GetVisible()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("visible"),value);
	return value;
}
void PBGraphicObject::SetVisible(bool visible)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("visible"),visible);
}

//Tag
tstring PBGraphicObject::GetTag()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("tag"),value);
	return value;
}
void PBGraphicObject::SetTag(tstring tag)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("tag"),tag);
}

//º¯Êý
SHORT PBGraphicObject::Hide()
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Hide"),_T("I"));
}
SHORT PBGraphicObject::Show()
{
	return PBXInvokeFunc<SHORT>(session,this->cls,this->obj,_T("Show"),_T("I"));
}

END_PBPLUS_NASPACE