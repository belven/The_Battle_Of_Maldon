

#include "The_Battle_of_Maldon.h"
#include "Weapon.h"


AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentItemType = ItemEnumns::Weapon;

	weaponDamage = 10;
	weaponRange = 200;
}