///////////////////////////////////////////////////////////
//  Inventory.cpp
//  Implementation of the Class Inventory
//  Created on:      27-Apr-2015 19:57:37
//  Original author: sam
///////////////////////////////////////////////////////////

#include "The_Battle_of_Maldon.h"
#include "Inventory.h"


Inventory::Inventory(){

}


TArray<AItem*> Inventory::GetItems(){
	return items;
}


void Inventory::SetItems(TArray<AItem*> newVal){
	items = newVal;
}


void Inventory::AddItem(AItem* itemToAdd){
	GetItems().Add(itemToAdd);
}