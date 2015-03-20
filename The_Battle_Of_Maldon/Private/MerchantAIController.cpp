// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "The_Battle_Of_Maldon.h"

void AMerchantAIController::BeginPlay(){
	if (getMerchant()->GetVillage()){
		//getMerchant()->GetVillage()->OnSuppliesGivenEvent.BindSP(this, &AMerchantAIController::SuppliesGivenEvent);
	}
}

void AMerchantAIController::SuppliesGivenEvent(ASupply* supply){
	if (Bot && !mechantHasSupplies()){
		setVillageSuppliesToCollect();
	}
}

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
			setVillageSuppliesToCollect();
			
			//If we found supplies, move towards them
			if (targetSupplies){
				//Move towards the villages supplies
				moveToTarget(targetSupplies);
			}
		}
	}
}

/*Makes the merchant give his supplies to his target village*/
void AMerchantAIController::giveSuppliesToTargetVillage(){
	for (ASupply* supply : getMerchant()->supplies){
		//if (targetVillage->getSupplies(supply->currentSupplyType)){
		FVector tempLoc = getMerchant()->GetActorLocation();
		tempLoc.X += 10;
		tempLoc.Z += 10;
		getMerchant()->supplies[0]->SetActorLocation(tempLoc);
		//}

		getMerchant()->supplies.Remove(targetVillage->giveSupplies(supply));
	}
}

/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AMerchantAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	canMove = true;

	//We have no supplies, therefore we have just moved towards some to pickup
	if (!mechantHasSupplies() && getMerchant()->GetVillage()){
		if (targetSupplies) {
			getMerchant()->supplies.Add(getMerchant()->GetVillage()->takeSupplies(targetVillageRequirements));
			targetSupplies = NULL;
		}
		else {
			setVillageSuppliesToCollect();

			//If we found supplies, move towards them
			if (targetSupplies){
				//Move towards the villages supplies
				moveToTarget(targetSupplies);
			}
		}
	}
	//We have supplies therefore we must have reached a village or it's supplies
	else if (mechantHasSupplies() && targetVillage){
		giveSuppliesToTargetVillage();
	}
}

/*Moves the bot to the first supplies found within the bots starting village*/
void AMerchantAIController::setVillageSuppliesToCollect()
{
	//Do we have a village, and does it have supplies
	if (getMerchant()->GetVillage() && getMerchant()->GetVillage()->villageHasSupplies()){

		//Get the amount of resources our village requires

		//Check each village for supplies
		for (AVillageVolume* village : getVillages()){
			if (village != getMerchant()->GetVillage() && targetSupplies == NULL){

				//Get what the other village needs from us, that we have
				FSupplyRequirement thierRequirement = getMerchant()->GetVillage()->getFirstRequirementThatWeCanSupply(village);

				//Get what the our village needs from them, that they have
				FSupplyRequirement ourRequirement = village->getFirstRequirementThatWeCanSupply(getMerchant()->GetVillage());

				//Is there something that both villages need?
				if (thierRequirement.currentSupplyType != SuppliesEnums::All && ourRequirement.currentSupplyType != SuppliesEnums::All){
					ourVillageRequirements = ourRequirement;
					targetVillageRequirements = thierRequirement;
					targetSupplies = getMerchant()->GetVillage()->getSupplies(thierRequirement.currentSupplyType);
					break;
				}
			}
		}
	}
}

/*Checks to see if the bot has any supplies*/
bool AMerchantAIController::mechantHasSupplies(){
	if (getMerchant()){
		for (ASupply* supply : getMerchant()->supplies){
			if (supply && supply->amount > 0){
				return true;
			}
		}
	}
	return false;
}

/*Returns the bot as a merchant*/
AMerchant* AMerchantAIController::getMerchant(){
	return Cast<AMerchant>(Bot);
}

TArray<AVillageVolume*> AMerchantAIController::getVillages(){
	TArray<AVillageVolume*> tempVillages;
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* actor = *It;
		if (actor->GetClass()->IsChildOf(AVillageVolume::StaticClass())){
			AVillageVolume* tempVillage = Cast<AVillageVolume>(*It);
			tempVillages.Add(tempVillage);
		}
	}
	return tempVillages;
}

/*
Iterrates over all actors and checks if they are a village.
If this is the case then we check if it's not the same village as the one we're in and move towards it.
*/
void AMerchantAIController::goToNearestVillage(){
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* actor = *It;
		if (actor->GetClass()->IsChildOf(AVillageVolume::StaticClass())){
			AVillageVolume* tempVillage = Cast<AVillageVolume>(*It);

			//Did we find a village and is it not the same as our current village
			if (tempVillage && getMerchant()->GetVillage() != tempVillage)
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
				break;
			}
		}
	}
}