// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVolume.h"
#include "UnrealString.h"
#include "Supply.h"
#include "SupplyRequirement.h"
#include "VillageVolume.generated.h"

UCLASS(Blueprintable, BlueprintType)
class THE_BATTLE_OF_MALDON_API AVillageVolume : public ABaseVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clan)
		FString clan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
		FString name;

	TArray<ALivingEntity*> GetAlliesInVillage();
	TArray<ALivingEntity*> GetEnimiesInVillage();
	TArray<ASupply*> supplies;
	TArray<ASupplyRequirement*> supplyRequirements;

	bool villageHasSupplies();
	ASupply* takeSupplies(ASupply* suppliesToTake);
	ASupply* giveSupplies(ASupply* suppliesToGive);
	ASupply* getSupplies(SuppliesEnums::SupplyType type);
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	virtual void ReceiveActorEndOverlap(AActor* OtherActor) override;
	virtual void BeginPlay() override;
};
