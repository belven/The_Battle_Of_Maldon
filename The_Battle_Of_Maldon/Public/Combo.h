#pragma once
#include "Array.h"
#include "UnrealString.h"

class Combo
{

public:
	Combo();
	void Add(Combo* ComboToAdd);

	int GetComboID();
	void SetComboID(int newVal);

	float GetComboDamageScaling();
	void SetComboDamageScaling(float newVal);

	float GetComboDelay();
	void SetComboDelay(float newVal);

	TArray<Combo*> GetComboList();
	void SetComboList(TArray<Combo*> newVal);

	FString GetComboButton();
	void SetComboButton(FString newVal);

	CombatEnums::CombatType GetCurrentCombatActionType();
	void SetCurrentCombatActionType(CombatEnums::CombatType newVal);

	class Effect* GetEffect();
	void SetEffect(class Effect* newVal);

private:
	int comboID;
	float cmboDamageScaling;
	float comboDelay;

	class Effect* effect;
	TArray<Combo*> comboList = *new TArray<Combo*>();
	FString comboButton;

	CombatEnums::CombatType currentCombatActionType;
	float comboDamageScaling;
};