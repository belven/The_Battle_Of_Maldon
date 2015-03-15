#pragma once
#include "Array.h"
#include "Effect.h"
#include "UnrealString.h"
#include "LivingEntity.h"
#include "Modifier.h"

/*This class is used to add modifier based methods and proporties to another class so it can utilise modifiers*/
class ModifierManager {
public:
	TArray<Modifier*> currentModifiers;

	const FString speedModiferName = "Speed";
	const FString damageModiferName = "Damage";
	const FString defenseModiferName = "Defense";

	/*Sets a modifiers value based on if it exists and if it's positive or not*/
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

	/*Changes a modifiers value*/
	void ChangeModifier(Modifier* m, double value, bool positive){
		if (positive){
			m->value += value;
		}
		else{
			m->value -= value;
		}
	}

	/*Returns a modifier, if it exists, with the inputted name*/
	Modifier* GetModifier(FString name){
		for (TArray<Modifier*>::TConstIterator it = currentModifiers.CreateConstIterator(); it.GetIndex() != NULL; it++){
			Modifier* m = (Modifier*)*it;
			if (m->name.Equals(name))
				return m;
		}
		return NULL;
	}

	/*Returns a new basic modifier i.e. 100% with the inputted name*/
	Modifier* GetBaseModifier(FString name){
		return new Modifier(name, 1);
	}

};