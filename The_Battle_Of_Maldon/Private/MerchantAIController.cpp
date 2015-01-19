// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "The_Battle_Of_Maldon.h"

/*Runs every frame and makes sure the mechant is always doing something*/
void AMerchantAIController::Tick(float DeltaTime)
{
	//The controller has a bot, and the bot can move
	if (Bot && canMove)
	{
		//Do we have supplies 
		if (mechantHasSupplies()){
			//We have supplies so go to trade with another village
			goToNearestVillage();
		}
		else {
			//We have no suplies so go and pick some up
			pickUpVillageSupplies();
		}
	}
}

/*Makes the merchant give his supplies to his target village*/
void AMerchantAIController::giveSuppliesToTargetVillage(){
	FVector tempLoc = getMerchant()->GetActorLocation();
	tempLoc.X += 10;
	tempLoc.Z += 10;

	getMerchant()->supplies[0]->SetActorLocation(tempLoc);
	getMerchant()->supplies.Remove(targetVillage->giveSupplies(getMerchant()->supplies[0]));
}

/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AMerchantAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	canMove = true;

	//We have no supplies, therefore we have just moved towards some to pickup
	if (!mechantHasSupplies() && targetSupplies && getMerchant()->GetVillage()){
		getMerchant()->supplies.Add(getMerchant()->GetVillage()->takeSupplies(targetSupplies));
		targetSupplies = NULL;
	}
	//We have supplies therefore we must have reached a village or it's supplies
	else if (mechantHasSupplies() && targetVillage){
		giveSuppliesToTargetVillage();
	}
}

/*Moves the bot to the first supplies found within the bots starting village*/
void AMerchantAIController::pickUpVillageSupplies()
{
	//Do we have a village, and does it have supplies
	if (getMerchant()->GetVillage() && getMerchant()->GetVillage()->villageHasSupplies()){

		//Move towards the villages supplies
		moveToTarget(getMerchant()->GetVillage()->supplies[0]);
		targetSupplies = getMerchant()->GetVillage()->supplies[0];
	}
}

/*Checks to see if the bot has any supplies*/
bool AMerchantAIController::mechantHasSupplies(){
	return getMerchant() ? getMerchant()->supplies.Num() > 0 : false;
}

/*Returns the bot as a merchant*/
AMerchant* AMerchantAIController::getMerchant(){
	return Cast<AMerchant>(Bot);
}

/*
Iterrates over all actors and checks if they are a village.
If this is the case then we check if it's not the same village as the one we're in and move towards it.
*/
void AMerchantAIController::goToNearestVillage(){
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AVillageVolume* tempVillage = Cast<AVillageVolume>(*It);

		//Did we find a village and is it not the same as our current village
		if (tempVillage  && getMerchant()->GetVillage() != tempVillage)
		{
			//Move towards the village
			moveToTarget(tempVillage);

			//If we find they have supplies then target them, 
			//This needs to be a check to see if they have the same type, if so move to and add to them 
			//Overwise put them within the village supplies area
			if (tempVillage->villageHasSupplies()){
				targetSupplies = tempVillage->supplies[0];
			}

			targetVillage = tempVillage;
		}
	}
}