#include "The_Battle_of_Maldon.h"

APerson::APerson()
: Super()
{
	CurrentEntityType = EntityEnums::Person;
	CurrentAggressionType = LivingEntityEnums::Passive;
	SetBody(*new PersonBody());

}