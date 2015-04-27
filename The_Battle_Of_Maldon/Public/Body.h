///////////////////////////////////////////////////////////
//  Body.h
//  Implementation of the Class Body
//  Created on:      25-Apr-2015 09:00:17
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_0865252D_DAC2_43de_B077_B693DDD183B9__INCLUDED_)
#define EA_0865252D_DAC2_43de_B077_B693DDD183B9__INCLUDED_

#pragma once
#include "Part.h"
#include "Array.h"

/*
* A body is a collection of zero to many parts
* Every living entity will have a body
* Each part will have a visual representation 
* This will allow damage to be dealt to each individual part
* and therefore visually removed once damaged enough
*/
class Body
{

public:
	// Creates a blank body
	Body();

	virtual ~Body();

	// Returns a list of current body parts
	TArray<Part*> GetParts();

	//Sets the current body parts
	void SetParts(TArray<Part*> newVal);

	virtual double GetTotalVitality() = 0;

private:
	TArray<Part*> parts;

};
#endif // !defined(EA_0865252D_DAC2_43de_B077_B693DDD183B9__INCLUDED_)


