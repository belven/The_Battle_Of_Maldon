#pragma once
#include "Array.h"
#include "UnrealString.h"

class Combo
{

public:
	Combo();

	int ComboID;
	float ComboDamageScaling;
	float ComboDelay;

	class Effect* effect;
	TArray<Combo*> ComboList;
	FString ComboButton;

	CombatEnums::CombatType currentCombatActionType;

	void Add(Combo* ComboToAdd);
};