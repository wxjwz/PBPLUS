#include "StdAfx.h"
#include "PBFuncTemplate.h"
//BEGIN_PBPLUS_NASPACE
//初始化函数调用参数
bool PBXInvokeFuncInitParm(IPB_Session* s,pbclass cls,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,pbmethodID& mid,bool  publicOnly  )
{
	pbboolean pubOnly = (publicOnly == true) ?1 : 0;
	mid=s->GetMethodID(cls,methodName,PBRT_FUNCTION,signature,pubOnly);
	s->InitCallInfo(cls,mid,&ci);
	return true;
}
bool PBXInvokeFuncInitParm(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,pbclass& cls,PBCallInfo& ci,pbmethodID& mid,bool  publicOnly  )
{
	if(funcType == PBSystemFunctions)
		cls=s->FindClass(s->GetSystemGroup(),_T("systemfunctions"));
	else
		cls=s->FindClass(s->FindGroup(methodName,pbgroup_function),methodName);
	pbboolean pubOnly = (publicOnly == true) ?1 : 0;
	mid=s->GetMethodID(cls,methodName,PBRT_FUNCTION,signature,pubOnly);
	s->InitCallInfo(cls,mid,&ci);
	return true;
}
//执行到执行PB函数
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,bool  publicOnly)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,bool  publicOnly)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	s->InvokeClassFunction(cls,mid,&ci);
}

//END_PBPLUS_NASPACE