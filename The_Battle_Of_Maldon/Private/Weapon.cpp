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


void AWeapon::Equip(ALivingEntity entity){

}

void AWeapon::UnEquip(ALivingEntity entity) {

}


bool AWeapon::IsEquiped(){

	return isEquiped;
}


void AWeapon::SetEquiped(bool newVal){

	isEquiped = newVal;
}