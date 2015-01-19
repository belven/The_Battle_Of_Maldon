// Fill out your copyright notice in the Description page of Project Settings.

UENUM(BlueprintType)
namespace VillageSuppliesEnums
{
	enum VillageSupplyType
	{
		Wood,
		Iron,
		Wheat
	};
}

#pragma once

#include "Item.h"
#include "Supply.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API ASupply : public AItem
{
	GENERATED_BODY()

public:
	ASupply(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VillageSupplyType)
	TEnumAsByte<VillageSuppliesEnums::VillageSupplyType> currentVillageSupplyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VillageSupplies)
		int32 amount;	
};
