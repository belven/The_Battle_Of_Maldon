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
class AMyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyAIController(const FObjectInitializer& ObjectInitializer);
	ALivingEntity* Bot;
	ALivingEntity* findNearestEnemyLivingEntity();
	AActor* target;
	AActor* currentRouteObject;

	int getWeaponDamage(ALivingEntity* targetToCheck);

	float ComboButtonPressed(FString BInput, float WeaponDamage);

	bool isAI;
	bool canMove;
	bool canAttack;
	bool isTargetInSightRange();
	bool isTargetInAttackRange(AActor* tempTarget);
	bool livingEntityIsWithinPatrolRange(ALivingEntity* le);
	bool isTargetPerfomingADefensiveAction(ALivingEntity* tempTarget);
	bool isTargetPerfomingAnAttackAction(ALivingEntity* tempTarget);

	FString buttonPressed();

	virtual void Possess(class APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)  override;
	virtual void Tick(float DeltaTime) override;

	void lookForTarget();
	void setNextRouteObject();
	void setAction(Combo* currentCombo);
	void goToNextPathObject();
	void moveToTarget(AActor* tempTarget);
	void attackAgain();
	void attackTarget(FString ButtonPressed, AActor* attackTarget);
	void reactToDefensiveAction();
	void reactToAttackAction();
	void performCombo(Combo* currentCombo);
};
