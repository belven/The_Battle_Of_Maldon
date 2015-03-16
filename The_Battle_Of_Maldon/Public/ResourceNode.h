// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Supply.h"
#include "Supply.h"
#include "ResourceNode.generated.h"

/**
 *
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AResourceNode : public ASupply
{
	GENERATED_BODY()
public:
	AResourceNode();
	AResourceNode(SuppliesEnums::SupplyType type);
	void takeResources(int amountToTake);

};
