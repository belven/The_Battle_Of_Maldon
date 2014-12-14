#pragma once
#include "Combo.h"
#include "Array.h"
#include "LivingEntity.h"
#include "UnrealString.h"
#include "TimerManager.h"
#include "CombatAction.h"

class Combos
{

public:
	int CombosID;
	float LastDamage;
	int HitCounter;
	Combo* OriganalCombo;
	Combo* CurrentCombo;
	bool lastComboSucsessfull;
	class ALivingEntity* Owner;
	//Name AnimNode;
	//Name ComboAnim;
	//SoundCue SwordClank;
	//AnimNodePlayCustomAnim CustomAnimNode;
	//Combo_DataProvider CurrentDB;

	Combos(class ALivingEntity* inOwner)
	{
		Owner = inOwner;
		LastDamage = 0;
		lastComboSucsessfull = false;
		HitCounter = 0;
		CombosID = 1;
		GetAndSetCombos();
	}

	void GetAndSetCombos()
	{
		//CurrentDB = RPGGame(WorldInfo.Game).ComboDB;
		//GetFirstCombo();
		createTestCombos();
	}

	void createTestCombos()
	{
		/*	if (Owner->CurrentAggressionType == LivingEntityEnums::Aggressive)
			{
			Combo* tempCombo = GenerateCombo(1, 1, 0.5f, "E");

			Combo* tempCombo2 = GenerateCombo(2, 1, 0.5f, "E");
			Combo* tempCombo3 = GenerateCombo(3, 1, 2.5f, "F");
			Combo* tempCombo4 = GenerateCombo(4, 3, 1.0f, "Q");
			Combo* tempCombo5 = GenerateCombo(5, 1.2, 0.5f, "E");

			tempCombo->ComboList.Add(tempCombo2);
			tempCombo2->ComboList.Add(tempCombo3);
			tempCombo2->ComboList.Add(tempCombo5);
			tempCombo3->ComboList.Add(tempCombo4);
			OriganalCombo = tempCombo;
			SetNextCombo(OriganalCombo);
			}
			else
			{*/
		float modifier = 1;
		float delay = rand() % 3 + modifier;
		Combo* tempCombo = GenerateCombo(1, 1, delay, "");

		delay = rand() % 2 + modifier;
		Combo* tempCombo2 = GenerateCombo(2, 1, delay, "E");

		delay = rand() % 2 + modifier;
		Combo* tempCombo3 = GenerateCombo(3, 2, delay, "F");

		delay = rand() % 2 + modifier;
		Combo* tempCombo4 = GenerateCombo(4, 3, delay, "Q");

		delay = rand() % 2 + modifier;
		Combo* tempCombo5 = GenerateCombo(5, 1.5, delay, "E");

		delay = rand() % 2 + modifier;
		Combo* tempCombo6 = GenerateCombo(6, 1.5, delay, "R");

		delay = rand() % 2 + modifier;
		Combo* tempCombo7 = GenerateCombo(7, 1.5, delay, "F");

		tempCombo->ComboList.Add(tempCombo2);
		tempCombo2->ComboList.Add(tempCombo3);
		tempCombo2->ComboList.Add(tempCombo5);
		tempCombo3->ComboList.Add(tempCombo4);
		tempCombo5->ComboList.Add(tempCombo6);
		tempCombo6->ComboList.Add(tempCombo7);

		OriganalCombo = tempCombo;
		SetNextCombo(OriganalCombo);
		//}
	}

	void GetFirstCombo()
	{
		int FirstComboID = 0;
		TArray<FString> CurrentDBData;

		/*
		if (CurrentDB == NULL)
		{
		GetAndSetCombos();
		}

		CurrentDB.GetSingleCombos(CombosID);

		if (CurrentDB.GetDataCount() > 0)
		{
		CurrentDBData = CurrentDB.GetDataSet(0);
		FirstComboID = int(CurrentDBData[0]);

		CurrentDB.GetSingleCombo(FirstComboID);

		if (CurrentDB.GetDataCount() > 0)
		{
		CurrentDBData = CurrentDB.GetDataSet(0);

		OriganalCombo = GenerateCombo(int(CurrentDBData[0]), CurrentDBData[1],
		float(CurrentDBData[2]), float(CurrentDBData[3]), Name(CurrentDBData[4]));
		SetNextCombo(OriganalCombo);
		GenerateCombos(OriganalCombo);
		}
		else
		{
		`log("No Data from GetSingleCombo" @ FirstComboID);
		}
		}
		else
		{
		`log("No Data from GetCombos" @ CombosID);
		}*/
	}

	void GenerateCombos(Combo* tempCombo)
	{
		int i = 0;
		int RowCount = 0;
		//TArray<FString> CurrentDBData;

		//CurrentDB.GetLinkedCombos(tempCombo.ComboID);

		//RowCount = CurrentDB.GetDataCount();

		/*if (RowCount > 0)
		{
		for (i = 0; i < RowCount; i++)
		{
		CurrentDBData = CurrentDB.GetDataSet(i);
		tempCombo.Add(GenerateCombo(int(CurrentDBData[0]), CurrentDBData[1],
		float(CurrentDBData[2]), float(CurrentDBData[3]), Name(CurrentDBData[4])));
		}

		for (i = 0; i < tempCombo.ComboList.Length; i++)
		{
		GenerateCombos(tempCombo.ComboList[i]);
		}
		}
		else
		{
		return;
		}*/
	}

	Combo* GenerateCombo(int ComboID, float tempComboDamageScaling, float tempComboDelay, FString tempComboButton
		, CombatEnums::CombatType ActionType = CombatEnums::Attack)
	{
		Combo* tempCombo = new Combo();
		tempCombo->ComboButton = *tempComboButton;
		tempCombo->ComboDamageScaling = tempComboDamageScaling;
		tempCombo->ComboDelay = tempComboDelay;
		tempCombo->CurrentCombatActionType = ActionType;
		//tempCombo.ComboAnim = tempComboAnim;
		tempCombo->ComboID = ComboID;
		return tempCombo;
	}

	void StopCombo()
	{
		LastDamage = 0;
		HitCounter = 0;
		CurrentCombo = OriganalCombo;
	}

	bool IsWithinCombo(FString* BInput)
	{
		bool PartOfCombo = false;
		int i = 0;

		if (CurrentCombo != NULL)
		{
			for (i = 0; i < CurrentCombo->ComboList.Num(); i++)
			{
				if (CurrentCombo->ComboList[i]->ComboButton == *BInput)
				{
					SetNextCombo(CurrentCombo->ComboList[i]);
					PartOfCombo = true;
					break;
				}
			}
		}

		return PartOfCombo;
	}

	bool IsWithinOriginalCombo(FString* BInput)
	{
		bool PartOfCombo = false;
		int i = 0;

		if (CurrentCombo != NULL)
		{
			for (i = 0; i < OriganalCombo->ComboList.Num(); i++)
			{
				if (OriganalCombo->ComboList[i]->ComboButton == *BInput)
				{
					SetNextCombo(OriganalCombo->ComboList[i]);
					PartOfCombo = true;
					break;
				}
			}
		}

		return PartOfCombo;
	}

	float ComboButtonPressed(FString BInput, float WeaponDamage)
	{
		//ItemOwner = WeaponOwner;

		/*if (ItemOwner != NULL && CustomAnimNode == NULL)
		{
		CustomAnimNode = AnimNodePlayCustomAnim(ItemOwner.Mesh.FindAnimNode(AnimNode));
		}*/

		if (CurrentCombo->ComboList.Num() == 0)
		{
			//GetWorldTimerManager().ClearTimer(this, &Combos::StopCombo);
			//GetWorldTimerManager().SetTimer(this, &Combos::StopCombo, 0.2f);
			StopCombo();
		}

		if (IsWithinCombo(&BInput))
		{
			//Run combo animation
			/*if (CustomAnimNode != NULL)
				{
				CustomAnimNode.PlayCustomAnim(tempCurrentCombo->ComboAnim, 1.0);
				}*/
			//ItemOwner->GetWorldTimerManager().ClearTimer(ItemOwner, &ALivingEntity::StopCombo);
			//ItemOwner->GetWorldTimerManager().SetTimer(ItemOwner, &ALivingEntity::StopCombo, CurrentCombo->ComboDelay);

			//if (CurrentCombo->CurrentCombatActionType != CombatEnums::Defense)
			//{
			lastComboSucsessfull = true;
			CalculateDamage(WeaponDamage);
			//}
		}
		else if (IsWithinOriginalCombo(&BInput))
		{
			lastComboSucsessfull = true;
			CalculateDamage(WeaponDamage);
		}
		else
		{
			//GetWorldTimerManager().ClearTimer(this, &Combos::StopCombo);
			StopCombo();
			lastComboSucsessfull = false;
		}

		if (CurrentCombo->ComboList.Num() == 0)
		{
			//GetWorldTimerManager().ClearTimer(this, &Combos::StopCombo);
			//GetWorldTimerManager().SetTimer(this, &Combos::StopCombo, 0.2f);
		}

		return LastDamage;
	}

	void SetNextCombo(Combo* nextCombo)
	{
		CurrentCombo = nextCombo;
	}

	void CalculateDamage(float WeaponDamage)
	{
		if (LastDamage == 0)
		{
			LastDamage = WeaponDamage;
		}
		else
		{
			LastDamage = LastDamage * CurrentCombo->ComboDamageScaling;
		}
		HitCounter++;
	}

};