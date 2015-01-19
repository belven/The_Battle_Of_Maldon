

#pragma once
#include "The_Battle_of_Maldon.h"

ACombosBP::ACombosBP(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	/*LastDamage = 0;
	lastComboSucsessfull = false;
	HitCounter = 0;*/
}

//void ACombosBP::StopCombo()
//{
//	LastDamage = 0;
//	HitCounter = 0;
//	CurrentCombo = OriganalCombo;
//}
//
//bool ACombosBP::IsWithinCombo(FString* BInput)
//{
//	bool PartOfCombo = false;
//	int i = 0;
//
//	if (CurrentCombo != NULL)
//	{
//		for (i = 0; i < CurrentCombo->ComboList.Num(); i++)
//		{
//			if (CurrentCombo->ComboList[i]->ComboButton == *BInput)
//			{
//				SetNextCombo(CurrentCombo->ComboList[i]);
//				PartOfCombo = true;
//				break;
//			}
//		}
//	}
//
//	return PartOfCombo;
//}
//
//bool ACombosBP::IsWithinOriginalCombo(FString* BInput)
//{
//	bool PartOfCombo = false;
//	int i = 0;
//
//	if (CurrentCombo != NULL)
//	{
//		for (i = 0; i < OriganalCombo->ComboList.Num(); i++)
//		{
//			if (OriganalCombo->ComboList[i]->ComboButton == *BInput)
//			{
//				SetNextCombo(OriganalCombo->ComboList[i]);
//				PartOfCombo = true;
//				break;
//			}
//		}
//	}
//
//	return PartOfCombo;
//}
//
//float ACombosBP::ComboButtonPressed(FString BInput, float WeaponDamage)
//{
//	if (CurrentCombo->ComboList.Num() == 0)
//	{
//		StopCombo();
//	}
//
//	if (IsWithinCombo(&BInput))
//	{
//		lastComboSucsessfull = true;
//		CalculateDamage(WeaponDamage);
//	}
//	else if (IsWithinOriginalCombo(&BInput))
//	{
//		lastComboSucsessfull = true;
//		CalculateDamage(WeaponDamage);
//	}
//	else
//	{
//		StopCombo();
//		lastComboSucsessfull = false;
//	}
//
//	if (CurrentCombo->ComboList.Num() == 0)
//	{
//		//GetWorldTimerManager().ClearTimer(this, &Combos::StopCombo);
//		//GetWorldTimerManager().SetTimer(this, &Combos::StopCombo, 0.2f);
//	}
//
//	return LastDamage;
//}
//
//void ACombosBP::SetNextCombo(AComboBP* nextCombo)
//{
//	CurrentCombo = nextCombo;
//}
//
//void ACombosBP::CalculateDamage(float WeaponDamage)
//{
//	if (LastDamage == 0)
//	{
//		LastDamage = WeaponDamage;
//	}
//	else
//	{
//		LastDamage = LastDamage * CurrentCombo->ComboDamageScaling;
//	}
//	HitCounter++;
//}