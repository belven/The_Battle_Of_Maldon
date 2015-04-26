///////////////////////////////////////////////////////////
//  Sunny.h
//  Implementation of the Class Sunny
//  Created on:      25-Apr-2015 22:21:54
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_50C9D326_42B2_4816_AE80_EB745A8606CA__INCLUDED_)
#define EA_50C9D326_42B2_4816_AE80_EB745A8606CA__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Sunny : public Weather
{

public:
	Sunny();
	virtual ~Sunny();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_50C9D326_42B2_4816_AE80_EB745A8606CA__INCLUDED_)
