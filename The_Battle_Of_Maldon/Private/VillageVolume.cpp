// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "The_Battle_of_Maldon.h"

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

/*Returns the villages supplies of that particular supply type, if it has any*/
AVillageSupplies* AVillageVolume::getSupplies(VillageSuppliesEnums::VillageSupplyType type){
	for (AVillageSupplies* supply : supplies){
		if (supply->currentVillageSupplyType == type){
			return supply;
		}
	}

	return NULL;
}

/*Sets up the supplies and merchants within a village, makes it eaiser to set up within the UE*/
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
		else if (aClass->IsChildOf(AVillager::StaticClass())){
			AVillager* tempLivingEntity = Cast<AVillager>(actor);
			tempLivingEntity->setVillage(this);
		}
	}
}

/*Returns a list of all the villages allies, i.e. bots with the same clan*/
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

/*Returns a list of all the villages enimies, i.e. bots not in the same clan*/
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

