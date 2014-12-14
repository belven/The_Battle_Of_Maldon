#include "The_Battle_of_Maldon.h"
#include "Creature.h"


ACreature::ACreature(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Creature;
}


