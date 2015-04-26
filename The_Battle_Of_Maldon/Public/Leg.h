///////////////////////////////////////////////////////////
//  Leg.h
//  Implementation of the Class Leg
//  Created on:      25-Apr-2015 08:58:45
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_CF516254_0860_480c_B773_D9174865082A__INCLUDED_)
#define EA_CF516254_0860_480c_B773_D9174865082A__INCLUDED_

#pragma once
#include "Part.h"

class Leg : public Part
{

public:
	virtual ~Leg();
	Leg(PartEnums::PartType type);

};
#endif // !defined(EA_CF516254_0860_480c_B773_D9174865082A__INCLUDED_)


