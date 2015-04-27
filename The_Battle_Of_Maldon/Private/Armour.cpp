///////////////////////////////////////////////////////////
//  AArmour.cpp
//  Implementation of the Class AArmour
//  Created on:      27-Apr-2015 19:37:53
//  Original author: sam
///////////////////////////////////////////////////////////
#pragma once
#include "The_Battle_of_Maldon.h"
#include "Armour.h"
#include "Part.h"


AArmour::AArmour(){

}


double AArmour::GetArmourStrength(){
	return armourStrength.GetValue();
}


void AArmour::SetArmourStrength(Stat newVal){
	armourStrength = newVal;
}


void AArmour::SetArmourStrength(double newVal){
	armourStrength = *new Stat(newVal);
}


void AArmour::Equip(ALivingEntity entity){

}


void AArmour::UnEquip(ALivingEntity entity) {

}


bool AArmour::IsEquiped(){
	return isEquiped;
}


void AArmour::SetEquiped(bool newVal){
	isEquiped = newVal;
}