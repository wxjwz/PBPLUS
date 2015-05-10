#include "StdAfx.h"
#include "PBDWObject.h"

BEGIN_PBPLUS_NASPACE
PBDWObject::PBDWObject(IPB_Session* s)
	:PBExtObject(s)
{
}


PBDWObject::~PBDWObject(void)
{
}

tstring PBDWObject::GetType()
{
	/*pbboolean   isNull;
	pbfieldID fid = session-> GetFieldID(cls, _T("type"));
	session->GetStringField(obj,fid,isNull);*/
	PBCallInfo ci;
	PBXExcuteFunc<pbobject>(session,PBUserDefineFuctions,_T("nwxj230606001dwot"),_T("SCdwobject."),this->obj,ci);
	LPCTSTR str = session->GetString(ci.returnValue->GetString());
	//LPCTSTR str = session->GetString(session->GetStringField(obj,fid,isNull));
	tstring val;
	val.assign(str);
	session->ReleaseString(str);
	session->FreeCallInfo(&ci);
	return val;
}
tstring PBDWObject::GetName()
{
	PBCallInfo ci;
	PBXExcuteFunc<pbobject>(session,PBUserDefineFuctions,_T("nwxj230606001dwon"),_T("SCdwobject."),this->obj,ci);
	LPCTSTR str = session->GetString(ci.returnValue->GetString());
	tstring val;
	val.assign(str);
	session->ReleaseString(str);
	session->FreeCallInfo(&ci);
	return val;
}
END_PBPLUS_NASPACE