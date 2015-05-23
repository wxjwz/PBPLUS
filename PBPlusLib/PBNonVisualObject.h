/*
* PBNonVisualObject.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbobject.h"
#include "PBSystem.h"
BEGIN_PBPLUS_NASPACE
class PBNonVisualObject :
	public PBObject
{
public:
	PBNonVisualObject(IPB_Session* s);
	~PBNonVisualObject(void);
	virtual void CreateSelfInstance(){};
};
END_PBPLUS_NASPACE
