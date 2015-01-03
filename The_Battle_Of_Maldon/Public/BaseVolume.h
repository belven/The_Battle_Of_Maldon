// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Volume.h"
#include "LivingEntity.h"
#include "Array.h"
#include "Engine.h"
#include "BaseVolume.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API ABaseVolume : public AVolume
{
	GENERATED_BODY()

public:
	//FActorBeginOverlapSignature OnActorBeginOverlap;

	TArray<ALivingEntity*> currentEntities;
	virtual void BeginPlay() override;
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	virtual void ReceiveActorEndOverlap(AActor* OtherActor) override;
	void EntitiesDetails();
};
