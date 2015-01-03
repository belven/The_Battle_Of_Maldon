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
	UMessageBP(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		FString npcReplyMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		FString playerRelpyMessage;

	UFUNCTION(BlueprintCallable, Category = "Messages")
		UMessageBP* GetMessageBP(FString inNpcReplyMessage, FString inPlayerRelpyMessage, TArray<UMessageBP*> playerReplies);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Messages")
		TArray<UMessageBP*> PlayerReplies;

	UFUNCTION(BlueprintCallable, Category = "Messages")
		TArray<FString> getPlayerReplies();

	UFUNCTION(BlueprintCallable, Category = "Messages")
		bool IsEnd();
};
