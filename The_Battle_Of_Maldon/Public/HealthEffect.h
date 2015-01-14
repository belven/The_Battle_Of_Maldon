#pragma once
#include "Array.h"
#include "Effect.h"
#include "Damage.h"
#include "UnrealString.h"
#include "LivingEntity.h"

/*This effect is used to heal/damage entities, positive is a heal, !positive is damage*/
class HealthEffect : public Effect {

public:
	double amountOfChange = 1.0;
	bool positive = false;

	HealthEffect(EffectStructs::HealthParams params, ALivingEntity* owner) : Effect(params, owner){
		type = EffectEnums::Health;
		amountOfChange = params.amountOfChange;
		positive = params.positive;
	}

	/*Run when the effect is applied, i.e. deal damage/heal*/
	virtual void ApplyEffect(){
		if (positive) {			
			//EffectOwner->GiveHealth(healthModifier);
		}
		else {
			effectOwner->InflictDamage(new Damage(amountOfChange));
		}
	}

	virtual void Expired(){}
};