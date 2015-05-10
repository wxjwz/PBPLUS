#pragma once
#include "pbobject.h"
BEGIN_PBPLUS_NASPACE
class PBGraphicObject :
	public PBObject
{
public:
	PBGraphicObject(IPB_Session* s);
	~PBGraphicObject(void);
//ÊôÐÔ
public:
	DECLAREPBPROPERTY(bool,Visible)
	DECLAREPBPROPERTY(tstring,Tag)
//º¯Êý
public:
	SHORT Hide();
	SHORT Show();
};
END_PBPLUS_NASPACE
