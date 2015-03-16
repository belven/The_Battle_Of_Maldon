

#pragma once

#include "Object.h"
#include "ComboBP.h"
#include "Array.h"
#include "UnrealString.h"
#include "CombosBP.generated.h"


/**
 *
 */
UCLASS()
class ACombosBP : public AActor
{
	GENERATED_BODY()

public:
	ACombosBP();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		AComboBP* OriganalCombo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ComboStuff)
		AComboBP* CurrentCombo;

	//public:
	//	int CombosID;
	//	float LastDamage;
	//	int HitCounter;
	//
	//public:
	//	bool lastComboSucsessfull;
	//	void StopCombo();
	//	bool IsWithinCombo(FString* BInput);
	//	bool IsWithinOriginalCombo(FString* BInput);
	//	float ComboButtonPressed(FString BInput, float WeaponDamage);
	//	void SetNextCombo(AComboBP* nextCombo);
	//	void CalculateDamage(float WeaponDamage);
};
