#include "The_Battle_of_Maldon.h"
#include "Entity.h"


AEntity::AEntity(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Non_Living;
	GetCharacterMovement()->bUseRVOAvoidance = true;
	receiver.hookEvent(&source);
}


