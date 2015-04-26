///////////////////////////////////////////////////////////
//  Rain.h
//  Implementation of the Class Rain
//  Created on:      25-Apr-2015 22:21:58
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_F0D4F124_2178_4754_91ED_E6C121ED753D__INCLUDED_)
#define EA_F0D4F124_2178_4754_91ED_E6C121ED753D__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Rain : public Weather
{

public:
	Rain();
	virtual ~Rain();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_F0D4F124_2178_4754_91ED_E6C121ED753D__INCLUDED_)
