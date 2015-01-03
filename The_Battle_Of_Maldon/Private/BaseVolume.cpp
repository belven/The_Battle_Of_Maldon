// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "BaseVolume.h"

void ABaseVolume::BeginPlay() {

}

void ABaseVolume::ReceiveActorBeginOverlap(AActor* OtherActor) {
	ALivingEntity* le = Cast<ALivingEntity>(OtherActor);
	if (le) {
		currentEntities.Add(le);
	}
}

void ABaseVolume::EntitiesDetails(){
	

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::FromInt(currentEntities.Num()));

	/*for (ALivingEntity* le : currentEntities){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, le->entityName);
	}*/
}

void ABaseVolume::ReceiveActorEndOverlap(AActor* OtherActor) {
	ALivingEntity* le = Cast<ALivingEntity>(OtherActor);
	if (le) {
		currentEntities.Remove(le);
	}
}