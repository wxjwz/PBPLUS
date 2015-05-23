/*
* PBFuncTemplate.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbext.h"
#include "PBObject.h"
#include "PBUtil.h"
//BEGIN_PBPLUS_NASPACE
//==============================================================================================================================
//以下是函数处理
USING_APP_NAMESPACE
#pragma region 函数执行完返回的模板

template <typename T>
struct PBXstrFunc
{
	friend static T PBXGetFuncReturnValue(T* t,IPB_Session* s,PBCallInfo* ci)
	{
		s->FreeCallInfo(ci);
		return ;
	}
};
template<>struct PBXstrFunc<void>
{
	/*friend static void PBXGetFuncReturnValue(int* a,IPB_Session* s,PBCallInfo* ci)
	{
		s->FreeCallInfo(ci);
		return ;
	}*/
	friend static void PBXGetFuncReturnValue(void* a,IPB_Session* s,PBCallInfo* ci)
	{
		s->FreeCallInfo(ci);
		return ;
	}
};
template<>struct PBXstrFunc<bool>
{
	friend static bool PBXGetFuncReturnValue(bool* t,IPB_Session* s, PBCallInfo* ci)
	{
		pbboolean rtn = ci->returnValue->GetBool();
		bool rVal= (rtn == 1)?true : false;
		s->FreeCallInfo(ci);
		return rVal;
	}
};
//pbint和SHORT相同
template<>struct PBXstrFunc<SHORT>
{
	friend static SHORT PBXGetFuncReturnValue(SHORT* t,IPB_Session* s, PBCallInfo* ci)
	{
		SHORT rtn = ci->returnValue->GetInt();
		s->FreeCallInfo(ci);
		return rtn;
	}
};
template<>struct PBXstrFunc<tstring>
{
	friend static tstring PBXGetFuncReturnValue(tstring* t,IPB_Session* s, PBCallInfo* ci)
	{
		pbstring rtn = ci->returnValue->GetString();
		LPCTSTR pStr = s->GetString(rtn);
		tstring sObj;
		sObj.assign(pStr);
		s->FreeCallInfo(ci);
		return sObj;
	}
};
template<>struct PBXstrFunc<long>
{
	friend static long PBXGetFuncReturnValue(long* t,IPB_Session* s, PBCallInfo* ci)
	{
		pblong rtn = ci->returnValue->GetLong();
		s->FreeCallInfo(ci);
		return (long)rtn;
	}
};
template<>struct PBXstrFunc<LONGLONG>
{
	friend static LONGLONG PBXGetFuncReturnValue(LONGLONG* t,IPB_Session* s, PBCallInfo* ci)
	{
		pblonglong rtn = ci->returnValue->GetLong();
		s->FreeCallInfo(ci);
		return (LONGLONG)rtn;
	}
};
template<>struct PBXstrFunc<HWND>
{
	friend static HWND PBXGetFuncReturnValue(HWND* t,IPB_Session* s, PBCallInfo* ci)
	{
		pblong rtn = ci->returnValue->GetLong();
		s->FreeCallInfo(ci);
		return (HWND)rtn;
	}
};

#pragma endregion

#pragma region 将值设置到函数参数中
template <typename T>
struct PBXstrSetToParm
{
	//将值赋值到PBCallInfo的参数中
	static friend void PBXFuncSetToParm(T t,PBCallInfo* ci,pbint order){}
	//将函数执行完后的值赋值给函数的参数
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,T& t,PBCallInfo* ci,pbint order){}
};
template<> struct PBXstrSetToParm<bool>
{
	static friend void PBXFuncSetToParm(bool t,PBCallInfo* ci,pbint order)
	{
		pbboolean val = (true==t)?1 : 0;
		ci->pArgs->GetAt(order)->SetBool(val);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,bool& t,PBCallInfo* ci,pbint order)
	{
		pbboolean val =ci->pArgs->GetAt(order)->GetBool();
		t =  (val == 1) ? true :false;
	}
};
template<> struct PBXstrSetToParm<SHORT>
{
	static friend void PBXFuncSetToParm(SHORT t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetInt(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,SHORT& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetInt();
	}
};
template<> struct PBXstrSetToParm<USHORT>
{
	static friend void PBXFuncSetToParm(USHORT t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetInt(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,USHORT& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetInt();
	}
};
template<> struct PBXstrSetToParm<tstring>
{
	static friend void PBXFuncSetToParm(tstring t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetString(t.c_str());
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,tstring& t,PBCallInfo* ci,pbint order)
	{
		t =s->GetString(ci->pArgs->GetAt(order)->GetString());
	}
};
template<> struct PBXstrSetToParm<long>
{
	static friend void PBXFuncSetToParm(pblong t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetLong(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,long& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetLong();
	}
};
template<> struct PBXstrSetToParm<ULONG>
{
	static friend void PBXFuncSetToParm(ULONG t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetLong(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,ULONG& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetLong();
	}
};
template<> struct PBXstrSetToParm<LONGLONG>
{
	static friend void PBXFuncSetToParm(LONGLONG t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetLongLong(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,LONGLONG& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetLongLong();
	}
};
template<> struct PBXstrSetToParm<ULONGLONG>
{
	static friend void PBXFuncSetToParm(ULONGLONG t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetLongLong(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,ULONGLONG& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetLongLong();
	}
};
template<> struct PBXstrSetToParm<pbobject>
{
	static friend void PBXFuncSetToParm(pbobject& t,PBCallInfo* ci,pbint order)
	{
		//ci->pArgs->GetAt(order);
		ci->pArgs->GetAt(order)->SetObject(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,pbobject& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetObject();
	}
};
template<> struct PBXstrSetToParm<pbblob>
{
	static friend void PBXFuncSetToParm(pbblob& t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetBlob(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,pbblob& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetBlob();
	}
};
template<> struct PBXstrSetToParm<pbstring>
{
	static friend void PBXFuncSetToParm(pbstring& t,PBCallInfo* ci,pbint order)
	{
		ci->pArgs->GetAt(order)->SetPBString(t);
	}
	static friend void PBXFuncSetToFuncParm(IPB_Session* s,pbstring& t,PBCallInfo* ci,pbint order)
	{
		t =ci->pArgs->GetAt(order)->GetString();
	}
};
#pragma endregion

//--------------------------------------------------------------
//函数参数初始化
bool PBXInvokeFuncInitParm(IPB_Session* s,pbclass cls,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,pbmethodID& mid,bool  publicOnly = true );
bool PBXInvokeFuncInitParm(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,pbclass& cls,PBCallInfo& ci,pbmethodID& mid,bool  publicOnly = true );
//--------------------------------------------------------------
//从执行完PB函数返回的数据
//1个参数
template <typename P1> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1)
{
	PBXFuncSetToFuncParm(s,p1,ci,order);
}
template <typename P1,typename P2> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order);
}
template <typename P1,typename P2,typename P3> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order);
}
template <typename P1,typename P2,typename P3,typename P4> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3,P4& p4)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order++);
	PBXFuncSetToFuncParm(s,p4,ci,order);
}
template <typename P1,typename P2,typename P3,typename P4,typename P5> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3,P4& p4,P5 &p5)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order++);
	PBXFuncSetToFuncParm(s,p4,ci,order++);
	PBXFuncSetToFuncParm(s,p5,ci,order);
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3,P4& p4,P5 &p5,P6 &p6)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order++);
	PBXFuncSetToFuncParm(s,p4,ci,order++);
	PBXFuncSetToFuncParm(s,p5,ci,order++);
	PBXFuncSetToFuncParm(s,p6,ci,order);
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3,P4& p4,P5 &p5,P6 &p6,P7 &p7)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order++);
	PBXFuncSetToFuncParm(s,p4,ci,order++);
	PBXFuncSetToFuncParm(s,p5,ci,order++);
	PBXFuncSetToFuncParm(s,p6,ci,order++);
	PBXFuncSetToFuncParm(s,p7,ci,order);
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8> 
void PBXGetDataFromCallInfo(IPB_Session* s,PBCallInfo* ci,pbint order,P1& p1,P2& p2,P3& p3,P4& p4,P5 &p5,P6 &p6,P7 &p7,P8 &p8)
{
	PBXFuncSetToFuncParm(s,p1,ci,order++);
	PBXFuncSetToFuncParm(s,p2,ci,order++);
	PBXFuncSetToFuncParm(s,p3,ci,order++);
	PBXFuncSetToFuncParm(s,p4,ci,order++);
	PBXFuncSetToFuncParm(s,p5,ci,order++);
	PBXFuncSetToFuncParm(s,p6,ci,order++);
	PBXFuncSetToFuncParm(s,p7,ci,order++);
	PBXFuncSetToFuncParm(s,p8,ci,order);
}
//END_PBPLUS_NASPACE
//--------------------------------------------------------------
//将值赋值到PBCallInfo,宏PBX_SETPARMVALUETOPBCALLINFO后的_数字表示有多少个参数
#define PBX_SETPARMVALUETOPBCALLINFO(order,p1,refParm,pos)\
		if(((refParm) & (pos))==0)\
			PBXFuncSetToParm((p1),&ci,order);

#define PBX_SETPARMVALUETOPBCALLINFO_1(order,p1,refParm,pos) \
	PBX_SETPARMVALUETOPBCALLINFO(order,p1,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_2(order,p1,p2,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_1(order - 1,p1,refParm,pos>>1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p2,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_3(order,p1,p2,p3,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_2(order - 1,p1,p2,refParm,pos >> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p3,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_4(order,p1,p2,p3,p4,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_3(order -  1,p1,p2,p3,refParm,pos>> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p4,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_5(order,p1,p2,p3,p4,p5,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_4(order - 1,p1,p2,p3,p4,refParm,pos >> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p5,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_6(order,p1,p2,p3,p4,p5,p6,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_5(order - 1,p1,p2,p3,p4,p5,refParm,pos >> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p6,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_7(order,p1,p2,p3,p4,p5,p6,p7,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_6(order - 1,p1,p2,p3,p4,p5,p6,refParm,pos >> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p7,refParm,pos)

#define PBX_SETPARMVALUETOPBCALLINFO_8(order,p1,p2,p3,p4,p5,p6,p7,p8,refParm,pos)\
	PBX_SETPARMVALUETOPBCALLINFO_7(order - 1,p1,p2,p3,p4,p5,p6,p7,refParm,pos >> 1)\
	PBX_SETPARMVALUETOPBCALLINFO(order,p8,refParm,pos)

//清理函数调用后的操作
#define PBX_GETFUNCRETURNVAL(R,r,s)\
	R* r=nullptr;\
	return PBXGetFuncReturnValue(r,s,&ci);
//-------------------------------------------------------------

//BEGIN_PBPLUS_NASPACE
//执行函数
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,bool  publicOnly =true);
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,PBCallInfo& ci,bool  publicOnly =true);

//1个参数
template <typename P1> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_1(0,p1,refParm,0x0001);
	//PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_1(0,p1,refParm,0x0001);
	//PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	s->InvokeClassFunction(cls,mid,&ci);
}

//2个参数
template <typename P1,typename P2> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_2(1,p1,p2,refParm,0x0002);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);*/
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_2(1,p1,p2,refParm,0x0002);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);*/
	s->InvokeClassFunction(cls,mid,&ci);
}
//3个参数
template <typename P1,typename P2,typename P3> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_3(2,p1,p2,p3,refParm,0x0004);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);*/
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_3(2,p1,p2,p3,refParm,0x0004);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);*/
	s->InvokeClassFunction(cls,mid,&ci);
}
//4个参数
template <typename P1,typename P2,typename P3,typename P4> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_4(3,p1,p2,p3,p4,refParm,0x0008);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);
	PBX_SETPARMVALUETOPBCALLINFO(3,p4,refParm,0x0004);*/
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3,typename P4> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_4(3,p1,p2,p3,p4,refParm,0x0008);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);
	PBX_SETPARMVALUETOPBCALLINFO(3,p4,refParm,0x0004);*/
	s->InvokeClassFunction(cls,mid,&ci);
}
//5个参数
template <typename P1,typename P2,typename P3,typename P4,typename P5> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_5(4,p1,p2,p3,p4,p5,refParm,0x0010);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);
	PBX_SETPARMVALUETOPBCALLINFO(3,p4,refParm,0x0004);
	PBX_SETPARMVALUETOPBCALLINFO(4,p5,refParm,0x0005);*/
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3,typename P4,typename P5> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_5(4,p1,p2,p3,p4,p5,refParm,0x0010);
	/*PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);
	PBX_SETPARMVALUETOPBCALLINFO(3,p4,refParm,0x0004);
	PBX_SETPARMVALUETOPBCALLINFO(4,p5,refParm,0x0005);*/
	s->InvokeClassFunction(cls,mid,&ci);
}

//6个参数
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_6(5,p1,p2,p3,p4,p5,p6,refParm,0x0020);
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_6(5,p1,p2,p3,p4,p5,p6,refParm,0x0020);
	s->InvokeClassFunction(cls,mid,&ci);
}
//7个参数
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_7(6,p1,p2,p3,p4,p5,p6,p7,refParm,0x0040);
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_7(6,p1,p2,p3,p4,p5,p6,p7,refParm,0x0040);
	s->InvokeClassFunction(cls,mid,&ci);
}
//8个参数
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8> 
void PBXExcuteFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_8(7,p1,p2,p3,p4,p5,p6,p7,p8,refParm,0x0080);
	s->InvokeObjectFunction(obj,mid,&ci);//执行函数
}
template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8> 
void PBXExcuteFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,PBCallInfo& ci,UINT refParm = 0,bool  publicOnly =true)
{
	pbclass cls;
	pbmethodID mid;
	PBXInvokeFuncInitParm(s,funcType,methodName,signature,cls,ci,mid,publicOnly);
	PBX_SETPARMVALUETOPBCALLINFO_8(7,p1,p2,p3,p4,p5,p6,p7,p8,refParm,0x0080);
	s->InvokeClassFunction(cls,mid,&ci);
}
//函数执行完整实现
//0个参数
template <typename R> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,bool  publicOnly =true)
{
	//pbmethodID mid;
	//PBCallInfo ci;
	//PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid);
	//s->InvokeObjectFunction(obj,mid,&ci);//执行函数
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,ci,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
	/*R* r=nullptr;
	return PBXGetFuncReturnValue(r,s,&ci);*/
}
 template <typename R> 
 R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,ci,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
 //1个参数
template <typename R,typename P1> 
 R PBXInvokeFunc(IPB_Session* s,pbclass& cls,pbobject& obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
  //1个参数(全局)
template <typename R,typename P1> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
  //2个参数
template <typename R,typename P1,typename P2> 
R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
//2个参数（全局）
template <typename R,typename P1,typename P2> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}

//3个参数
template <typename R,typename P1,typename P2,typename P3> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
 //3个参数(全局)
 template <typename R,typename P1,typename P2,typename P3> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}

//4个参数
template <typename R,typename P1,typename P2,typename P3,typename P4> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,p4,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
  //4个参数(全局)
 template <typename R,typename P1,typename P2,typename P3,typename P4> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,p4,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
//5个参数
template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,p4,p5,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
	///*pbmethodID mid=s->GetMethodID(cls,methodName,PBRT_FUNCTION,signature);
	//PBCallInfo ci;
	//s->InitCallInfo(cls,mid,&ci);*/
	//PBCallInfo ci;
	//pbmethodID mid;
	//PBXInvokeFuncInitParm(s,cls,methodName,signature,ci,mid);
	//pbint order=0;
	//PBX_SETPARMVALUETOPBCALLINFO(0,p1,refParm,0x0001);
	//PBX_SETPARMVALUETOPBCALLINFO(1,p2,refParm,0x0002);
	//PBX_SETPARMVALUETOPBCALLINFO(2,p3,refParm,0x0003);
	//PBX_SETPARMVALUETOPBCALLINFO(3,p4,refParm,0x0004);
	//PBX_SETPARMVALUETOPBCALLINFO(4,p5,refParm,0x0005);
	///*PBXFuncSetToParm(p1,&ci,order++);
	//PBXFuncSetToParm(p2,&ci,order++);
	//PBXFuncSetToParm(p3,&ci,order++);
	//PBXFuncSetToParm(p4,&ci,order++);
	//PBXFuncSetToParm(p5,&ci,order++);*/
	//s->InvokeObjectFunction(obj,mid,&ci);//执行函数
	//PBX_GETFUNCRETURNVAL(R,r,s);
	///*R *r=nullptr;
	//return PBXGetFuncReturnValue(r,s,&ci);*/
}
   //5个参数(全局)
 template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,p4,p5,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}

//6个参数
template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,p4,p5,p6,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
   //6个参数(全局)
 template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,p4,p5,p6,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
//7个参数
template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,p4,p5,p6,p7,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
   //7个参数(全局)
 template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,p4,p5,p6,p7,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
//8个参数
template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8> 
 R PBXInvokeFunc(IPB_Session* s,pbclass cls,pbobject obj,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,cls,obj,methodName,signature,p1,p2,p3,p4,p5,p6,p7,p8,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
   //8个参数(全局)
 template <typename R,typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8> 
R PBXInvokeFunc(IPB_Session* s,PBFunctionType funcType,LPCTSTR methodName,LPCTSTR signature,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,UINT refParm = 0,bool  publicOnly =true)
{
	PBCallInfo ci;
	PBXExcuteFunc(s,funcType,methodName,signature,p1,p2,p3,p4,p5,p6,p7,p8,ci,refParm,publicOnly);
	PBX_GETFUNCRETURNVAL(R,r,s);
}
//#pragma endregion

//////实现函数体
//#define IMPLEMENT_FUNC_BODY0(Class,Func,Signature,ReturnDataType)\
//	ReturnDataType Class##::##Func(void)\
//	{\
//	return PBXInvokeFunc<ReturnDataType>(session,this->cls,this->obj,_T(#Func),_T(#Signature));\
//	}
//
//#define IMPLEMENT_FUNC_BODY1(Class,Func,Signature,ReturnDataType,T1,V1)\
//	ReturnDataType Class##::##Func("#T1 # V1")\
//	{\
//	return PBXInvokeFunc<ReturnDataType,T1>(session,this->cls,this->obj,_T(#Func),_T(#Signature),V1);\
//	}
//
//#define IMPLEMENT_FUNC_BODY2(Class,Func,Signature,ReturnDataType,T1,V1,T2,V2)\
//	ReturnDataType Class##::##Func(T1  "#V1", T2 V2)\
//	{\
//	return PBXInvokeFunc<ReturnDataType,T1,T2>(session,this->cls,this->obj,_T(#Func),_T(#Signature),V1,V2);\
//	}
//

//END_PBPLUS_NASPACE