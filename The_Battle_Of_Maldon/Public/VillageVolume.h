// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseVolume.h"
#include "UnrealString.h"
#include "Supply.h"
#include "SupplyRequirement.h"
#include "VillageVolume.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuppliesGivenEvent, ASupply*, supply);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuppliesTakenEvent, ASupply*, supply);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllyEnterEvent, ALivingEntity*, entity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAllyLeaveEvent, ALivingEntity*, entity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyEnterEvent, ALivingEntity*, entity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnemyLeaveEvent, ALivingEntity*, entity);

UCLASS(Blueprintable, BlueprintType)
class THE_BATTLE_OF_MALDON_API AVillageVolume : public ABaseVolume
{
	GENERATED_BODY()

private:
	TArray<ALivingEntity*> allies = *new TArray<ALivingEntity*>();
	TArray<ALivingEntity*> enemies = *new TArray<ALivingEntity*>();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clan)
		FString clan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Name)
		FString name;

	TArray<ALivingEntity*> GetAlliesInVillage();
	TArray<ALivingEntity*> GetEnimiesInVillage();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
		TArray<ASupply*> supplies = *new TArray<ASupply*>();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Supplies)
		TArray<FSupplyRequirement> supplyRequirements = *new TArray<FSupplyRequirement>();

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

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSuppliesGivenEvent OnSuppliesGivenEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FSuppliesTakenEvent OnSuppliesTakenEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FAllyEnterEvent OnAllyEnterEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FAllyLeaveEvent OnAllyLeaveEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FEnemyEnterEvent OnEnemyEnterEvent;

	UPROPERTY(BlueprintAssignable, Category = "Events")
		FEnemyLeaveEvent OnEnemyLeaveEvent;
};
