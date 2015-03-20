#pragma once

#include "Supply.h"
#include "SupplyData.generated.h"

USTRUCT(BlueprintType)
struct FSupplyData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
	TEnumAsByte<SuppliesEnums::SupplyType> currentSupplyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
		int32 amount;
	
};