UENUM(BlueprintType)
namespace EntityEnums
{
	enum EntityType
	{
		Living UMETA(DisplayName = "Living Entity"),
		Non_Living UMETA(DisplayName = "Non Living Entity"),
		Person UMETA(DisplayName = "Person"),
		Creature UMETA(DisplayName = "Creature")
	};
}
#pragma once

#include "GameFramework/Character.h"
#include "Action.h"
#include "EventReceiver.h"
#include "EventSource.h"
#include "Entity.generated.h"

UCLASS()
class AEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AEntity();
	UPROPERTY(VisibleAnywhere, Category = EntityType)
	TEnumAsByte<EntityEnums::EntityType> CurrentEntityType;

	Action* CurrentAction;
	EventSource source = *new EventSource();
	EventReceiver* receiver = new EventReceiver();
};
