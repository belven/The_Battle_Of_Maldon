#pragma once
#include "Array.h"
#include "Effect.h"
#include "UnrealString.h"
#include "LivingEntity.h"

class ModifierEffect : public Effect {

public:
	double modifier = 0.2;
	bool positive = false;
	FString modifierName = "";

	ModifierEffect(EffectStructs::ModifierParams params, ALivingEntity* owner) : Effect(params, owner) {
		type = EffectEnums::Modifier;
		modifier = params.modifier;
		modifierName = params.modifierName;
		positive = params.positive;
	}

	virtual void ApplyEffect(){
		if (!stacks && !effectOwner->HasEffect(this)){
			effectOwner->SetModifier(modifierName, modifier, positive);
		}
		else if (stacks){
			effectOwner->SetModifier(modifierName, modifier, positive);
		}
	}

	virtual void Expired(){
		effectOwner->SetModifier(modifierName, 1, !positive);
	}
};