// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "ResourceNode.h"
#include "ResourceVolume.h"

AResourceVolume::AResourceVolume() : Super(){
	supplyType = SuppliesEnums::All;
}

AResourceVolume::AResourceVolume(SuppliesEnums::SupplyType type) : Super(){
	supplyType = type;
}

/*Sets up the supplies and merchants within a village, makes it eaiser to set up within the UE*/
void AResourceVolume::BeginPlay(){
	TArray<AActor*> actors;
	GetOverlappingActors(actors, AActor::StaticClass());
	UClass* aClass;

	for (AActor* actor : actors){
		aClass = actor->GetClass();

		if (aClass->IsChildOf(AResourceNode::StaticClass())){
			AResourceNode* tempSupplies = Cast<AResourceNode>(actor);

			if (supplyType == SuppliesEnums::All || tempSupplies->currentSupplyType == supplyType){
				resources.Add(tempSupplies);
			}
		}
	}
}

bool AResourceVolume::hasReources() {
	for (AResourceNode* resource : resources){
		if (resource->amount > 0){
			return true;
		}
	}
	return false;
}

