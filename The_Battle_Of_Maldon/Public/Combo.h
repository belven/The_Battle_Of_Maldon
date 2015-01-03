#pragma once
#include "Array.h"
#include "UnrealString.h"
#include "CombatAction.h"

class Combo
{

public:
	Combo()
	{
		ComboID = 1;
		ComboButton = "";
		ComboDamageScaling = 1;
		ComboDelay = 1;
	}

	int ComboID;
	float ComboDamageScaling;
	float ComboDelay;
	TArray<Combo*> ComboList;
	FString ComboButton;
	CombatEnums::CombatType currentCombatActionType;

	void Add(Combo* ComboToAdd)
	{
		ComboList.Add(ComboToAdd);
	}
};