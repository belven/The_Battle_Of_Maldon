// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyAIController.h"
#include "CombatAIController.generated.h"


/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API ACombatAIController : public AMyAIController
{
	GENERATED_BODY()
public:
	ACombatAIController(const FObjectInitializer& ObjectInitializer);
	bool canAttack; 

	int getWeaponDamage(ALivingEntity* targetToCheck);

	float ComboButtonPressed(FString BInput, float WeaponDamage);

	bool isTargetPerfomingADefensiveAction(ALivingEntity* tempTarget);
	bool isTargetPerfomingAnAttackAction(ALivingEntity* tempTarget);
	bool isTargetInAttackRange(AActor* tempTarget);
	bool isTargetInSightRange();

	FString buttonPressed();

	void attackAgain();
	void attackTarget(FString ButtonPressed, AActor* attackTarget);
	void reactToDefensiveAction();
	void reactToAttackAction();
	void performCombo(Combo* currentCombo);
	void lookForTarget();
	void setAction(Combo* currentCombo);

	void Tick(float DeltaTime) override;
	virtual void Possess(class APawn* InPawn) override;


	ALivingEntity* findNearestEnemyLivingEntity();
};
