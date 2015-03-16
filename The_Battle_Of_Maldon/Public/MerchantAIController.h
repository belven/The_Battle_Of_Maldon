// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Supply.h"
#include "Merchant.h"
#include "VillageVolume.h"
#include "VillagerAIController.h"
#include "MerchantAIController.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AMerchantAIController : public AVillagerAIController
{
	GENERATED_BODY()
public:
	void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)  override;

	void goToNearestVillage();
	void pickUpVillageSupplies();
	void giveSuppliesToTargetVillage();
	AMerchant* getMerchant();	
	AVillageVolume* targetVillage;
	ASupply* targetSupplies;
	bool mechantHasSupplies();
	
};
