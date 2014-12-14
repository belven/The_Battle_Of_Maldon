#include "The_Battle_of_Maldon.h"
#include "Person.h"


APerson::APerson(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Person;
	CurrentAggressionType = LivingEntityEnums::Passive;

}

