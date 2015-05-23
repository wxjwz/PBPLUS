/*
* PBWindowObject.h
*
*  Created on: 2015.05.23
*      Author: wxj
*		EMAIL: wxj_wz@qq.com
*/
#pragma once
#include "pbgraphicobject.h"
BEGIN_PBPLUS_NASPACE
class PBWindowObject :
	public PBGraphicObject
{
public:
	PBWindowObject(IPB_Session* s);
	~PBWindowObject(void);
//ÊôÐÔ(ÎÞ)
//º¯Êý
public:
	SHORT Move(SHORT x,SHORT y);
	SHORT Resize(SHORT w,SHORT h);
};
END_PBPLUS_NASPACE
