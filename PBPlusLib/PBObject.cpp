#include "StdAfx.h"
#include "PBObject.h"

BEGIN_PBPLUS_NASPACE
PBObject::PBObject(IPB_Session* sess):session(sess),obj(nullptr),cls(nullptr)
{
}


PBObject::~PBObject(void)
{
}

tstring PBObject::ClassName()
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("ClassName"),_T("S"));
}
bool PBObject::PostEvent(tstring e)
{
	return PBXInvokeFunc<bool,tstring>(session,this->cls,this->obj,_T("PostEvent"),_T("BS"),e);
}
bool PBObject::PostEvent(tstring e,long w,long l)
{
	return PBXInvokeFunc<bool,tstring,long,long>(session,this->cls,this->obj,_T("PostEvent"),_T("BSLL"),e,w,l);
}
bool PBObject::PostEvent(tstring e,long w,tstring l)
{
	return PBXInvokeFunc<bool,tstring,long,tstring>(session,this->cls,this->obj,_T("PostEvent"),_T("BSLS"),e,w,l);
}
SHORT PBObject::TriggerEvent(tstring e)
{
	return PBXInvokeFunc<SHORT,tstring>(session,this->cls,this->obj,_T("TriggerEvent"),_T("IS"),e);
}
SHORT PBObject::TriggerEvent(tstring e,long w,long l)
{
	return PBXInvokeFunc<SHORT,tstring,long,long>(session,this->cls,this->obj,_T("TriggerEvent"),_T("ISLL"),e,w,l);
}
SHORT PBObject::TriggerEvent(tstring e,long w,tstring l)
{
	return PBXInvokeFunc<SHORT,tstring,long,tstring>(session,this->cls,this->obj,_T("TriggerEvent"),_T("ISLS"),e,w,l);
}
END_PBPLUS_NASPACE