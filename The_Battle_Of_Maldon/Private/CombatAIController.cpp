// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "CombatAIController.h"
#include "Combo.h"
#include "Damage.h"
#include "DefenseAction.h"
#include "AttackAction.h"
#include "Engine.h"
#include <iostream>
#include <string>

ACombatAIController::ACombatAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("ACombatAIController start"));
	canAttack = true;
	//std::cout << "Test 1";
	UE_LOG(LogTemp, Warning, TEXT("ACombatAIController end"));
}


void ACombatAIController::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("ACombatAIController Tick"));
	AAIController::Tick(DeltaTime);

	if (Bot && isAI)
	{
		UE_LOG(LogTemp, Warning, TEXT("is Bot & isAI"));
		lookForTarget();
	}
	UE_LOG(LogTemp, Warning, TEXT("ACombatAIController Tick end"));
}

void ACombatAIController::Possess(APawn* InPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Possess"));
	Super::Possess(InPawn);
	canAttack = true;
	UE_LOG(LogTemp, Warning, TEXT("Possess end"));
}

void ACombatAIController::lookForTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("lookForTarget start"));
	//Check if there is anything within the bots patrol range otherwise move towards next RouteObject

	if (!Bot->CurrentAggressionType == LivingEntityEnums::Passive)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentAggressionType"));
		ALivingEntity* tempTarget = findNearestEnemyLivingEntity();

		if (livingEntityIsWithinPatrolRange(tempTarget))
		{
			UE_LOG(LogTemp, Warning, TEXT("livingEntityIsWithinPatrolRange"));
			//If the target isn't close enough move towards it
			if (!isTargetInAttackRange(tempTarget))
			{
				UE_LOG(LogTemp, Warning, TEXT("isTargetInAttackRange"));
				moveToTarget(tempTarget);
				UE_LOG(LogTemp, Warning, TEXT("isTargetInAttackRange end"));
			}
			else if (canAttack)
			{
				UE_LOG(LogTemp, Warning, TEXT("canAttack"));
				StopMovement();
				attackTarget(buttonPressed(), tempTarget);
			}

			target = tempTarget;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("goToNextPathObject"));
			goToNextPathObject();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("goToNextPathObject 2"));
		goToNextPathObject();
	}
	UE_LOG(LogTemp, Warning, TEXT("lookForTarget end"));
}

/*This will find all ALivingEntities within the world and choose the closest one that is it's enemy*/
ALivingEntity* ACombatAIController::findNearestEnemyLivingEntity()
{
	UE_LOG(LogTemp, Warning, TEXT("findNearestEnemyLivingEntity start"));
	TArray<ALivingEntity*> EntitiesFound;
	ALivingEntity* tempPawn = NULL;
	float lastDistanceTo = 0;
	float currentDistanceTo = 0;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		ALivingEntity* TestPawn = Cast<ALivingEntity>(*It);

		if (TestPawn && Bot != TestPawn && TestPawn->clan != Bot->clan && TestPawn->health > 0)	//&& isTargetInSightRange())
		{
			EntitiesFound.Add(TestPawn);
		}
	}

	for (ALivingEntity* le : EntitiesFound)
	{
		currentDistanceTo = Bot->GetDistanceTo(le);

		if (tempPawn != NULL && currentDistanceTo < lastDistanceTo)
		{
			lastDistanceTo = currentDistanceTo;
			tempPawn = le;
		}
		else if (tempPawn == NULL)
		{
			lastDistanceTo = currentDistanceTo;
			tempPawn = le;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("findNearestEnemyLivingEntity end"));

	return tempPawn;
}

#pragma region Combat

/*If the owner of this controller has pressed the right button and isn't in the air, then they will run the approprite animation and set the damage to do*/
void ACombatAIController::attackTarget(FString ButtonPressed, AActor* attackTarget)
{
	UE_LOG(LogTemp, Warning, TEXT("attackTarget"));
	if (canAttack && Bot && attackTarget && !Bot->GetCharacterMovement()->IsFalling() && !Bot->GetCharacterMovement()->IsFlying())
	{
		ALivingEntity* tempTarget = (ALivingEntity*)attackTarget;
		ACombatAIController* tempCon = (ACombatAIController*)tempTarget->GetController();;

		//Get the next damage to.
		float damageDone = ComboButtonPressed(ButtonPressed, getWeaponDamage(Bot));

		if (tempTarget && Bot->EntityCombos->lastComboSucsessfull)
		{
			UE_LOG(LogTemp, Warning, TEXT("lastComboSucsessfull"));
			//Is the target perfomring an action, then react to action, removed for players as they control thier own defenses 
			if (isAI && tempTarget->CurrentAction)
			{
				if (isTargetPerfomingADefensiveAction(tempTarget))
				{
					reactToDefensiveAction();
				}
				else if (isTargetPerfomingAnAttackAction(tempTarget) && tempCon->target == Bot)
				{
					reactToAttackAction();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("performCombo"));
					performCombo(Bot->EntityCombos->CurrentCombo);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("performCombo 2"));
				performCombo(Bot->EntityCombos->CurrentCombo);
			}
		}
	}
}

float ACombatAIController::ComboButtonPressed(FString BInput, float WeaponDamage)
{
	UE_LOG(LogTemp, Warning, TEXT("ComboButtonPressed start"));
	Combos* combos = Bot->EntityCombos;
	/*if (ItemOwner != NULL && CustomAnimNode == NULL)
	{
	CustomAnimNode = AnimNodePlayCustomAnim(ItemOwner.Mesh.FindAnimNode(AnimNode));
	}*/

	if (combos->IsWithinCombo(&BInput))
	{
		UE_LOG(LogTemp, Warning, TEXT("IsWithinCombo"));
		//Run combo animation
		/*if (CustomAnimNode != NULL)
		{
		CustomAnimNode.PlayCustomAnim(tempCurrentCombo->ComboAnim, 1.0);
		}*/

		Bot->SetStopComboTimer(combos->CurrentCombo->ComboDelay);
		combos->lastComboSucsessfull = true;
		combos->CalculateDamage(WeaponDamage);
	}
	else if (combos->IsWithinOriginalCombo(&BInput))
	{
		UE_LOG(LogTemp, Warning, TEXT("IsWithinOriginalCombo"));
		Bot->SetStopComboTimer(combos->CurrentCombo->ComboDelay);
		combos->lastComboSucsessfull = true;
		combos->CalculateDamage(WeaponDamage);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ComboButtonPressed else"));
		Bot->ClearStopComboTimer();
		combos->StopCombo();
		combos->lastComboSucsessfull = false;
	}

	if (combos->CurrentCombo->ComboList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ComboButtonPressed StopCombo"));
		combos->StopCombo();
	}

	UE_LOG(LogTemp, Warning, TEXT("ComboButtonPressed end"));
	return combos->LastDamage;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void ACombatAIController::reactToDefensiveAction()
{
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, 1.5f);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + "s' attack was blocked");
	Bot->EntityCombos->StopCombo();
	canAttack = false;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void ACombatAIController::reactToAttackAction()
{
	Bot->Dodge(DodgeEnums::Backwards);
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, 1);
	canAttack = false;
}

/*Will return unreals LineOfSightTo() on the current target*/
bool ACombatAIController::isTargetInSightRange()
{
	if (target)
	{
		FVector eyeLoc;
		FRotator eyeRotation;
		Bot->GetActorEyesViewPoint(eyeLoc, eyeRotation);
		return LineOfSightTo(target, eyeLoc);
	}
	else
	{
		return false;
	}
}

/*This will check the targets distance from the pawns currently held weapon*/
bool ACombatAIController::isTargetInAttackRange(AActor* tempTarget)
{
	float DistSq = Bot->GetDistanceTo(tempTarget);
	float attackRange = 200;
	APerson* tempBot = (APerson*)Bot;

	if (Bot->CurrentEntityType == EntityEnums::Person)
	{
		if (tempBot && tempBot->Weapon)
		{
			attackRange = tempBot->Weapon->weaponRange;
		}
	}

	return (DistSq <= attackRange);
}

/*This is to be used with timers in order to allow the bot to attack again*/
void ACombatAIController::attackAgain()
{
	UE_LOG(LogTemp, Warning, TEXT("attackAgain start"));
	ALivingEntity* tempTarget = (ALivingEntity*)target;
	Damage* damage = new Damage(Bot->EntityCombos->LastDamage);
	if (tempTarget)	tempTarget->TakeDamage(damage);
	UE_LOG(LogTemp, Warning, TEXT("TakeDamage"));

	Bot->CurrentAction = NULL;

	if (Bot->entityName == "Player")
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " can attack again");
	}

	canAttack = true;
	UE_LOG(LogTemp, Warning, TEXT("attackAgain end"));
}

/*Sets the Bots action, and sets the dely on the attack and canAttack to false*/
void ACombatAIController::performCombo(Combo* currentCombo)
{
	UE_LOG(LogTemp, Warning, TEXT("performCombo start"));
	setAction(currentCombo);
	float Delay = currentCombo ? currentCombo->ComboDelay : 1;
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, (Delay - 0.5) > 0 ? Delay - 0.5 : 1);
	canAttack = false;
	UE_LOG(LogTemp, Warning, TEXT("performCombo end"));
}

/*This will controll all the variables that Bot->CurrentAction should have*/
void ACombatAIController::setAction(Combo* currentCombo)
{
	//Determin the the type of attack we shall perform
	if (currentCombo->CurrentCombatActionType == CombatEnums::Attack)
	{
		AttackAction* tempAttackAction = new AttackAction();
		tempAttackAction->AttackCombo = currentCombo;

		if (__raise Bot->source.AttackActionEvent(tempAttackAction))
		{
			Bot->CurrentAction = tempAttackAction;
		}
	}
	else if (currentCombo->CurrentCombatActionType == CombatEnums::Defense)
	{
		DefenseAction* tempDefenseAction = new DefenseAction();
		tempDefenseAction->AttackCombo = currentCombo;
		Bot->CurrentAction = tempDefenseAction;
	}
}

/*Returns the passed in LivingEntities weawpon damage*/
int ACombatAIController::getWeaponDamage(ALivingEntity* targetToCheck)
{
	if (targetToCheck && targetToCheck->Weapon)
	{
		return targetToCheck->Weapon->weaponDamage;
	}
	return 10;
}

/*Checks to see if the target is Attacking*/
bool ACombatAIController::isTargetPerfomingAnAttackAction(ALivingEntity* tempTarget)
{
	CombatAction* tempAction = (CombatAction*)tempTarget->CurrentAction;

	//Is the target attacking us
	return  (tempAction && tempAction->CurrentCombatActionType == CombatEnums::Attack);
}

/*Checks to see if the target is Block/Evading*/
bool ACombatAIController::isTargetPerfomingADefensiveAction(ALivingEntity* tempTarget)
{
	//Is the target in combat
	if (tempTarget->CurrentAction->CurrentActionType == ActionEnums::Combat)
	{
		CombatAction* tempAction = (CombatAction*)tempTarget->CurrentAction;

		//Are they performing a defensive action.
		return (tempAction->CurrentCombatActionType == CombatEnums::Defense);
	}
	return false;
}

/*Returns a random string from attackButtons*/
FString ACombatAIController::buttonPressed()
{
	int index = 0;
	TArray<Combo*> comboList = Bot->EntityCombos->CurrentCombo->ComboList;

	if (comboList.Num() > 0){
		index = rand() % comboList.Num();
		if (index < 0) index = 0;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " just pressed " + comboList[index]->ComboButton);
		return comboList[index]->ComboButton;
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " just pressed " + Bot->EntityCombos->OriganalCombo->ComboButton);
		return Bot->EntityCombos->OriganalCombo->ComboButton;
	}
}

#pragma endregion
