#pragma once

#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "LivingEntity.h"
#include "Person.h"
#include "UnrealString.h"
#include "Combo.h"
#include "AIController.h"
#include "MyAIController.generated.h"

UCLASS()
class THE_BATTLE_OF_MALDON_API AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController(const FObjectInitializer& ObjectInitializer);
	ALivingEntity* Bot;
	AActor* target;
	AActor* currentRouteObject;	

	bool isAI;
	bool canMove;
	bool isTargetInSightRange();
	bool isTargetInAttackRange(AActor* tempTarget);
	bool livingEntityIsWithinPatrolRange(ALivingEntity* le);
	
	virtual void Possess(class APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)  override;
	virtual void Tick(float DeltaTime) override;

	void lookForTarget();
	void setNextRouteObject();
	void goToNextPathObject();
	void moveToTarget(AActor* tempTarget);
};
