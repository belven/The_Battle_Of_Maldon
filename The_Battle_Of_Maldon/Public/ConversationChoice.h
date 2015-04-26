
#pragma once
//#include "UserWidget.h"
//#include "ConversationChoice.generated.h"
#include "UnrealString.h"

class UChoiceResponse;

//UCLASS()
class THE_BATTLE_OF_MALDON_API UConversationChoice //: public UUserWidget
{
	//GENERATED_BODY()
private:
	virtual ~UConversationChoice();
	UChoiceResponse* response;
	FString text;
public:
	UConversationChoice(FString text);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Message)
	UChoiceResponse* GetResponse();
	void SetResponse(UChoiceResponse* newVal);
	FString GetText();
	void SetText(FString newVal);
	
};
