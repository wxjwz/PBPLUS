#pragma once
#include "pbobject.h"
#include <string>
BEGIN_PBPLUS_NASPACE
class PBDWBase :
	public PBObject
{
public:
	PBDWBase(IPB_Session* sess);
	~PBDWBase(void);
};
END_PBPLUS_NASPACE
