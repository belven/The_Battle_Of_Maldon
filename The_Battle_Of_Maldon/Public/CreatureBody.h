///////////////////////////////////////////////////////////
//  CreatureBody.h
//  Implementation of the Class CreatureBody
//  Created on:      25-Apr-2015 14:05:42
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_E7C4D473_5050_4baa_A249_C964C6D5B7A8__INCLUDED_)
#define EA_E7C4D473_5050_4baa_A249_C964C6D5B7A8__INCLUDED_

#pragma once
#include "Body.h"
class CreatureBody : public Body
{

public:
	CreatureBody();
	virtual ~CreatureBody();
	double GetTotalVitality() override;

};
#endif // !defined(EA_E7C4D473_5050_4baa_A249_C964C6D5B7A8__INCLUDED_)
