#pragma once
#include "Array.h"
#include "LivingEntity.h"
#include "Message.h"
#include "UnrealString.h"

class Conversation
{

public:
	Conversation(Message* con)
	{
		currentMessage = con;
	}
	
	bool HasRemainingMessages()
	{
		return currentMessage ? !currentMessage->IsEnd() : false;
	}

	/**
		Returns a list of messages to send the player

		@parma Index The index of the messages last displayed, starting at 1
	*/
	TArray<FString> SetNextMessages(int Index)
	{
		TArray<FString> messagesToSend;
		
		//If we aren't at the end of the conversation then move to the message at the players choosen index
		if (HasRemainingMessages())
		{
			messagesToSend.Add(currentMessage->npcReplyMessage);

			for (FString message : currentMessage->playerReplies()){

				messagesToSend.Add(message);
			}
			currentMessage = GoToConversation(Index);
		}
		
		return messagesToSend;
	}

private:
	Message* currentMessage;

	/**
		Returns the message at the index choosen by the player,
		the player inputs 1 - 4 so it's message at index -1
		@parma Index The index of the messages last displayed, starting at 1
		*/
	Message* GoToConversation(int Index)
	{
		if (currentMessage->PlayerReplies.Num() >= Index)
		{
			return currentMessage->PlayerReplies[Index - 1];
		}
		return NULL;
	}
};