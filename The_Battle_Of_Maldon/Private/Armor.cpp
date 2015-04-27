///////////////////////////////////////////////////////////
//  AArmor.cpp
//  Implementation of the Class AArmor
//  Created on:      27-Apr-2015 19:37:53
//  Original author: sam
///////////////////////////////////////////////////////////
#pragma once
#include "The_Battle_of_Maldon.h"
#include "Armor.h"


AArmor::AArmor(){

}


double AArmor::GetArmourStrength(){
	return armourStrength.GetValue();
}


void AArmor::SetArmourStrength(Stat newVal){
	armourStrength = newVal;
}


void AArmor::SetArmourStrength(double newVal){
	armourStrength = *new Stat(newVal);
}


void AArmor::Equip(ALivingEntity entity){

}


bool AArmor::IsEquiped(){
	return isEquiped;
}


void AArmor::SetEquiped(bool newVal){
	isEquiped = newVal;
}