#pragma once
#include "Combo.h"
#include "Array.h"
#include "UnrealString.h"
#include "TimerManager.h"
#include "CombatAction.h"
#include "Effect.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


class Combos
{

public:

	Combos(ALivingEntity* inOwner);

	void loadCombos();

	void createTestCombos();

	/*Creates a new Combo with all the approprite parameters*/
	Combo* GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton
		, class Effect* inEffect = NULL, CombatEnums::CombatType ActionType = CombatEnums::Attack);

	/*Reset the combo to the first, we might have failed to hit the buttons at the right time*/
	void StopCombo();

	/*Checks to see if the button pressed, e.g. F, is one of the combos that the current one links to*/
	bool IsWithinCombo(FString BInput);

	/*This is to allow chaining of combos as we can revert back to the starting combo to cut short are current assult*/
	bool IsWithinOriginalCombo(FString BInput);
	void SetNextCombo(Combo* nextCombo);
	void CalculateDamage(float WeaponDamage);

	float GetLastDamage();
	void SetLastDamage(float newVal);

	int GetHitCounter();
	void SetHitCounter(int newVal);

	Combo* GetOriganalCombo();
	void SetOriganalCombo(Combo* newVal);

	Combo* GetCurrentCombo();
	void SetCurrentCombo(Combo* newVal);

	bool WasLastComboSucsessfull();
	void SetLastComboSucsessfull(bool newVal);

	ALivingEntity* GetOwner();
	void SetOwner(ALivingEntity* newVal);

private:
	int CombosID;
	float lastDamage;
	int hitCounter;
	Combo* origanalCombo;
	Combo* currentCombo;
	bool lastComboSucsessfull;
	ALivingEntity* Owner;
};