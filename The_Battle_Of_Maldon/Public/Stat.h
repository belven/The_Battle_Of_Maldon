///////////////////////////////////////////////////////////
//  Stat.h
//  Implementation of the Class Stat
//  Created on:      27-Apr-2015 19:02:38
//  Original author: sam
///////////////////////////////////////////////////////////

#if !defined(EA_C7DA055B_AB8E_4cee_B943_2DE3C2FABA98__INCLUDED_)
#define EA_C7DA055B_AB8E_4cee_B943_2DE3C2FABA98__INCLUDED_

class Stat
{

public:
	Stat(double value);
	virtual ~Stat();

	double GetValue();
	void SetValue(double newVal);
private:
	double value;

};
#endif // !defined(EA_C7DA055B_AB8E_4cee_B943_2DE3C2FABA98__INCLUDED_)
