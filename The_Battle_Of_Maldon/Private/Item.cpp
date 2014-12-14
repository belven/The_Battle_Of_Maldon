

#include "The_Battle_of_Maldon.h"
#include "Item.h"


AItem::AItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentItemType = ItemEnumns::Other;
	Name = "Test";
}


