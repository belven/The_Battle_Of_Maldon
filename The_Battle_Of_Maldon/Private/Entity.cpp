#include "The_Battle_of_Maldon.h"



AEntity::AEntity() : Super()
{
	CurrentEntityType = EntityEnums::Non_Living;
	GetCharacterMovement()->bUseRVOAvoidance = true;
	receiver.hookEvent(&source);
}
