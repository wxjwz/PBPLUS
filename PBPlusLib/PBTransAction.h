/*
* PBTransAction.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbnonvisualobject.h"
BEGIN_PBPLUS_NASPACE
class PBTransAction :
	public PBNonVisualObject
{
public:
	PBTransAction(IPB_Session* s);
	~PBTransAction(void);
	virtual void CreateSelfInstance();
#pragma region ∂‘”¶ Ù–‘
public:
	DECLAREPBPROPERTY(bool,AutoCommit)
	DECLAREPBPROPERTY(long,SQLCode)
	DECLAREPBPROPERTY(long,SQLDBCode)
	DECLAREPBPROPERTY(long,SQLNRows)
	DECLAREPBPROPERTY(tstring,Database)
	DECLAREPBPROPERTY(tstring,DBMS)
	DECLAREPBPROPERTY(tstring,DBParm)
	DECLAREPBPROPERTY(tstring,DBPass)
	DECLAREPBPROPERTY(tstring,Lock)
	DECLAREPBPROPERTY(tstring,LogID)
	DECLAREPBPROPERTY(tstring,LogPass)
	DECLAREPBPROPERTY(tstring,ServerName)
	DECLAREPBPROPERTY(tstring,SQLErrText)
	DECLAREPBPROPERTY(tstring,SQLReturnData)
	DECLAREPBPROPERTY(tstring,UserID)
#pragma endregion
	
public:
	bool Connect();
	bool DisConnect();
	long DBHandle(void);
	tstring SyntaxFromSQL ( tstring sqlselect, tstring presentation,tstring err );
//private:
//	bool ExeDBFunc(LPCTSTR funcName,LPCTSTR signature);
};

END_PBPLUS_NASPACE