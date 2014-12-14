#include "The_Battle_of_Maldon.h"
#include "MyAIController.h"
#include "LivingEntity.h"
#include "Person.h"
#include "AttackAction.h"
#include "MoveAction.h"
#include "DefenseAction.h"
#include "DrawDebugHelpers.h"
#include "ColorList.h"
#include "Combo.h"
#include "Damage.h"
#include "Engine.h"

AMyAIController::AMyAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	canMove = true;
	canAttack = true;
	isAI = true;
}

void AMyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	Bot = Cast<ALivingEntity>(InPawn);
	canMove = true;
	canAttack = true;
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Bot)
	{
		lookForTarget();
	}
}

void AMyAIController::lookForTarget()
{
	//Check if there is anything within the bots patrol range otherwise move towards next RouteObject

	if (!Bot->CurrentAggressionType == LivingEntityEnums::Passive)
	{
		ALivingEntity* tempTarget = findNearestEnemyLivingEntity();

		if (livingEntityIsWithinPatrolRange(tempTarget))
		{
			//If the target isn't close enough move towards it
			if (!isTargetInAttackRange(tempTarget))
			{
				moveToTarget(tempTarget);
			}
			else if (canAttack)
			{
				StopMovement();
				attackTarget(buttonPressed(), tempTarget);
			}

			target = tempTarget;
		}
		else
		{
			goToNextPathObject();
		}
	}
	else
	{
		goToNextPathObject();
	}
}

#pragma region Perception

/*Check to see if both the pawn and the taraget is within the Bot->patrolRange of currentRouteObject*/
bool AMyAIController::livingEntityIsWithinPatrolRange(ALivingEntity* le)
{
	if (Bot->PathObjects.Num() > 0)
	{
		if (!currentRouteObject)
		{
			currentRouteObject = Bot->PathObjects[0];
		}

		if (le == NULL || currentRouteObject == NULL)
		{
			return false;
		}

		return (Bot->GetDistanceTo(currentRouteObject) <= Bot->patrolRange	&& le->GetDistanceTo(currentRouteObject) <= Bot->patrolRange);
	}
	else
	{
		return false;
	}
}

/*This will find all ALivingEntities within the world and choose the closest one that is it's enemy*/
ALivingEntity* AMyAIController::findNearestEnemyLivingEntity()
{
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

	return tempPawn;
}

/*Will return unreals LineOfSightTo() on the current target*/
bool AMyAIController::isTargetInSightRange()
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

#pragma endregion

#pragma region Path Objects

/*This method will set the pawn to focus and move towards the next object within it's PathObjects*/
void AMyAIController::goToNextPathObject()
{
	if (canMove)
	{
		if (currentRouteObject)
		{
			setNextRouteObject();
		}
		else if (Bot->PathObjects.Num() > 0)
		{
			currentRouteObject = Bot->PathObjects[0];
		}

		if (currentRouteObject)
		{
			moveToTarget(currentRouteObject);
			target = currentRouteObject;
		}
	}
}

/*This will set currentRouteObject to the current index in PathObjects + 1 else it will go back to the start*/
void AMyAIController::setNextRouteObject()
{
	int32 index = Bot->PathObjects.IndexOfByKey(currentRouteObject);

	if ((index + 1) >= Bot->PathObjects.Num())
	{
		currentRouteObject = Bot->PathObjects[0];
	}
	else
	{
		currentRouteObject = Bot->PathObjects[index + 1];
	}
}

#pragma endregion

#pragma region Movement

/* This will move and set the focus of the pawn to the passed in Actor but only if the pawn isn't performing another action*/
void AMyAIController::moveToTarget(AActor* tempTarget)
{
	MoveAction* ma = new MoveAction(10);

	if (__raise Bot->source.MoveActionEvent(ma) && Bot->CurrentAction == NULL)
	{
		SetFocus(tempTarget);
		MoveToActor(tempTarget);
		canMove = false;
		Bot->CurrentAction = ma;
	}
}

/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AMyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	canMove = true;

	if (Result != EPathFollowingResult::Success && target == currentRouteObject)
	{
		goToNextPathObject();
	}
}

#pragma endregion

#pragma region Combat

/*If the owner of this controller has pressed the right button and isn't in the air, then they will run the approprite animation and set the damage to do*/
void AMyAIController::attackTarget(FString ButtonPressed, AActor* attackTarget)
{
	if (canAttack && Bot && attackTarget && !Bot->GetCharacterMovement()->IsFalling() && !Bot->GetCharacterMovement()->IsFlying())
	{
		ALivingEntity* tempTarget = (ALivingEntity*)attackTarget;
		AMyAIController* tempCon = (AMyAIController*)tempTarget->GetController();;

		//Get the next damage to.
		float damageDone = ComboButtonPressed(ButtonPressed, getWeaponDamage(Bot));

		if (tempTarget && Bot->EntityCombos->lastComboSucsessfull)
		{
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
					performCombo(Bot->EntityCombos->CurrentCombo);
				}
			}
			else
			{
				performCombo(Bot->EntityCombos->CurrentCombo);
			}
		}
	}
}

float AMyAIController::ComboButtonPressed(FString BInput, float WeaponDamage)
{
	Combos* combos = Bot->EntityCombos;
	/*if (ItemOwner != NULL && CustomAnimNode == NULL)
	{
	CustomAnimNode = AnimNodePlayCustomAnim(ItemOwner.Mesh.FindAnimNode(AnimNode));
	}*/

	if (combos->IsWithinCombo(&BInput))
	{
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
		Bot->SetStopComboTimer(combos->CurrentCombo->ComboDelay);
		combos->lastComboSucsessfull = true;
		combos->CalculateDamage(WeaponDamage);
	}
	else
	{
		Bot->ClearStopComboTimer();
		combos->StopCombo();
		combos->lastComboSucsessfull = false;
	}

	if (combos->CurrentCombo->ComboList.Num() == 0)
	{
		combos->StopCombo();
	}

	return combos->LastDamage;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void AMyAIController::reactToDefensiveAction()
{
	GetWorldTimerManager().SetTimer(this, &AMyAIController::attackAgain, 1.5f);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + "s' attack was blocked");
	Bot->EntityCombos->StopCombo();
	canAttack = false;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void AMyAIController::reactToAttackAction()
{
	Bot->Dodge(DodgeEnums::Backwards);
	GetWorldTimerManager().SetTimer(this, &AMyAIController::attackAgain, 1);
	canAttack = false;
}

/*This will check the targets distance from the pawns currently held weapon*/
bool AMyAIController::isTargetInAttackRange(AActor* tempTarget)
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
void AMyAIController::attackAgain()
{
	ALivingEntity* tempTarget = (ALivingEntity*)target;
	Damage* damage = new Damage(Bot->EntityCombos->LastDamage);
	if (tempTarget)	tempTarget->TakeDamage(damage);

	Bot->CurrentAction = NULL;

	if (Bot->entityName == "Player")
	{
		//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " can attack again");
	}

	canAttack = true;
}

/*Sets the Bots action, and sets the dely on the attack and canAttack to false*/
void AMyAIController::performCombo(Combo* currentCombo)
{
	setAction(currentCombo);
	float Delay = currentCombo ? currentCombo->ComboDelay : 1;
	GetWorldTimerManager().SetTimer(this, &AMyAIController::attackAgain, Delay);
	canAttack = false;
}

/*This will controll all the variables that Bot->CurrentAction should have*/
void AMyAIController::setAction(Combo* currentCombo)
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
int AMyAIController::getWeaponDamage(ALivingEntity* targetToCheck)
{
	if (targetToCheck && targetToCheck->Weapon)
	{
		return targetToCheck->Weapon->weaponDamage;
	}
	return 10;
}

/*Checks to see if the target is Attacking*/
bool AMyAIController::isTargetPerfomingAnAttackAction(ALivingEntity* tempTarget)
{
	CombatAction* tempAction = (CombatAction*)tempTarget->CurrentAction;

	//Is the target attacking us
	return  (tempAction && tempAction->CurrentCombatActionType == CombatEnums::Attack);
}

/*Checks to see if the target is Block/Evading*/
bool AMyAIController::isTargetPerfomingADefensiveAction(ALivingEntity* tempTarget)
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
FString AMyAIController::buttonPressed()
{
	int index = 0;
	TArray<Combo*> comboList = Bot->EntityCombos->CurrentCombo->ComboList;

	if (comboList.Num() > 0){
		index = rand() % comboList.Num();
		if (index < 0) index = 0;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " just pressed " + comboList[index]->ComboButton);
		return comboList[index]->ComboButton;
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " just pressed " + Bot->EntityCombos->OriganalCombo->ComboButton);
		return Bot->EntityCombos->OriganalCombo->ComboButton;
	}
}

#pragma endregion