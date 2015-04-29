#pragma once
#include "The_Battle_of_Maldon.h"

ComboManager::ComboManager(ALivingEntity* inOwner)
{
	SetOwner(inOwner);
	createTestComboManager();
}

void ComboManager::loadComboManager(){
	//try
	//{

	//	std::ifstream data("test.csv");
	//	std::string line;

	//	while (std::getline(data, line))
	//	{
	//		std::stringstream lineStream(line);
	//		std::string cell;

	//		while (std::getline(lineStream, cell, ','))
	//		{
	//			// You have a cell!!!!
	//		}
	//	}
	//}
	//catch (...){
	//	UE_LOG(LogTemp, Warning, TEXT("Failed to load file"));
	//}
}

void ComboManager::createTestComboManager()
{
	float delay = 1;
	Combo* tempCombo = GenerateCombo(1, 1, delay, "");
	Combo* tempCombo2 = GenerateCombo(2, 1.75, 1, "E");
	Combo* tempCombo3 = GenerateCombo(3, 2.25, 2, "F");
	Combo* tempCombo4 = GenerateCombo(4, 1.15, 1.5, "Q");
	Combo* tempCombo5 = GenerateCombo(5, 2.25, 1, "E");
	
	Combo* tempCombo6 = GenerateCombo(6, 2.75, 1.25, "R");
	Combo* tempCombo7 = GenerateCombo(7, 1.4, 2, "F");
	Combo* tempCombo8 = GenerateCombo(8, 3.8, 1.75, "Q");

	//--------------------------
	tempCombo->Add(tempCombo2);

	//E - R - F
	tempCombo->Add(tempCombo6);

	//E - F
	tempCombo2->Add(tempCombo3);

	//E - F - Q
	tempCombo3->Add(tempCombo4);

	//--------------------------
	//E - Q
	tempCombo2->Add(tempCombo8);

	//E - Q - E
	tempCombo8->Add(tempCombo5);

	//--------------------------
	//E - E
	tempCombo2->Add(tempCombo5);

	//E - E - R
	tempCombo5->Add(tempCombo6);

	//E - E - R - F
	tempCombo6->Add(tempCombo7);

	SetOriganalCombo(tempCombo);
	SetNextCombo(tempCombo);
}

/*Creates a new Combo with all the approprite parameters*/
Combo* ComboManager::GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton,
class Effect* inEffect, CombatEnums::CombatType ActionType)
{
	Combo* tempCombo = new Combo();
	tempCombo->SetComboButton(tempComboButton);
	tempCombo->SetComboDamageScaling(tempComboDamageScaling);
	tempCombo->SetComboDelay(tempComboDelay);
	tempCombo->SetCurrentCombatActionType(ActionType);
	//tempCombo->SetEffect(inEffect);
	//tempCombo.ComboAnim = tempComboAnim;
	tempCombo->SetComboID(ComboID);
	return tempCombo;
}

/*Reset the combo to the first, we might have failed to hit the buttons at the right time*/
void ComboManager::StopCombo()
{
	lastDamage = 0;
	hitCounter = 0;
	currentCombo = origanalCombo;
}

/*Checks to see if the button pressed, e.g. F, is one of the ComboManager that the current one links to*/
bool ComboManager::IsWithinCombo(FString BInput)
{
	bool PartOfCombo = false;

	if (currentCombo != NULL)
	{
		for (Combo* combo : currentCombo->GetComboList())
		{
			if (combo->GetComboButton().Equals(BInput))
			{
				SetNextCombo(combo);
				PartOfCombo = true;
				break;
			}
		}
	}

	return PartOfCombo;
}

/*This is to allow chaining of ComboManager as we can revert back to the starting combo to cut short are current assult*/
bool ComboManager::IsWithinOriginalCombo(FString BInput)
{
	bool PartOfCombo = false;
	int i = 0;

	if (currentCombo != NULL)
	{
		for (Combo* combo : currentCombo->GetComboList())
		{
			if (combo->GetComboButton().Equals(BInput))
			{
				SetNextCombo(combo);
				PartOfCombo = true;
				break;
			}
		}
	}

	return PartOfCombo;
}


void ComboManager::SetNextCombo(Combo* nextCombo)
{
	currentCombo = nextCombo;
}

void ComboManager::CalculateDamage(float WeaponDamage)
{
	if (lastDamage == 0)
	{
		lastDamage = WeaponDamage;
	}
	else
	{
		lastDamage = lastDamage * currentCombo->GetComboDamageScaling();
	}
	hitCounter++;
}


float ComboManager::GetLastDamage(){
	return lastDamage;
}


void ComboManager::SetLastDamage(float newVal){
	lastDamage = newVal;
}


int ComboManager::GetHitCounter(){
	return hitCounter;
}


void ComboManager::SetHitCounter(int newVal){
	hitCounter = newVal;
}


Combo* ComboManager::GetOriganalCombo(){
	return origanalCombo;
}


void ComboManager::SetOriganalCombo(Combo* newVal){
	origanalCombo = newVal;
}


Combo* ComboManager::GetCurrentCombo(){
	return currentCombo;
}


void ComboManager::SetCurrentCombo(Combo* newVal){
	currentCombo = newVal;
}


bool ComboManager::WasLastComboManagerucsessfull(){
	return lastComboManagerucsessfull;
}


void ComboManager::SetLastComboManagerucsessfull(bool newVal){
	lastComboManagerucsessfull = newVal;
}


ALivingEntity* ComboManager::GetOwner(){
	return Owner;
}


void ComboManager::SetOwner(ALivingEntity* newVal){
	Owner = newVal;
}