#pragma once
#include "Array.h"
#include "Effect.h"
#include "UnrealString.h"
#include "LivingEntity.h"
#include "Modifier.h"

class ModifierManager {
public:
	TArray<Modifier*> currentModifiers;

	const FString speedModiferName = "Speed";
	const FString damageModiferName = "Damage";
	const FString defenseModiferName = "Defense";

	void SetModifier(FString name, double value, bool positive){
		Modifier* m = GetModifier(name);

		if (m){
			ChangeModifier(m, value, positive);
		}
		else{
			m = GetBaseModifier(name);
			ChangeModifier(m, value, positive);
			currentModifiers.Add(m);
		}
	}

	void ChangeModifier(Modifier* m, double value, bool positive){
		if (positive){
			m->value += value;
		}
		else{
			m->value -= value;
		}
	}

	Modifier* GetModifier(FString name){
		for (Modifier* m : currentModifiers){
			if (m->name.Equals(name))
				return m;
		}

		return NULL;
	}

	Modifier* GetBaseModifier(FString name){
		return new Modifier(name, 1);
	}


};