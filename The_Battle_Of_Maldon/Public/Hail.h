///////////////////////////////////////////////////////////
//  Hail.h
//  Implementation of the Class Hail
//  Created on:      25-Apr-2015 22:21:57
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_C44D5986_15BC_4e8d_B56D_937B7A028203__INCLUDED_)
#define EA_C44D5986_15BC_4e8d_B56D_937B7A028203__INCLUDED_

#include "Environment.h"
#include "Weather.h"

class Hail : public Weather
{

public:
	Hail();
	virtual ~Hail();

	virtual void StartWeather(Environment* env);
	virtual void StopWeather(Environment* env);

};
#endif // !defined(EA_C44D5986_15BC_4e8d_B56D_937B7A028203__INCLUDED_)
