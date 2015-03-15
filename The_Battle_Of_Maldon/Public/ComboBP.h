//UENUM(BlueprintType)
//namespace CombatEnums
//{
//	enum CombatType
//	{
//		Attack,
//		Defense,
//		Other
//	};
//}

#pragma once

#include "Object.h"
#include "The_Battle_of_Maldon.h"
#include "ComboBP.generated.h"

/**
 *
 */
UCLASS()
class AComboBP : public AActor
{
	GENERATED_BODY()

public:
	AComboBP();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		float ComboDamageScaling;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		float ComboDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		TArray<AComboBP*> ComboList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		FString ComboButton;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combo)
	//	TEnumAsByte<CombatEnums::CombatType> currentCombatActionType;

};
