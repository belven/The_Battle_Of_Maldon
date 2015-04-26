#pragma once

//#include "UserWidget.h"
//#include "ChoiceResponse.generated.h"
#include "Array.h"
#include "UnrealString.h"

class UConversationChoice;

//UCLASS()
class THE_BATTLE_OF_MALDON_API UChoiceResponse //: public UUserWidget
{
	//GENERATED_BODY()
public:
	UChoiceResponse(FString text);
	virtual ~UChoiceResponse();

	TArray<UConversationChoice*> GetChoices();
	void SetChoices(TArray<UConversationChoice*> newVal);
	FString GetText();
	void SetText(FString newVal);
	void AddChoice(UConversationChoice* choice);

private:
	TArray<UConversationChoice*> choices;
	FString text;
};
