// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <stdio.h>
#include "Supply.h"
#include "Merchant.h"
#include "VillageVolume.h"
#include "VillagerAIController.h"
#include "MerchantAIController.generated.h"

/**
 * 
 */

//[event_receiver(native)]
UCLASS()
class THE_BATTLE_OF_MALDON_API AMerchantAIController : public AVillagerAIController
{
	GENERATED_BODY()
public:
	void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)  override;

	void goToNearestVillage();
	void setVillageSuppliesToCollect();
	void giveSuppliesToTargetVillage();
	AMerchant* getMerchant();	
	AVillageVolume* targetVillage;
	ASupply* targetSupplies;
	bool mechantHasSupplies();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "AddItem")
	void SuppliesGivenEvent(ASupply* supply);

	TArray<AVillageVolume*> getVillages();
	FSupplyRequirement ourVillageRequirements;
	FSupplyRequirement targetVillageRequirements;

};
