// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "VillageVolume.h"
#include "Merchant.h"

void AVillageVolume::ReceiveActorBeginOverlap(AActor* OtherActor) {
	ABaseVolume::ReceiveActorBeginOverlap(OtherActor);
}

void AVillageVolume::ReceiveActorEndOverlap(AActor* OtherActor) {
	ABaseVolume::ReceiveActorEndOverlap(OtherActor);
}

/*Checks to see if this village has any supplies*/
bool AVillageVolume::villageHasSupplies() {
	return  supplies.Num() > 0;
}

/*Removes the supplies from the village, will also hide the mesh of the supplies*/
AVillageSupplies* AVillageVolume::takeSupplies(AVillageSupplies* suppliesToTake){
	if (supplies.Contains(suppliesToTake)){
		suppliesToTake->SetActorHiddenInGame(true);
		supplies.Remove(suppliesToTake);
		return suppliesToTake;
	}
	return NULL;
}

/*Adds the supplies from the village, will also show the mesh of the supplies*/
AVillageSupplies* AVillageVolume::giveSupplies(AVillageSupplies* suppliesToGive){
	suppliesToGive->SetActorHiddenInGame(false);
	AVillageSupplies* supply = getSupplies(suppliesToGive->currentVillageSupplyType);

	if (supply){
		supply->amount += suppliesToGive->amount;
	}
	else {
		supplies.Add(suppliesToGive);
	}
	return suppliesToGive;
}

AVillageSupplies* AVillageVolume::getSupplies(VillageSuppliesEnums::VillageSupplyType type){
	for (AVillageSupplies* supply : supplies){
		if (supply->currentVillageSupplyType == type){
			return supply;
		}
	}

	return NULL;
}

void AVillageVolume::BeginPlay(){
	TArray<AActor*> actors;
	GetOverlappingActors(actors, AActor::StaticClass());
	UClass* aClass;

	for (AActor* actor : actors){
		aClass = actor->GetClass();

		if (aClass->IsChildOf(AVillageSupplies::StaticClass())){
			AVillageSupplies* tempSupplies = Cast<AVillageSupplies>(actor);
			supplies.Add(tempSupplies);
		}
		else if (aClass->IsChildOf(AMerchant::StaticClass())){
			AMerchant* tempLivingEntity = Cast<AMerchant>(actor);
			tempLivingEntity->setVillage(this);
		}
	}
}

TArray<ALivingEntity*> AVillageVolume::GetAlliesInVillage(){
	TArray<ALivingEntity*> allies;
	FString message = "";

	for (ALivingEntity* le : currentEntities){
		if (le->clan.Equals(clan)){
			allies.Add(le);
			message += le->entityName + ", ";
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, message);
	return allies;
}

TArray<ALivingEntity*> AVillageVolume::GetEnimiesInVillage(){
	TArray<ALivingEntity*> enimies;
	FString message = "";

	for (ALivingEntity* le : currentEntities){
		if (!le->clan.Equals(clan)){
			enimies.Add(le);
			message += le->entityName + ", ";
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, message);
	return enimies;
}
