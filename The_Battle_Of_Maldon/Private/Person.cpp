#include "The_Battle_of_Maldon.h"


APerson::APerson(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Person;
	CurrentAggressionType = LivingEntityEnums::Passive;

}

