///////////////////////////////////////////////////////////
//  Inventory.h
//  Implementation of the Class Inventory
//  Created on:      27-Apr-2015 19:57:37
//  Original author: sam
///////////////////////////////////////////////////////////

#pragma once
#include "Array.h"
#include "Item.h"

class Inventory
{

public:
	Inventory();

	TArray<AItem*> GetItems();
	void SetItems(TArray<AItem*> newVal);
	void AddItem(AItem* itemToAdd);

private:
	TArray<AItem*> items;

};
