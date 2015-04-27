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
	AWeapon* equipedWeapon = NULL;

	for (AWeapon* w : entity->GetEquipedWeapons()){
		if (w->GetBodyPart() == GetBodyPart()){
			equipedWeapon = w;
			break;
		}
	}

	if (equipedWeapon){
		equipedWeapon->UnEquip(entity);
	}

	entity->GetEquipedWeapons().Add(this);
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