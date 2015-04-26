///////////////////////////////////////////////////////////
//  Snow.h
//  Implementation of the Class Snow
//  Created on:      25-Apr-2015 22:22:00
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_E3558114_9BFB_446c_A651_6CAD0FB0E039__INCLUDED_)
#define EA_E3558114_9BFB_446c_A651_6CAD0FB0E039__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Snow : public Weather
{

public:
	Snow();
	virtual ~Snow();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_E3558114_9BFB_446c_A651_6CAD0FB0E039__INCLUDED_)
