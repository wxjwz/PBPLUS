#pragma once
#include "pbext.h"
#include <string>
#include <sstream>

#ifdef _UNICODE
//消除导出类包含C4251警告
template class  std::allocator<wchar_t>;
template class  std::basic_string<wchar_t>;  
//---------------
#define tstring std::wstring
#define tstringstream std::wstringstream

#else
//消除导出类包含C4251警告
template class  std::allocator<char>;
template class  std::basic_string<char>;  
//------------------------
#define tstring std::string
#define tstringstream std::stringstream
#endif


//判断字符是否相同（不区分大小写）
bool  caseInsCompare(const std::string& s1,const std::string& s2);
//PBCallInfo* PBXCreateCallInfo(IPB_Session* s,pbclass cls,LPCTSTR methodName,LPCTSTR signature);

//将指定的字符串替换成新的字符串，并返回替换后的字符串
tstring ReplaceString(tstring&  str,const tstring&   old_value,const tstring& new_value);
