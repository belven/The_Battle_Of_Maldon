// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"


UMessageBP::UMessageBP(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){


}

TArray<FString> UMessageBP::getPlayerReplies(){
	TArray<FString> tempReplies;

	for (int i = 0; i < PlayerReplies.Num(); i++)
	{
		tempReplies.Add(PlayerReplies[i]->playerRelpyMessage);
	}

	return tempReplies;
}

UMessageBP* UMessageBP::GetMessageBP(FString inNpcReplyMessage, FString inPlayerRelpyMessage, TArray<UMessageBP*> playerReplies)
{
	UMessageBP* tempMessage = Cast<UMessageBP>(StaticConstructObject(UMessageBP::GetClass()));
	tempMessage->npcReplyMessage = inNpcReplyMessage;
	tempMessage->playerRelpyMessage = inPlayerRelpyMessage;
	tempMessage->PlayerReplies = playerReplies;
	return tempMessage;
}

bool UMessageBP::IsEnd()
{
	return PlayerReplies.Num() <= 0;
}


