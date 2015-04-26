///////////////////////////////////////////////////////////
//  Environment.h
//  Implementation of the Class Environment
//  Created on:      25-Apr-2015 21:41:55
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_E819ED33_25A3_459e_BC45_825B23DCB4E3__INCLUDED_)
#define EA_E819ED33_25A3_459e_BC45_825B23DCB4E3__INCLUDED_

#include "Weather.h"
#include <vector>

class Environment
{

public:
	Environment();
	virtual ~Environment();

	std::vector<Weather*> GetWeather();
	void SetWeather(std::vector<Weather*> newVal);
	Weather* GetCurrentWeather();
	void SetCurrentWeather(Weather* newVal);
	Weather* GetDefaultWeather();
	void SetDefaultWeather(Weather* newVal);

private:
	std::vector<Weather*> weather;
	Weather* currentWeather;
	Weather* defaultWeather;

};
#endif // !defined(EA_E819ED33_25A3_459e_BC45_825B23DCB4E3__INCLUDED_)
