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