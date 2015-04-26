///////////////////////////////////////////////////////////
//  Blizzard.h
//  Implementation of the Class Blizzard
//  Created on:      25-Apr-2015 22:21:56
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_F5A9A69F_C4F3_4f1e_B5C6_8070FCEDC658__INCLUDED_)
#define EA_F5A9A69F_C4F3_4f1e_B5C6_8070FCEDC658__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Blizzard : public Weather
{

public:
	Blizzard();
	virtual ~Blizzard();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_F5A9A69F_C4F3_4f1e_B5C6_8070FCEDC658__INCLUDED_)
