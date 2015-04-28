#pragma once
#include "The_Battle_of_Maldon.h"

Combos::Combos(ALivingEntity* inOwner)
{
	SetOwner(inOwner);
	SetLastDamage(0);
	SetLastComboSucsessfull(false);
	SetHitCounter(0);
	CombosID = 1;
	createTestCombos();
}

void Combos::loadCombos(){
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

void Combos::createTestCombos()
{
	float delay = 1;
	Combo* tempCombo = GenerateCombo(1, 1, delay, "");
	Combo* tempCombo2 = GenerateCombo(2, 1.75, 1, "E");
	Combo* tempCombo3 = GenerateCombo(3, 2.25, 2, "F");
	Combo* tempCombo4 = GenerateCombo(4, 1.15, 1.5, "Q");
	Combo* tempCombo5 = GenerateCombo(5, 2.25, 1, "E");

	EffectStructs::HealthParams hp;
	hp.amountOfChange = 20;
	hp.positive = false;
	hp.dely = 1;
	hp.id = "Basic Damage";
	hp.stacks = false;
	hp.maxDuration = 3;

	HealthEffect* he = new HealthEffect(hp, Owner);

	Combo* tempCombo6 = GenerateCombo(6, 2.75, 1.25, "R");
	Combo* tempCombo7 = GenerateCombo(7, 1.4, 2, "F");
	Combo* tempCombo8 = GenerateCombo(8, 3.8, 1.75, "Q");

	//--------------------------
	tempCombo->GetComboList().Add(tempCombo2);

	//E - R - F
	tempCombo->GetComboList().Add(tempCombo6);

	//E - F
	tempCombo2->GetComboList().Add(tempCombo3);

	//E - F - Q
	tempCombo3->GetComboList().Add(tempCombo4);

	//--------------------------
	//E - Q
	tempCombo2->GetComboList().Add(tempCombo8);

	//E - Q - E
	tempCombo8->GetComboList().Add(tempCombo5);

	//--------------------------
	//E - E
	tempCombo2->GetComboList().Add(tempCombo5);

	//E - E - R
	tempCombo5->GetComboList().Add(tempCombo6);

	//E - E - R - F
	tempCombo6->GetComboList().Add(tempCombo7);

	SetOriganalCombo(tempCombo);
	SetNextCombo(tempCombo);
}

/*Creates a new Combo with all the approprite parameters*/
Combo* Combos::GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton,
class Effect* inEffect, CombatEnums::CombatType ActionType)
{
	Combo* tempCombo = new Combo();
	tempCombo->SetComboButton(tempComboButton);
	tempCombo->SetComboDamageScaling(tempComboDamageScaling);
	tempCombo->SetComboDelay(tempComboDelay);
	tempCombo->SetCurrentCombatActionType(ActionType);
	tempCombo->SetEffect(inEffect);
	//tempCombo.ComboAnim = tempComboAnim;
	tempCombo->SetComboID(ComboID);
	return tempCombo;
}

/*Reset the combo to the first, we might have failed to hit the buttons at the right time*/
void Combos::StopCombo()
{
	lastDamage = 0;
	hitCounter = 0;
	currentCombo = origanalCombo;
}

/*Checks to see if the button pressed, e.g. F, is one of the combos that the current one links to*/
bool Combos::IsWithinCombo(FString BInput)
{
	bool PartOfCombo = false;
	int i = 0;

	if (currentCombo != NULL)
	{
		for (i = 0; i < currentCombo->GetComboList().Num(); i++)
		{
			if (currentCombo->GetComboList()[i]->GetComboButton().Equals(BInput))
			{
				SetNextCombo(currentCombo->GetComboList()[i]);
				PartOfCombo = true;
				break;
			}
		}
	}

	return PartOfCombo;
}

/*This is to allow chaining of combos as we can revert back to the starting combo to cut short are current assult*/
bool Combos::IsWithinOriginalCombo(FString BInput)
{
	bool PartOfCombo = false;
	int i = 0;

	if (currentCombo != NULL)
	{
		for (i = 0; i < origanalCombo->GetComboList().Num(); i++)
		{
			if (origanalCombo->GetComboList()[i]->GetComboButton().Equals(BInput))
			{
				SetNextCombo(origanalCombo->GetComboList()[i]);
				PartOfCombo = true;
				break;
			}
		}
	}

	return PartOfCombo;
}


void Combos::SetNextCombo(Combo* nextCombo)
{
	currentCombo = nextCombo;
}

void Combos::CalculateDamage(float WeaponDamage)
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


float Combos::GetLastDamage(){
	return lastDamage;
}


void Combos::SetLastDamage(float newVal){
	lastDamage = newVal;
}


int Combos::GetHitCounter(){
	return hitCounter;
}


void Combos::SetHitCounter(int newVal){
	hitCounter = newVal;
}


Combo* Combos::GetOriganalCombo(){
	return origanalCombo;
}


void Combos::SetOriganalCombo(Combo* newVal){
	origanalCombo = newVal;
}


Combo* Combos::GetCurrentCombo(){
	return currentCombo;
}


void Combos::SetCurrentCombo(Combo* newVal){
	currentCombo = newVal;
}


bool Combos::WasLastComboSucsessfull(){
	return lastComboSucsessfull;
}


void Combos::SetLastComboSucsessfull(bool newVal){
	lastComboSucsessfull = newVal;
}


ALivingEntity* Combos::GetOwner(){
	return Owner;
}


void Combos::SetOwner(ALivingEntity* newVal){
	Owner = newVal;
}