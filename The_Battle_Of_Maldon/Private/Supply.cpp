// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"

/*This class is used by a village and mechant to hold supplies they might need*/
ASupply::ASupply() {
	amount = 100;
	currentSupplyType = SuppliesEnums::Wood;
}

/*This class is used by a village and mechant to hold supplies they might need*/
ASupply::ASupply(SuppliesEnums::SupplyType type) {
	amount = 100;
	currentSupplyType = type;
}




