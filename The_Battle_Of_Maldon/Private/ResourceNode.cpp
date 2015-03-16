// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "ResourceNode.h"

AResourceNode::AResourceNode() : Super(){
	amount = 100;
}

AResourceNode::AResourceNode(SuppliesEnums::SupplyType type) : Super(type) {
	amount = 100;
	currentSupplyType = type;
}

void AResourceNode::takeResources(int amountToTake){
	amount -= amountToTake;

	if (amount <= 0){
		SetActorHiddenInGame(true);
	}
}