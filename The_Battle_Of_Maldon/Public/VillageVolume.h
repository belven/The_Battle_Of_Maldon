// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVolume.h"
#include "UnrealString.h"
#include "Supply.h"
#include "SupplyRequirement.h"
#include "VillageVolume.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(SuppliesGivenEvent, ASupply*);

UCLASS(Blueprintable, BlueprintType)
class THE_BATTLE_OF_MALDON_API AVillageVolume : public ABaseVolume
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clan)
		FString clan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
		FString name;

	TArray<ALivingEntity*> GetAlliesInVillage();
	TArray<ALivingEntity*> GetEnimiesInVillage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
	TArray<ASupply*> supplies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
	TArray<FSupplyRequirement> supplyRequirements;

	bool villageHasSupplies();

	TArray<FSupplyRequirement> getVillageSupplyRequirements();

	ASupply* takeSupplies(ASupply* suppliesToTake);
	ASupply* takeSupplies(FSupplyRequirement suppliesToTake);
	ASupply* giveSupplies(ASupply* suppliesToGive);
	ASupply* getSupplies(SuppliesEnums::SupplyType type);


	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	virtual void ReceiveActorEndOverlap(AActor* OtherActor) override;
	virtual void BeginPlay() override;

	FSupplyRequirement getRequirement(SuppliesEnums::SupplyType type);
	FSupplyRequirement getSupplyRequirement(SuppliesEnums::SupplyType type);
	FSupplyRequirement getFirstRequirementThatWeCanSupply(AVillageVolume* otherVillage);

	//UPROPERTY(BlueprintAssignable, Category = "Events")
		//SuppliesGivenEvent OnSuppliesGivenEvent;
};
