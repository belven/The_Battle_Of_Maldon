#include "The_Battle_of_Maldon.h"


ACreature::ACreature(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Creature;
}


