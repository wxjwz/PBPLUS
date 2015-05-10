#include "StdAfx.h"
#include "PBUtil.h"
inline bool caseInsCharCompareN(char a,char b)
{
	return (toupper(a)==toupper(b));
}
//比较字符串是否相等
 bool  caseInsCompare(const std::string& s1,const std::string& s2)
{
	return (s1.size()==s2.size() && 
		std::equal(s1.begin(),s1.end(),s2.begin(),caseInsCharCompareN));
}

//PBCallInfo* PBXCreateCallInfo(IPB_Session* s,pbclass cls,LPCTSTR methodName,LPCTSTR signature)
//{
//	pbmethodID mid=s->GetMethodID(cls,methodName,PBRT_FUNCTION,signature);
//	PBCallInfo *ci;
//	s->InitCallInfo(cls,mid,ci);
//	return ci;
//}

 tstring  ReplaceString(tstring&  str,const tstring&   old_value,const tstring& new_value)     
{   
	tstring newStr(str);
	for(tstring::size_type   pos(0);   pos!=tstring::npos;   pos+=new_value.length())   
	{     
		if((pos=newStr.find(old_value,pos))!=tstring::npos   )     
			newStr.replace(pos,old_value.length(),new_value);     
		else   
			break;     
	}     
	return   newStr;     
}