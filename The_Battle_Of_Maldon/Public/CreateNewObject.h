// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "CreateNewObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THE_BATTLE_OF_MALDON_API UCreateNewObject : public UEdGraphNode
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject"), Category = Create)
	static UObject* NewObjectFromBlueprint(UObject* WorldContextObject, TSubclassOf<UObject> UC);
	
	
};
