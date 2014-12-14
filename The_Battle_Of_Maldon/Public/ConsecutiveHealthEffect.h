#pragma once
#include "Array.h"
#include "HealthEffect.h"
#include "UnrealString.h"
#include "LivingEntity.h"

class ConsecutiveHealthEffect : public HealthEffect {

public:
	double HealthPercentIncrease = 1.5;
	double minChange = 0.0;
	double maxChange = 10000;

	ConsecutiveHealthEffect(EffectStructs::ConsecutiveHealthParams params, ALivingEntity* owner) : HealthEffect(params, owner) {
		type = EffectEnums::ConsecutiveHealth;
		HealthPercentIncrease = params.HealthPercentIncrease;
		minChange = params.minChange;
		maxChange = params.maxChange;
	}

	virtual void ApplyEffect(){
		HealthEffect::ApplyEffect();
		double tempHealth = amountOfChange *= HealthPercentIncrease;

		if (tempHealth > maxChange){
			tempHealth = maxChange;
		}
		else if (tempHealth < minChange){
			tempHealth = minChange;
		}
	}

	virtual void Expired(){};
};