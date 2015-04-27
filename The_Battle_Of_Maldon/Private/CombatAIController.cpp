// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "Engine.h"
//DEFINE_LOG_CATEGORY(CombatCombos);
//DEFINE_LOG_CATEGORY(CombatDecisions);

ACombatAIController::ACombatAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	canAttack = true;
}

/*Runs each frame to make sure bots are always doing something*/
void ACombatAIController::Tick(float DeltaTime)
{
	AAIController::Tick(DeltaTime);

	if (Bot && isAI)
	{
		lookForTarget();
	}
}

/*Runs once the controller is being used by a pawn*/
void ACombatAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	canAttack = true;
}

/*Looks for actors that the bot can go towards and possibly attack*/
void ACombatAIController::lookForTarget()
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

/*This will find all ALivingEntities within the world and choose the closest one that is it's enemy*/
ALivingEntity* ACombatAIController::findNearestEnemyLivingEntity()
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

	for (TArray<ALivingEntity*>::TConstIterator it = EntitiesFound.CreateConstIterator(); it; it++){
		ALivingEntity* le = (ALivingEntity*)*it;
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

#pragma region Combat

/*If the owner of this controller has pressed the right button and isn't in the air, then they will run the approprite animation and set the damage to do*/
void ACombatAIController::attackTarget(FString ButtonPressed, AActor* attackTarget)
{
	if (canAttack && Bot && attackTarget && !Bot->GetCharacterMovement()->IsFalling() && !Bot->GetCharacterMovement()->IsFlying())
	{
		ALivingEntity* tempTarget = (ALivingEntity*)attackTarget;
		ACombatAIController* tempCon = (ACombatAIController*)tempTarget->GetController();;

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
				//Check to see if the target is attacking and wether we have started attacking
				//This will need to include some level of intelligence as the hit counter check determines how far into a ccombo we are
				else if (isTargetPerfomingAnAttackAction(tempTarget) && Bot->EntityCombos->hitCounter == 0 && tempCon->target == Bot)
				{
					reactToAttackAction();
				}
				else
				{
					performCombo(Bot->EntityCombos->currentCombo);
				}
			}
			else
			{
				performCombo(Bot->EntityCombos->currentCombo);
			}
		}
	}
}

/*Extracted from entityCombos, this is designed to control the combo system by checking button presses against a list of possile combos*/
float ACombatAIController::ComboButtonPressed(FString BInput, float WeaponDamage)
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

		Bot->SetStopComboTimer(combos->currentCombo->ComboDelay);
		combos->lastComboSucsessfull = true;
		combos->CalculateDamage(WeaponDamage);
	}
	else if (combos->IsWithinOriginalCombo(&BInput))
	{
		Bot->SetStopComboTimer(combos->currentCombo->ComboDelay);
		combos->lastComboSucsessfull = true;
		combos->CalculateDamage(WeaponDamage);
	}
	else
	{
		Bot->ClearStopComboTimer();
		combos->StopCombo();
		combos->lastComboSucsessfull = false;
	}

	if (combos->currentCombo->ComboList.Num() == 0)
	{
		Bot->ClearStopComboTimer();
		combos->StopCombo();
	}

	return combos->lastDamage;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void ACombatAIController::reactToDefensiveAction()
{
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, 1.5f);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + "s' attack was blocked");
	Bot->EntityCombos->StopCombo();
	canAttack = false;
}

/*This will eventually control Reaction animations and strength of force of the hit*/
void ACombatAIController::reactToAttackAction()
{
	Bot->Dodge(DodgeEnums::Backwards);
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, 1.5f);
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
			attackRange = tempBot->Weapon->GetWeaponRange();
		}
	}

	return (DistSq <= attackRange);
}

/*This is to be used with timers in order to allow the bot to attack again*/
void ACombatAIController::attackAgain()
{
	ALivingEntity* tempTarget = (ALivingEntity*)target;
	LivingEntityDamage* damage = new LivingEntityDamage(Bot, tempTarget, Bot->EntityCombos->lastDamage);
	if (tempTarget)	tempTarget->InflictDamage(damage);

	Bot->CurrentAction = NULL;

	if (Bot->entityName == "Player")
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, Bot->entityName + " can attack again");
	}

	canAttack = true;
}

/*Sets the Bots action, and sets the dely on the attack and canAttack to false*/
void ACombatAIController::performCombo(Combo* currentCombo)
{
	ALivingEntity* tempTarget = (ALivingEntity*)target;
	if (tempTarget && currentCombo->effect) {
		tempTarget->GiveEffect(currentCombo->effect);
	}

	setAction(currentCombo);
	float delay = currentCombo ? currentCombo->ComboDelay - 0.4 : 1;
	GetWorldTimerManager().SetTimer(this, &ACombatAIController::attackAgain, delay > 0 ? delay : 1);
	canAttack = false;
}

/*This will controll all the variables that Bot->CurrentAction should have*/
void ACombatAIController::setAction(Combo* currentCombo)
{
	//Determin the the type of attack we shall perform
	if (currentCombo->currentCombatActionType == CombatEnums::Attack)
	{
		AttackAction* tempAttackAction = new AttackAction();
		tempAttackAction->AttackCombo = currentCombo;

		if (__raise Bot->source.AttackActionEvent(tempAttackAction))
		{
			Bot->CurrentAction = tempAttackAction;
		}
	}
	else if (currentCombo->currentCombatActionType == CombatEnums::Defense)
	{
		DefenseAction* tempDefenseAction = new DefenseAction();
		Bot->CurrentAction = tempDefenseAction;
	}
}

/*Returns the passed in LivingEntities weawpon damage*/
double ACombatAIController::getWeaponDamage(ALivingEntity* targetToCheck)
{
	if (targetToCheck && targetToCheck->Weapon)
	{
		return targetToCheck->Weapon->GetWeaponDamage();
	}
	return Bot->attackDamage;
}

/*Checks to see if the target is Attacking*/
bool ACombatAIController::isTargetPerfomingAnAttackAction(ALivingEntity* tempTarget)
{
	CombatAction* tempAction = (CombatAction*)tempTarget->CurrentAction;

	//Is the target attacking us
	return  (tempAction && tempAction->currentCombatActionType == CombatEnums::Attack);
}

/*Checks to see if the target is Block/Evading*/
bool ACombatAIController::isTargetPerfomingADefensiveAction(ALivingEntity* tempTarget)
{
	//Is the target in combat
	if (tempTarget->CurrentAction->CurrentActionType == ActionEnums::Combat)
	{
		CombatAction* tempAction = (CombatAction*)tempTarget->CurrentAction;

		//Are they performing a defensive action.
		return (tempAction->currentCombatActionType == CombatEnums::Defense && ((DefenseAction*)tempAction)->currentDefenseType == DefenseEnums::Block);
	}
	return false;
}

/*Returns a random string from attackButtons*/
FString ACombatAIController::buttonPressed()
{
	int index = 0;
	TArray<Combo*> comboList = Bot->EntityCombos->currentCombo->ComboList;

	if (comboList.Num() > 0){
		FString text = Bot->entityName + " just pressed " + comboList[index]->ComboButton;
		index = rand() % comboList.Num();
		if (index == comboList.Num()) index--;

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, text);
		UE_LOG(LogTemp, Log, TEXT("%s"), *text);
		return comboList[index]->ComboButton;
	}

	return "";
}

#pragma endregion
