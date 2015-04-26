///////////////////////////////////////////////////////////
//  Tornadoe.h
//  Implementation of the Class Tornadoe
//  Created on:      25-Apr-2015 22:22:02
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_440D2FB2_48C7_41d9_8E28_F0ECE30DB895__INCLUDED_)
#define EA_440D2FB2_48C7_41d9_8E28_F0ECE30DB895__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Tornadoe : public Weather
{

public:
	Tornadoe();
	virtual ~Tornadoe();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_440D2FB2_48C7_41d9_8E28_F0ECE30DB895__INCLUDED_)
