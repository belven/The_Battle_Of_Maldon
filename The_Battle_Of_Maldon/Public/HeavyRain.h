///////////////////////////////////////////////////////////
//  HeavyRain.h
//  Implementation of the Class HeavyRain
//  Created on:      25-Apr-2015 22:21:58
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_9EC6218A_D532_408d_BF41_0DB357A0FFFD__INCLUDED_)
#define EA_9EC6218A_D532_408d_BF41_0DB357A0FFFD__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class HeavyRain : public Weather
{

public:
	HeavyRain();
	virtual ~HeavyRain();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_9EC6218A_D532_408d_BF41_0DB357A0FFFD__INCLUDED_)
