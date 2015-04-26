///////////////////////////////////////////////////////////
//  Chest.h
//  Implementation of the Class Chest
//  Created on:      25-Apr-2015 08:59:01
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_33673CDA_892D_441a_A3C2_B9B0FDCBD561__INCLUDED_)
#define EA_33673CDA_892D_441a_A3C2_B9B0FDCBD561__INCLUDED_

#pragma once
#include "Part.h"

class Chest : public Part
{

public:
	virtual ~Chest();
	Chest(PartEnums::PartType type);

};
#endif // !defined(EA_33673CDA_892D_441a_A3C2_B9B0FDCBD561__INCLUDED_)