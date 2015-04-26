///////////////////////////////////////////////////////////
//  Weather.h
//  Implementation of the Class Weather
//  Created on:      25-Apr-2015 21:41:57
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_E847C5EF_7819_4b9e_9D25_9468265C2154__INCLUDED_)
#define EA_E847C5EF_7819_4b9e_9D25_9468265C2154__INCLUDED_

class Environment;

class Weather
{

public:
	Weather();
	virtual ~Weather();

	double GetDuration();
	void SetDuration(double newVal);
	virtual void StartWeather(Environment* env) = 0;
	virtual void StopWeather(Environment* env) = 0;

private:
	double duration;

};
#endif // !defined(EA_E847C5EF_7819_4b9e_9D25_9468265C2154__INCLUDED_)
