// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "ConversationChoice.h"
#include "ChoiceResponse.h"


UConversationChoice::UConversationChoice(FString text){
	SetText(text);
}

UConversationChoice::~UConversationChoice(){

}


UChoiceResponse* UConversationChoice::GetResponse(){
	return response;
}


void UConversationChoice::SetResponse(UChoiceResponse* newVal){
	response = newVal;
}


FString UConversationChoice::GetText(){
	return text;
}


void UConversationChoice::SetText(FString newVal){
	text = newVal;
}


