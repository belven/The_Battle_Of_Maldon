#pragma once
#include "Item.h"
#include "Weapon.generated.h"

UCLASS()
class AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float weaponDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float weaponRange;
};