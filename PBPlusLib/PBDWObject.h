/*
* PBDWObject.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbextobject.h"
BEGIN_PBPLUS_NASPACE
class PBDWObject :
	public PBExtObject
{
public:
	PBDWObject(IPB_Session* s);
	~PBDWObject(void);
public:
	DECLAREPBPROPERTY_GET(tstring,Type);
	DECLAREPBPROPERTY_GET(tstring,Name);
};
END_PBPLUS_NASPACE

