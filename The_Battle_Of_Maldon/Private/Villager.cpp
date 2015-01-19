// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "The_Battle_of_Maldon.h"


AVillager::AVillager(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//AIControllerClass = AMerchantAIController::StaticClass();
}


/*Returns the mechants home village from the controller*/
AVillageVolume* AVillager::GetVillage(){
	return village;
}

/*Sets the AMerchantAIControllers' village*/
void AVillager::setVillage(AVillageVolume* inVillage){
	village = inVillage;
}