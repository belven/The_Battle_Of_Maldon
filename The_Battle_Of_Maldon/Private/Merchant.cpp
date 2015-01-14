// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "The_Battle_Of_Maldon.h"
#include "MerchantAIController.h"
#include "Merchant.h"



AMerchant::AMerchant(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	AIControllerClass = AMerchantAIController::StaticClass();
}

/*Returns the mechants home village from the controller*/
AVillageVolume* AMerchant::GetVillage(){
	return Cast<AMerchantAIController>(GetController()) ? Cast<AMerchantAIController>(GetController())->currentVillage : NULL;
}

/*Sets the AMerchantAIControllers' village*/
void AMerchant::setVillage(AVillageVolume* inVillage){
	if (AIControllerClass == AMerchantAIController::StaticClass()){
		AMerchantAIController* con = Cast<AMerchantAIController>(GetController());
		con->currentVillage = inVillage;
	}
}

