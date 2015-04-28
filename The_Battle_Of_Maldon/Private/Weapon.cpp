#pragma once
#include "The_Battle_of_Maldon.h"

AWeapon::AWeapon()
{
	CurrentItemType = ItemEnumns::Weapon;
}

double AWeapon::GetWeaponDamage(){
	return weaponDamage.GetValue();
}


double AWeapon::GetWeaponRange(){
	return weaponRange.GetValue();
}


void AWeapon::SetWeaponDamage(Stat newVal){
	weaponDamage = newVal;
}


void AWeapon::SetWeaponRange(Stat newVal){
	weaponRange = newVal;
}


void AWeapon::Equip(ALivingEntity* entity){
	for (AWeapon* w : entity->GetEquipedWeapons()){
		if (IsTwoHanded() || w->GetBodyPart() == GetBodyPart()){
			w->UnEquip(entity);
		}
	}

	entity->AddWeapon(this);
	SetEquiped(true);
}

void AWeapon::UnEquip(ALivingEntity* entity) {
	entity->GetEquipedWeapons().Remove(this);
	SetEquiped(false);
}


bool AWeapon::IsEquiped(){
	return isEquiped;
}


void AWeapon::SetEquiped(bool newVal){
	isEquiped = newVal;
}

PartEnums::PartType AWeapon::GetBodyPart(){
	return bodyPart;
}


void AWeapon::SetBodyPart(PartEnums::PartType newVal){
	bodyPart = newVal;
}


bool AWeapon::IsTwoHanded(){
	return twoHanded;
}


void AWeapon::SetTwoHanded(bool newVal){
	twoHanded = newVal;
}