// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "ResourceVolume.h"
#include "Gatherer.h"
#include "GathererAIController.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AGathererAIController : public AMyAIController
{
	GENERATED_BODY()
public:
	void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)  override;

	AResourceVolume* targetResource;
	AResourceNode* targetResourceNode;
	void goToNearestResource();
	void pickUpResources();
	void giveSuppliesToTargetVillage();
	AGatherer* getGatherer();
	bool gathererHasResources();
};
