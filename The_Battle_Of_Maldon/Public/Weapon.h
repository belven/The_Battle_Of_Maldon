#pragma once
#include "Item.h"
#include "Stat.h"
#include "Equipable.h"
#include "Part.h"
#include "Weapon.generated.h"

UCLASS()
class AWeapon : public AItem, public Equipable
{
	GENERATED_BODY()

public:
	AWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		double GetWeaponDamage();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		double GetWeaponRange();

	void SetWeaponDamage(Stat<double> newVal);
	void SetWeaponRange(Stat<double> newVal);

	virtual void Equip(ALivingEntity* entity);
	virtual void UnEquip(ALivingEntity* entity);

	bool IsEquiped();
	void SetEquiped(bool newVal);

	PartEnums::PartType GetBodyPart();
	void SetBodyPart(PartEnums::PartType newVal);
	bool IsTwoHanded();
	void SetTwoHanded(bool newVal);

private:
	Stat<double> weaponDamage = *new Stat<double>(100);
	Stat<double> weaponRange = *new Stat<double>(200);
	TEnumAsByte<PartEnums::PartType> bodyPart = PartEnums::Chest;
	bool twoHanded = false;
};