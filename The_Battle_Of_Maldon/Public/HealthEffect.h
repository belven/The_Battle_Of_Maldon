#pragma once
#include "Array.h"
#include "Effect.h"
#include "UnrealString.h"
#include "LivingEntity.h"

class HealthEffect : public Effect {

public:
	double amountOfChange = 1.0;
	bool positive = false;

	HealthEffect(EffectStructs::HealthParams params, ALivingEntity* owner) : Effect(params, owner){
		type = EffectEnums::Health;
		amountOfChange = params.amountOfChange;
		positive = params.positive;
	}

	virtual void ApplyEffect(){
		if (positive){
			
			//EffectOwner->GiveHealth(healthModifier);
		}
		else{
			//EffectOwner->TakeHealth(healthModifier);
		}
	}

	virtual void Expired(){}
};