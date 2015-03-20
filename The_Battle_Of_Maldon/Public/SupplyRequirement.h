// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SupplyData.h"
#include "SupplyRequirement.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct THE_BATTLE_OF_MALDON_API FSupplyRequirement : public FSupplyData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
	int32 value;
	
	
};
