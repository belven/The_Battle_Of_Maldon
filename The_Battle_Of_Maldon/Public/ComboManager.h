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


class ComboManager
{

public:

	ComboManager(ALivingEntity* inOwner);

	void loadComboManager();

	void createTestComboManager();

	/*Creates a new Combo with all the approprite parameters*/
	Combo* GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton
		, class Effect* inEffect = NULL, CombatEnums::CombatType ActionType = CombatEnums::Attack);

	/*Reset the combo to the first, we might have failed to hit the buttons at the right time*/
	void StopCombo();

	/*Checks to see if the button pressed, e.g. F, is one of the ComboManager that the current one links to*/
	bool IsWithinCombo(FString BInput);

	/*This is to allow chaining of ComboManager as we can revert back to the starting combo to cut short are current assult*/
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

	bool WasLastComboManagerucsessfull();
	void SetLastComboManagerucsessfull(bool newVal);

	ALivingEntity* GetOwner();
	void SetOwner(ALivingEntity* newVal);

private:
	int ComboManagerID = 1;
	float lastDamage = 0;
	int hitCounter = 0;
	Combo* origanalCombo = NULL;
	Combo* currentCombo = NULL;
	bool lastComboManagerucsessfull = false;
	ALivingEntity* Owner = NULL;
};