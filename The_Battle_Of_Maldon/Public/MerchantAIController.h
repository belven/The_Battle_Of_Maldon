// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "VillageVolume.h"
#include "Merchant.h"
#include "MerchantAIController.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AMerchantAIController : public AMyAIController
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
	AVillageVolume* currentVillage;
	AVillageSupplies* targetSupplies;
	bool mechantHasSupplies();
	
};
