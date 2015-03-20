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
	return supplies.Num() > 0;
}

/*Removes the supplies from the village, will also hide the mesh of the supplies*/
ASupply* AVillageVolume::takeSupplies(FSupplyRequirement suppliesToTake){
	ASupply* supply = getSupplies(suppliesToTake.currentSupplyType);

	if (supply){	
		if (supply->amount > suppliesToTake.amount){
			supply->amount -= suppliesToTake.amount;
			supply = GetWorld()->SpawnActor<ASupply>(ASupply::StaticClass());
			supply->amount = suppliesToTake.amount;
			supply->currentSupplyType = suppliesToTake.currentSupplyType;
		}
		else {
			supply->SetActorHiddenInGame(true);
			supplies.Remove(supply);
		}
		return supply;
	}
	return NULL;
}

/*Removes the supplies from the village, will also hide the mesh of the supplies*/
ASupply* AVillageVolume::takeSupplies(ASupply* suppliesToTake){
	if (supplies.Contains(suppliesToTake)){
		suppliesToTake->SetActorHiddenInGame(true);
		suppliesToTake->SetActorEnableCollision(true);
		supplies.Remove(suppliesToTake);
		return suppliesToTake;
	}
	return NULL;
}

/*Adds the supplies from the village, will also show the mesh of the supplies*/
ASupply* AVillageVolume::giveSupplies(ASupply* suppliesToGive){
	suppliesToGive->SetActorHiddenInGame(false);
	suppliesToGive->SetActorEnableCollision(true);
	ASupply* supply = getSupplies(suppliesToGive->currentSupplyType);

	if (supply) {
		supply->amount += suppliesToGive->amount;
	}
	else {
		supplies.Add(suppliesToGive);
	}

	//OnSuppliesGivenEvent.Broadcast(suppliesToGive);
	return suppliesToGive;
}

/*Returns the villages supplies of that particular supply type, if it has any*/
ASupply* AVillageVolume::getSupplies(SuppliesEnums::SupplyType type){
	for (ASupply* supply : supplies){
		if (supply->currentSupplyType == type){
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

		if (aClass->IsChildOf(ASupply::StaticClass())){
			ASupply* tempSupplies = Cast<ASupply>(actor);
			supplies.Add(tempSupplies);
		}
		else if (aClass->IsChildOf(AVillager::StaticClass())){
			AVillager* tempLivingEntity = Cast<AVillager>(actor);
			tempLivingEntity->setVillage(this);
		}
	}
}

FSupplyRequirement AVillageVolume::getRequirement(SuppliesEnums::SupplyType type){
	FSupplyRequirement temp;
	temp.amount = 0;
	temp.currentSupplyType = type;

	for (FSupplyRequirement requirement : supplyRequirements){
		if (requirement.currentSupplyType == type){
			return requirement;
		}
	}
	return temp;
}


FSupplyRequirement AVillageVolume::getSupplyRequirement(SuppliesEnums::SupplyType type){
	FSupplyRequirement tempRequirement;
	tempRequirement.currentSupplyType = SuppliesEnums::All;
	tempRequirement.amount = 0;

	for (FSupplyRequirement requirement : supplyRequirements){
		if (requirement.currentSupplyType == type){
			return requirement;
		}
	}
	return tempRequirement;
}

FSupplyRequirement AVillageVolume::getFirstRequirementThatWeCanSupply(AVillageVolume* otherVillage){
	FSupplyRequirement tempRequirement;
	tempRequirement.currentSupplyType = SuppliesEnums::All;
	tempRequirement.amount = 0;

	//Check each of our villages requirements
	for (FSupplyRequirement requirement : otherVillage->getVillageSupplyRequirements()){

		//Get the amount of supplies the village has that ours requires
		ASupply* supply = getSupplies(requirement.currentSupplyType);

		//Get the amount of that item that the other village requires
		FSupplyRequirement otherRequirement = getRequirement(requirement.currentSupplyType);

		//Do they have more supplies than they need of that type
		if (supply && supply->amount > 0 && otherRequirement.amount < supply->amount){
			tempRequirement.amount = supply->amount - otherRequirement.amount;
			tempRequirement.currentSupplyType = requirement.currentSupplyType;
			return tempRequirement;
		}
	}

	return tempRequirement;
}

TArray<FSupplyRequirement> AVillageVolume::getVillageSupplyRequirements(){
	TArray<FSupplyRequirement> tempRequirements;

	for (FSupplyRequirement requirement : supplyRequirements){
		ASupply* supply = getSupplies(requirement.currentSupplyType);

		if (supply && supply->amount < requirement.amount){
			FSupplyRequirement newRequirement;
			newRequirement.currentSupplyType = requirement.currentSupplyType;
			newRequirement.amount = requirement.amount - supply->amount;

			tempRequirements.Add(newRequirement);
		}
		else if (supply == NULL){
			tempRequirements.Add(requirement);
		}
	}

	return tempRequirements;
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

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, message);
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

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, message);
	return enimies;
}

