
namespace ItemEnumns
{
	enum ItemType
	{
		Weapon,
		Armor,
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
	AItem(const FObjectInitializer& ObjectInitializer);

	ItemEnumns::ItemType CurrentItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Temp)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Temp)
		TArray<FName> SocketsToAttachTo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
		USkeletalMesh* ItemMesh;
};
