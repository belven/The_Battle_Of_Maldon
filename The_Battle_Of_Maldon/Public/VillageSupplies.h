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
#include "VillageSupplies.generated.h"

/**
 *
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AVillageSupplies : public AItem
{
	GENERATED_BODY()

public:
	AVillageSupplies(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VillageSupplyType)
		TEnumAsByte<VillageSuppliesEnums::VillageSupplyType> currentVillageSupplyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VillageSupplies)
		int32 amount;
};
