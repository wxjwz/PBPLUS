#pragma once

#include "PBConstants.h"
#include "PBUtil.h"
#include "PBPropertyFunc.h"
#include "PBFuncTemplate.h"
BEGIN_PBPLUS_NASPACE
class PBObject
{
//public:
//	pbclass cSys;//系统函数的class
public:
	pbobject obj;
	pbclass cls;
public:
	IPB_Session* session;
public:
	PBObject(IPB_Session* sess);
	virtual ~PBObject(void);
//属性
public:
	//classdefinition 未实现

//函数
public:
	tstring ClassName(void);
	//getcontextservice 未实现
	//getparent 未实现
	bool PostEvent(tstring e);
	bool PostEvent(tstring e,long w,long l);
	bool PostEvent(tstring e,long w,tstring l);
	//trigevent枚举类型具体值还未知，暂时无实现

	SHORT TriggerEvent(tstring e);
	SHORT TriggerEvent(tstring e,long w,long l);
	SHORT TriggerEvent(tstring e,long w,tstring l);
	//trigevent枚举类型具体值还未知，暂时无实现

	//typeof ( ) 未实现
};

END_PBPLUS_NASPACE