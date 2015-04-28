
namespace ItemEnumns
{
	enum ItemType
	{
		Weapon,
		Armor,
		Supply,
		Other
	};
}

#pragma once

#include "UnrealString.h"
#include "Item.generated.h"

/**
 *
 */
UCLASS()
class AItem : public APawn
{
	GENERATED_BODY()


public:
	AItem();
	ItemEnumns::ItemType CurrentItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Temp)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Temp)
		TArray<FName> SocketsToAttachTo = *new TArray<FName>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMesh* ItemMesh;
};
