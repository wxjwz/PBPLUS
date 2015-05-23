/*
* PBExtObject.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbnonvisualobject.h"
BEGIN_PBPLUS_NASPACE
class PBExtObject :
	public PBNonVisualObject
{
public:
	PBExtObject(IPB_Session* s);
	~PBExtObject(void);

};

END_PBPLUS_NASPACE