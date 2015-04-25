///////////////////////////////////////////////////////////
//  Arm.h
//  Implementation of the Class Arm
//  Created on:      25-Apr-2015 08:59:08
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_B5B722B4_B784_45e5_BA41_2CA3CA68F1A5__INCLUDED_)
#define EA_B5B722B4_B784_45e5_BA41_2CA3CA68F1A5__INCLUDED_

#include "Part.h"

class Arm : public Part
{

public:
	virtual ~Arm();
	Arm(PartEnums::PartType type);

};
#endif // !defined(EA_B5B722B4_B784_45e5_BA41_2CA3CA68F1A5__INCLUDED_)