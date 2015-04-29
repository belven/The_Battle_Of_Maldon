
#include "The_Battle_of_Maldon.h"

Combo::Combo()
{
}

void Combo::Add(Combo* ComboToAdd)
{
	comboList.Add(ComboToAdd);
}


int Combo::GetComboID(){
	return comboID;
}


void Combo::SetComboID(int newVal){
	comboID = newVal;
}


float Combo::GetComboDamageScaling(){
	return comboDamageScaling;
}


void Combo::SetComboDamageScaling(float newVal){
	comboDamageScaling = newVal;
}


float Combo::GetComboDelay(){
	return comboDelay;
}


void Combo::SetComboDelay(float newVal){
	comboDelay = newVal;
}


TArray<Combo*> Combo::GetComboList(){
	return comboList;
}


void Combo::SetComboList(TArray<Combo*> newVal){
	comboList = newVal;
}


FString Combo::GetComboButton(){
	return comboButton;
}


void Combo::SetComboButton(FString newVal){
	comboButton = newVal;
}


CombatEnums::CombatType Combo::GetCurrentCombatActionType(){
	return currentCombatActionType;
}


void Combo::SetCurrentCombatActionType(CombatEnums::CombatType newVal){
	currentCombatActionType = newVal;
}


Effect* Combo::GetEffect(){
	return effect;
}


void Combo::SetEffect(Effect* newVal){
	effect = newVal;
}