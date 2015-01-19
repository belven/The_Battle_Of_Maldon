// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Villager.h"
#include "SupplyRequirement.h"
#include "Merchant.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AMerchant : public AVillager
{
	GENERATED_BODY()
public:
	AMerchant(const FObjectInitializer& ObjectInitializer);	
	TArray<AVillageSupplies*> supplies;
	TArray<ASupplyRequirement*> supplyRequirements;
};
