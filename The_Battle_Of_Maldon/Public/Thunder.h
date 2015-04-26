///////////////////////////////////////////////////////////
//  Thunder.h
//  Implementation of the Class Thunder
//  Created on:      25-Apr-2015 22:22:01
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_6EBAABF5_60F8_4bc8_B9E6_88E1D55B9C91__INCLUDED_)
#define EA_6EBAABF5_60F8_4bc8_B9E6_88E1D55B9C91__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Thunder : public Weather
{

public:
	Thunder();
	virtual ~Thunder();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_6EBAABF5_60F8_4bc8_B9E6_88E1D55B9C91__INCLUDED_)
