// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "UnrealString.h"
#include "MessageBP.generated.h"

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class THE_BATTLE_OF_MALDON_API UMessageBP : public UObject
{
	GENERATED_BODY()

public:
	/*UFUNCTION(BlueprintCallable, Category = "Messages")
		UMessageBP(const FObjectInitializer& ObjectInitializer);*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		FString npcReplyMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		FString playerRelpyMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		TArray<UMessageBP*> PlayerReplies;

	UFUNCTION(BlueprintCallable, Category = "Messages")
		TArray<FString> getPlayerReplies();

	UFUNCTION(BlueprintCallable, Category = "Messages")
		bool IsEnd();
};
