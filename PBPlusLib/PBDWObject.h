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

