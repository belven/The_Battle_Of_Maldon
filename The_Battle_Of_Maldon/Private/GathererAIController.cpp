// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "GathererAIController.h"
#include "ResourceVolume.h"

/*Runs every frame and makes sure the mechant is always doing something*/
void AGathererAIController::Tick(float DeltaTime)
{
	//The controller has a bot, and the bot can move
	if (Bot && getGatherer() && canMove)
	{
		if (gathererHasResources() && getGatherer()->village){
			moveToTarget(getGatherer()->village);
		}
		else {
			goToNearestResource();
		}
	}
}

/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AGathererAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	canMove = true;

	if (gathererHasResources()) {
		giveSuppliesToTargetVillage();
	}
	else if (targetResourceNode) {
		pickUpResources();
	}
}

void AGathererAIController::goToNearestResource() {
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* actor = *It;

		if (actor->GetClass()->IsChildOf(AResourceVolume::StaticClass())){
			AResourceVolume* tempResource = Cast<AResourceVolume>(*It);

			//Did we find a resource and is it not the same as our current resource
			if (tempResource && tempResource->supplyType == getGatherer()->supplyType)
			{
				//If we find they have supplies then target them, 
				//This needs to be a check to see if they have the same type, if so move to and add to them 
				if (tempResource->hasReources()) {
					for (AResourceNode* resourceNode : tempResource->resources){
						if (resourceNode->amount > 0){
							targetResourceNode = resourceNode;
							targetResource = tempResource;

							//Move towards the resource node
							moveToTarget(targetResourceNode);
							break;
						}
					}

					break;
				}
			}
		}
	}
}

void AGathererAIController::pickUpResources() {
	if (targetResourceNode) {
		int amountToTake = targetResourceNode->amount;

		FActorSpawnParameters Parameters;
		Parameters.Template = targetResourceNode;
		Parameters.bNoFail = true;
		//Parameters.Owner = getGatherer();

		ASupply* newResource = GetWorld()->SpawnActor<ASupply>(ASupply::StaticClass(), Parameters);
		//newResource->amount = targetResourceNode->amount;
		//newResource->currentSupplyType = targetResourceNode->currentSupplyType;
		newResource->SetActorHiddenInGame(false);
		getGatherer()->resources.Add(newResource);
		targetResourceNode->takeResources(amountToTake);
	}
}

void AGathererAIController::giveSuppliesToTargetVillage() {
	FVector tempLoc = getGatherer()->GetActorLocation();
	tempLoc.X += 10;
	tempLoc.Z += 10;

	getGatherer()->resources[0]->SetActorLocation(tempLoc);
	getGatherer()->resources.Remove(getGatherer()->village->giveSupplies(getGatherer()->resources[0]));
}

bool AGathererAIController::gathererHasResources() {
	return getGatherer()->resources.Num() > 0;
}

/*Returns the bot as a Gatherer*/
AGatherer* AGathererAIController::getGatherer() {
	return Cast<AGatherer>(Bot);
}