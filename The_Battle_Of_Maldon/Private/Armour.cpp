///////////////////////////////////////////////////////////
//  AArmour.cpp
//  Implementation of the Class AArmour
//  Created on:      27-Apr-2015 19:37:53
//  Original author: sam
///////////////////////////////////////////////////////////
#pragma once
#include "The_Battle_of_Maldon.h"
#include "Armour.h"


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


void AArmour::Equip(ALivingEntity* entity){
	AArmour* equipedArmour = NULL;

	for (AArmour* a : entity->GetEquipedArmour()){
		if (a->GetBodyPart() == GetBodyPart()){
			equipedArmour = a;
			break;
		}
	}

	if (equipedArmour){
		equipedArmour->UnEquip(entity);
	}

	entity->GetEquipedArmour().Add(this);
	SetEquiped(true);
}


void AArmour::UnEquip(ALivingEntity* entity) {
	entity->GetEquipedArmour().Remove(this);
	SetEquiped(false);
}


bool AArmour::IsEquiped(){
	return isEquiped;
}


void AArmour::SetEquiped(bool newVal){
	isEquiped = newVal;
}


PartEnums::PartType AArmour::GetBodyPart(){
	return bodyPart;
}


void AArmour::SetBodyPart(PartEnums::PartType newVal){
	bodyPart = newVal;
}