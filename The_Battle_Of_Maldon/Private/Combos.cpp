#pragma once
#include "The_Battle_of_Maldon.h"

Combos::Combos(ALivingEntity* inOwner)
{
	Owner = inOwner;
	lastDamage = 0;
	lastComboSucsessfull = false;
	hitCounter = 0;
	CombosID = 1;
	GetAndSetCombos();
}

void Combos::getCombos(){
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

void Combos::GetAndSetCombos()
{
	createTestCombos();
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
	tempCombo->ComboList.Add(tempCombo2);

	//E - R - F
	tempCombo->ComboList.Add(tempCombo6);

	//E - F
	tempCombo2->ComboList.Add(tempCombo3);

	//E - F - Q
	tempCombo3->ComboList.Add(tempCombo4);

	//--------------------------
	//E - Q
	tempCombo2->ComboList.Add(tempCombo8);

	//E - Q - E
	tempCombo8->ComboList.Add(tempCombo5);

	//--------------------------
	//E - E
	tempCombo2->ComboList.Add(tempCombo5);

	//E - E - R
	tempCombo5->ComboList.Add(tempCombo6);

	//E - E - R - F
	tempCombo6->ComboList.Add(tempCombo7);

	origanalCombo = tempCombo;
	SetNextCombo(origanalCombo);
}

/*Creates a new Combo with all the approprite parameters*/
Combo* Combos::GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton,
class Effect* inEffect, CombatEnums::CombatType ActionType)
{
	Combo* tempCombo = new Combo();
	tempCombo->ComboButton = *tempComboButton;
	tempCombo->ComboDamageScaling = tempComboDamageScaling;
	tempCombo->ComboDelay = tempComboDelay;
	tempCombo->currentCombatActionType = ActionType;
	tempCombo->effect = inEffect;
	//tempCombo.ComboAnim = tempComboAnim;
	tempCombo->ComboID = ComboID;
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
bool Combos::IsWithinCombo(FString* BInput)
{
	bool PartOfCombo = false;
	int i = 0;

	if (currentCombo != NULL)
	{
		for (i = 0; i < currentCombo->ComboList.Num(); i++)
		{
			if (currentCombo->ComboList[i]->ComboButton == *BInput)
			{
				SetNextCombo(currentCombo->ComboList[i]);
				PartOfCombo = true;
				break;
			}
		}
	}

	return PartOfCombo;
}

/*This is to allow chaining of combos as we can revert back to the starting combo to cut short are current assult*/
bool Combos::IsWithinOriginalCombo(FString* BInput)
{
	bool PartOfCombo = false;
	int i = 0;

	if (currentCombo != NULL)
	{
		for (i = 0; i < origanalCombo->ComboList.Num(); i++)
		{
			if (origanalCombo->ComboList[i]->ComboButton == *BInput)
			{
				SetNextCombo(origanalCombo->ComboList[i]);
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
		lastDamage = lastDamage * currentCombo->ComboDamageScaling;
	}
	hitCounter++;
}