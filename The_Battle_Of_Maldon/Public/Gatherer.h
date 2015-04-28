// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Villager.h"
#include "Supply.h"
#include "Array.h"
#include "Gatherer.generated.h"

/**
 *
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AGatherer : public AVillager
{
	GENERATED_BODY()
public:
	AGatherer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
		TArray<ASupply*> resources = *new TArray<ASupply*>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
		TEnumAsByte<SuppliesEnums::SupplyType> supplyType;



};
