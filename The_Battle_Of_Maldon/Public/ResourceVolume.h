// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVolume.h"
#include "ResourceNode.h"
#include "ResourceVolume.generated.h"

/**
 *
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AResourceVolume : public ABaseVolume
{
	GENERATED_BODY()
public:
	AResourceVolume();
	AResourceVolume(SuppliesEnums::SupplyType type);
	virtual void BeginPlay() override;
	TArray<AResourceNode*> resources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
		TEnumAsByte<SuppliesEnums::SupplyType> supplyType;

	bool hasReources();
};
