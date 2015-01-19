// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"


/*This class is used by a village and mechant to hold supplies they might need*/
ASupply::ASupply(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	amount = 100;
	currentVillageSupplyType = VillageSuppliesEnums::Wood;
}

