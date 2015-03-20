// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UserWidget.h"
#include "ConversationChoice.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API UConversationChoice : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Message)
	FString message;
	
};
