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

	void SetWeaponDamage(UStat<double> newVal);
	void SetWeaponRange(UStat<double> newVal);

	virtual void Equip(ALivingEntity* entity);
	virtual void UnEquip(ALivingEntity* entity);

	bool IsEquiped();
	void SetEquiped(bool newVal);

	PartEnums::PartType GetBodyPart();
	void SetBodyPart(PartEnums::PartType newVal);
	bool IsTwoHanded();
	void SetTwoHanded(bool newVal);

private:
	UStat<double> weaponDamage = *new UStat<double>(100, "Damage");
	UStat<double> weaponRange = *new UStat<double>(200, "Range");
	TEnumAsByte<PartEnums::PartType> bodyPart = PartEnums::Chest;
	bool twoHanded = false;
};