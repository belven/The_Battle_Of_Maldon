///////////////////////////////////////////////////////////
//  ChoiceResponse.cpp
//  Implementation of the Class ChoiceResponse
//  Created on:      26-Apr-2015 11:05:25
//  Original author: sam
///////////////////////////////////////////////////////////

#include "The_Battle_Of_Maldon.h"
#include "ChoiceResponse.h"
#include "ConversationChoice.h"



UChoiceResponse::UChoiceResponse(FString text){
	SetText(text);
}

UChoiceResponse::~UChoiceResponse(){

}


TArray<UConversationChoice*> UChoiceResponse::GetChoices(){
	return choices;
}


void UChoiceResponse::SetChoices(TArray<UConversationChoice*> newVal){
	choices = newVal;
}


FString UChoiceResponse::GetText(){
	return text;
}


void UChoiceResponse::SetText(FString newVal){
	text = newVal;
}


void UChoiceResponse::AddChoice(UConversationChoice* choice){
	choices.Add(choice);
}