#pragma once
#include "Damage.generated.h"

USTRUCT(BlueprintType)
struct FDamage
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
		double damageDone = 0;

};