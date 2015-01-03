// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVolume.h"
#include "UnrealString.h"
#include "VillageSupplies.h"
#include "VillageVolume.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class THE_BATTLE_OF_MALDON_API AVillageVolume : public ABaseVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clan)
	FString clan;

	TArray<ALivingEntity*> GetAlliesInVillage();
	TArray<ALivingEntity*> GetEnimiesInVillage();
	TArray<AVillageSupplies*> supplies;

	bool villageHasSupplies();
	AVillageSupplies* takeSupplies(AVillageSupplies* suppliesToTake);
	AVillageSupplies* giveSupplies(AVillageSupplies* suppliesToGive);
	AVillageSupplies* getSupplies(VillageSuppliesEnums::VillageSupplyType type);
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	virtual void ReceiveActorEndOverlap(AActor* OtherActor) override;
	virtual void BeginPlay() override;
};
