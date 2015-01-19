#pragma once
#include "The_Battle_of_Maldon.h"
#include "Weapon.generated.h"

UCLASS()
class AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float weaponDamage;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		float weaponRange;
};