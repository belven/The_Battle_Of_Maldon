#pragma once
#include "The_Battle_of_Maldon.h"
#include "ChoiceResponse.h"
#include "Conversation.h"
#include "ConversationChoice.h"


UConversation::UConversation(UChoiceResponse* newVal)
{
	SetStartingResponse(newVal);
	SetCurrentResponse(newVal);
}


UChoiceResponse* UConversation::GetStartingResponse(){
	return startingResponse;
}


void UConversation::SetStartingResponse(UChoiceResponse* newVal){
	startingResponse = newVal;
}


UChoiceResponse* UConversation::GetCurrentResponse(){
	return currentResponse;
}


void UConversation::SetCurrentResponse(UChoiceResponse* newVal){
	currentResponse = newVal;
}


TArray<UConversationChoice*> UConversation::GetCurrentChoices(){
	return currentResponse != NULL ? currentResponse->GetChoices() : *new TArray<UConversationChoice*>();
}


UChoiceResponse* UConversation::GetLastResponse(){
	return lastResponse;
}


void UConversation::SetLastResponse(UChoiceResponse* newVal){
	lastResponse = newVal;
}


void UConversation::SelectChoice(int choiceIndex){
	lastResponse = GetCurrentResponse();

	if (GetCurrentChoices().Num() >=  choiceIndex + 1){
		UChoiceResponse* response = GetCurrentChoices()[(choiceIndex)]->GetResponse();
		SetCurrentResponse(response);
	}
}


void UConversation::ResetConversation(){
	SetCurrentResponse(GetStartingResponse());
}