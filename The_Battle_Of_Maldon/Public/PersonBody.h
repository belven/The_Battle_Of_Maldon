///////////////////////////////////////////////////////////
//  PersonBody.h
//  Implementation of the Class PersonBody
//  Created on:      25-Apr-2015 14:02:40
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_1149FD36_402D_45f8_928C_5962BE3AC4BF__INCLUDED_)
#define EA_1149FD36_402D_45f8_928C_5962BE3AC4BF__INCLUDED_

#pragma once
#include "Body.h"
class PersonBody : public Body
{

public:
	PersonBody();
	virtual ~PersonBody();
	double GetTotalVitality() override;

};
#endif // !defined(EA_1149FD36_402D_45f8_928C_5962BE3AC4BF__INCLUDED_)
