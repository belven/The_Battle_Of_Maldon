// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Person.h"
#include "Merchant.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AMerchant : public APerson
{
	GENERATED_BODY()
public:
	AMerchant(const FObjectInitializer& ObjectInitializer);	
	void setVillage(AVillageVolume* inVillage);
	TArray<AVillageSupplies*> supplies;
	AVillageVolume* GetVillage();
};
