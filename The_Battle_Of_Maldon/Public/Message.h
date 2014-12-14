#pragma once
#include "Array.h"
#include "LivingEntity.h"
#include "Quest.h"
#include "UnrealString.h"

class Message
{

public:
	Message(FString tempNPCReplyMessage, FString tempPlayerRelpyMessage)
	{
		npcReplyMessage = tempNPCReplyMessage;
		playerRelpyMessage = tempPlayerRelpyMessage;
	}

	FString npcReplyMessage;
	FString playerRelpyMessage;
	bool npcReplied = false;
	Quest* questGiven;

	TArray<Message*> PlayerReplies;

	/*
		Adds a Message to the PlayerReplies rather than doing 
		Message->PlayerReplies.Add();
	*/
	void Add(Message* MessageToAdd)
	{
		PlayerReplies.Add(MessageToAdd);
	}

	/*
	Adds an array of Message(s) to the PlayerReplies rather than doing
	Message->PlayerReplies.Add();
	*/
	void Add(TArray<Message*> MessagesToAdd)
	{
		for (int i = 0; i < MessagesToAdd.Num(); i++)
		{
			PlayerReplies.Add(MessagesToAdd[i]);
		}
	}

	/*
		Resets the npcReplied bool to allow for re-use
	*/
	void Reset()
	{
		npcReplied = false;
	}

	TArray<FString> playerReplies()
	{
		TArray<FString> tempReplies;

		for (int i = 0; i < PlayerReplies.Num(); i++)
		{
			tempReplies.Add(PlayerReplies[i]->playerRelpyMessage);
		}

		return tempReplies;
	}
		

	/*
		Checks if this is the end of a conversation, 
		i.e the player has no more possible choices
	*/
	bool IsEnd()
	{
		return PlayerReplies.Num() <= 0;
	}
};