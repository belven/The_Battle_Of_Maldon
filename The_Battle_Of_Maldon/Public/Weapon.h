#pragma once
#include "Item.h"
#include "Stat.h"
#include "Equipable.h"
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

	void SetWeaponDamage(Stat newVal);
	void SetWeaponRange(Stat newVal);

	virtual void Equip(ALivingEntity entity);

	bool IsEquiped();
	void SetEquiped(bool newVal);

private:
	Stat weaponDamage = *new Stat(10);
	Stat weaponRange = *new Stat(200);
};