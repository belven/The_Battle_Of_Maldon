#pragma once
//#include "LivingEntity.h"

class Damage
{
public:
	//Damage(ALivingEntity* eh, ALivingEntity* ae, float damageIn)
	Damage(float damageIn)
	{
		//entityHit = eh;
		//attackingEntity = ae;
		damageDone = damageIn;
	}

	//ALivingEntity* entityHit;
	//ALivingEntity* attackingEntity;
	float damageDone = 0;

};