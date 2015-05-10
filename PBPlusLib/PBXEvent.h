#pragma once
template<typename DstClassType>
class XEventT
{
	DstClassType *pThis;
	typedef void (DstClassType:: *Class_MemberFuncType)();
	Class_MemberFuncType Class_MemberFunc;
  public:
	  XEventT(DstClassType *This,Class_MemberFuncType ClassMemberFunction)
	  {
		  this->pThis=This;
		  this->Class_MemberFunc=ClassMemberFunction;
	  }
	  void Fire()
	  { 
		  //验证两个指针有效性
		  (pThis->*Class_MemberFunc)();
	  }
};
