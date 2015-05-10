#include "StdAfx.h"
#include "PBTransAction.h"

BEGIN_PBPLUS_NASPACE
PBTransAction::PBTransAction(IPB_Session* s)
	:PBNonVisualObject(s)
{

}


PBTransAction::~PBTransAction(void)
{
}
void PBTransAction::CreateSelfInstance()
{
	PBSystem::CreateObject(session,cls,obj,_T("nwxj230606001ct"),_T("Cnwxj230506012ab87."));
}
//属性实现
//AutoCommit
bool PBTransAction::GetAutoCommit()
{
	bool value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("AutoCommit"),value);
	return value;
}
void PBTransAction::SetAutoCommit(bool autoCommit)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("AutoCommit"),autoCommit);
}
//SQLCode
long PBTransAction::GetSQLCode()
{
	long value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("SQLCode"),value);
	return value;
}
void PBTransAction::SetSQLCode(long sqlCode)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("SQLCode"),sqlCode);
}
//SQLDBCode
long PBTransAction::GetSQLDBCode()
{
	long value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("SQLDBCode"),value);
	return value;
}
void PBTransAction::SetSQLDBCode(long sqlDBCode)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("SQLDBCode"),sqlDBCode);
}
//SQLNRows
long PBTransAction::GetSQLNRows()
{
	long value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("SQLNRows"),value);
	return value;
}
void PBTransAction::SetSQLNRows(long sqlLNRows)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("SQLNRows"),sqlLNRows);
}
//Database
tstring PBTransAction::GetDatabase()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("Database"),value);
	return value;
}
void PBTransAction::SetDatabase(tstring database)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("Database"),database);
}
//DBMS
tstring PBTransAction::GetDBMS()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("DBMS"),value);
	return value;
}
void PBTransAction::SetDBMS(tstring dbms)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("DBMS"),dbms);
}
//DBParm
tstring PBTransAction::GetDBParm()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("DBParm"),value);
	return value;
}
void PBTransAction::SetDBParm(tstring dbParm)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("DBParm"),dbParm);
}
//DBPass
tstring PBTransAction::GetDBPass()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("DBPass"),value);
	return value;
}
void PBTransAction::SetDBPass(tstring dbPass)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("DBPass"),dbPass);
}
//Lock
tstring PBTransAction::GetLock()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("Lock"),value);
	return value;
}
void PBTransAction::SetLock(tstring lock)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("Lock"),lock);
}
//LogID
tstring PBTransAction::GetLogID()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("LogID"),value);
	return value;
}
void PBTransAction::SetLogID(tstring logID)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("LogID"),logID);
}
//LogPass
tstring PBTransAction::GetLogPass()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("LogPass"),value);
	return value;
}
void PBTransAction::SetLogPass(tstring logPass)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("LogPass"),logPass);
}
//ServerName
tstring PBTransAction::GetServerName()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("ServerName"),value);
	return value;
}
void PBTransAction::SetServerName(tstring serverName)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("ServerName"),serverName);
}
//SQLErrText
tstring PBTransAction::GetSQLErrText()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("SQLErrText"),value);
	return value;
}
void PBTransAction::SetSQLErrText(tstring sqlErrText)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("SQLErrText"),sqlErrText);
}
//SQLReturnData
tstring PBTransAction::GetSQLReturnData()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("SQLReturnData"),value);
	return value;
}
void PBTransAction::SetSQLReturnData(tstring sqlReturnData)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("SQLReturnData"),sqlReturnData);
}
//UserID
tstring PBTransAction::GetUserID()
{
	tstring value;
	PBGetPropertyValue(session,this->cls,this->obj,_T("UserID"),value);
	return value;
}
void PBTransAction::SetUserID(tstring userID)
{
	PBSetPropertyValue(session,this->cls,this->obj,_T("UserID"),userID);
}
//属性实现完毕---------------<<<


//bool PBTransAction::ExeDBFunc(LPCTSTR funcName,LPCTSTR signature)
//{
//		bool rtn = true;
//	if(session == NULL) return false;
//	pbgroup group = session->FindGroup(funcName,pbgroup_function);
//	if (group == NULL) return false;
//	pbclass FuncCls = session->FindClass(group,funcName);
//	if (FuncCls == NULL) return false;
//	PBCallInfo ci;
//	pbmethodID mid = session->GetMethodID(FuncCls, funcName,PBRT_FUNCTION,signature);
//	session->InitCallInfo(FuncCls, mid, &ci);
//	try
//	{
//		ci.pArgs->GetAt(0)->SetObject(obj);
//		session->InvokeClassFunction(FuncCls, mid, &ci);
//		if (session->HasExceptionThrown())
//		{
//			session->ClearException();
//			rtn = false;
//		}
//		else
//		{
//			rtn=true;
//		}
//	}
//	catch (...)
//	{
//		return false;
//	}
//	session->FreeCallInfo(&ci);
//	return rtn;
//}

bool PBTransAction::Connect()
{
	return PBXInvokeFunc<bool>(session,PBUserDefineFuctions,_T("nwxj230606001cn"),_T("BRCnwxj230506012ab87."),this->obj);
}
bool PBTransAction::DisConnect()
{
	return PBXInvokeFunc<bool>(session,PBUserDefineFuctions,_T("nwxj230606001dcn"),_T("BRCnwxj230506012ab87."),this->obj);
}
long PBTransAction::DBHandle(void)
{
	return PBXInvokeFunc<long>(session,this->cls,this->obj,_T("DBHandle"),_T("L"));
}
tstring PBTransAction::SyntaxFromSQL ( tstring sqlselect, tstring presentation,tstring err )
{
	return PBXInvokeFunc<tstring>(session,this->cls,this->obj,_T("SyntaxFromSQL"),_T("SSSRS"),sqlselect,presentation,err);
}
END_PBPLUS_NASPACE