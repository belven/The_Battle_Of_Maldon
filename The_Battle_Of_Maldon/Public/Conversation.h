#pragma once
#include "UnrealString.h"
#include "ChoiceResponse.h"
#include "Array.h"

class THE_BATTLE_OF_MALDON_API UConversation
{
private:
	UChoiceResponse* startingResponse;
	UChoiceResponse* currentResponse;
	UChoiceResponse* lastResponse;
public:
	UConversation(UChoiceResponse* newVal);

	TArray<UConversationChoice*> GetCurrentChoices();

	void SetStartingResponse(UChoiceResponse* newVal);
	void SetCurrentResponse(UChoiceResponse* newVal);
	void SetLastResponse(UChoiceResponse* newVal);

	UChoiceResponse* GetLastResponse();
	UChoiceResponse* GetCurrentResponse();
	UChoiceResponse* GetStartingResponse();

	void SelectChoice(int choiceIndex);
	void ResetConversation();
};