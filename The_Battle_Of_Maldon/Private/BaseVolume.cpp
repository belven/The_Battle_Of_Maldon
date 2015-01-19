// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "Engine.h"

/*Run when the game first starts*/
void ABaseVolume::BeginPlay() {

}

/*Adds living entities each time they walk into the volume
to my own collection of entities to make it easier to access*/
void ABaseVolume::ReceiveActorBeginOverlap(AActor* OtherActor) {
	ALivingEntity* le = Cast<ALivingEntity>(OtherActor);
	if (le) {
		currentEntities.Add(le);
	}
}

/*Was used to test how many entities are within the volume*/
void ABaseVolume::EntitiesDetails(){
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::FromInt(currentEntities.Num()));

	/*for (ALivingEntity* le : currentEntities){
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, le->entityName);
	}*/
}

/*Removes living entities, each time they walk out of the volume,
from my own collection of entities to make it easier to access*/
void ABaseVolume::ReceiveActorEndOverlap(AActor* OtherActor) {
	ALivingEntity* le = Cast<ALivingEntity>(OtherActor);
	if (le) {
		currentEntities.Remove(le);
	}
}