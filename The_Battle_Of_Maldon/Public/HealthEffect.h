#pragma once
#include "Effect.h"

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
		FLivingEntityDamage damage;

		if (positive) {
			damage.damageDone -= amountOfChange;
		}
		else {
			damage.damageDone = amountOfChange;
		}

		effectOwner->InflictDamage(damage);
	}

	virtual void Expired(){}
};