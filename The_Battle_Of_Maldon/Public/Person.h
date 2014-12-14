
#pragma once

#include "LivingEntity.h"
#include "Person.generated.h"

/**
 *
 */
UCLASS()
class APerson : public ALivingEntity
{
	GENERATED_BODY()
public:
	APerson(const FObjectInitializer& ObjectInitializer);

	 //void AttachRootComponentToActor(AActor* InParentActor, FName InSocketName = NAME_None, EAttachLocation::Type AttachLocationType = EAttachLocation::KeepRelativeOffset) OVERRIDE;
	 //void AttachRootComponentTo(class USceneComponent* InParent, FName InSocketName = NAME_None, EAttachLocation::Type AttachLocationType = EAttachLocation::KeepRelativeOffset) OVERRIDE;
};
