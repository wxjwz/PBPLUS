#pragma once
#include "pbobject.h"
BEGIN_PBPLUS_NASPACE
class PBApplication :
	public PBObject
{
public:
	PBApplication(IPB_Session* s);
	~PBApplication(void);
};

END_PBPLUS_NASPACE