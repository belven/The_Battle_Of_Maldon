// Fill out your copyright notice in the Description page of Project Settings.

UENUM(BlueprintType)
namespace SuppliesEnums
{
	enum SupplyType
	{
		Wood,
		Iron,
		Wheat,
		All
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
	ASupply();
	ASupply(SuppliesEnums::SupplyType type);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SupplyType)
		TEnumAsByte<SuppliesEnums::SupplyType> currentSupplyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
		int32 amount;	

	
};
