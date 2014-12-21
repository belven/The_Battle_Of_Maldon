#include "The_Battle_of_Maldon.h"
#include "CombatAIController.h"
#include "LivingEntity.h"
#include "Engine.h"
#include <iostream>
#include <string>

ALivingEntity::ALivingEntity(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Living;
	AIControllerClass = ACombatAIController::StaticClass();
	EntityCombos = new Combos(this);
	health = 1000000000000;
	entityName = "Test";
	clan = "2";
	attackDamage = 20;
	currentHealth = health;
	rollDistance = 400;
	rollVelocity = 300;

	Message* start = new Message("NPC: Hello", "");
	Message* middle = new Message("NPC: " + entityName, "Player: Whats your name?");
	Message* middle2 = new Message("NPC: Hello?", "Player: What did you say again?");
	Message* end = new Message("NPC: Cya", "Player: ok, Bye");

	start->Add(middle);
	middle2->Add(end);

	middle->Add(end);
	middle->Add(middle2);
	startingMessage = start;
}

void ALivingEntity::CheckEffects(double deltaTime){
	for (Effect* e : currentEffects) {
		if (e->ShouldApply(deltaTime))	{
			e->ApplyEffect();
			e->lastTimeRan = deltaTime;
			e->EffectApplied();

			if (e->EffectExpired(deltaTime)) {
				e->Expired();
				currentEffects.Remove(e);
			}
		}
	}
}

bool ALivingEntity::HasEffect(Effect* newE) {
	for (Effect* e : currentEffects) {
		if (e->id.Equals(newE->id)){
			return true;
		}
	}
	return false;
}

void ALivingEntity::GiveEffect(Effect* newE) {
	if (!newE->stacks) {
		for (Effect* e : currentEffects) {
			if (e->id.Equals(newE->id) && e->Score() < newE->Score()){
				e = newE;
			}
		}
	}
	else {
		currentEffects.Add(newE);
	}
}

void ALivingEntity::Dodge(DodgeEnums::DodgeDirection dodgeDirection = DodgeEnums::Backwards)
{
	switch (dodgeDirection)
	{
	case DodgeEnums::Left:
		RollLeft();
		break;
	case DodgeEnums::Right:
		RollRight();
		break;
	case DodgeEnums::Forwards:
		RollForwards();
		break;
	case DodgeEnums::Backwards:
		RollBackwards();
		break;
	default:
		RollBackwards();
		break;
	}
}

void ALivingEntity::SetStopComboTimer(float ComboDelay){
	ClearStopComboTimer();
	GetWorldTimerManager().SetTimer(this, &ALivingEntity::StopCombo, ComboDelay);
}

void ALivingEntity::ClearStopComboTimer(){
	GetWorldTimerManager().ClearTimer(this, &ALivingEntity::StopCombo);
}

void ALivingEntity::StopCombo()
{
	EntityCombos->StopCombo();
}

void ALivingEntity::AddItemToInventory(AItem* itemToAdd)
{
	Inventory.Add(itemToAdd);
	FName itemSocket;

	if (itemToAdd->SocketsToAttachTo.Num() > 0)
	{
		itemSocket = itemToAdd->SocketsToAttachTo[0];
		AttachItemToSocket(itemToAdd, itemToAdd->SocketsToAttachTo[0]);
	}
	else
	{
		itemSocket = NAME_None;
	}
}

void ALivingEntity::AttachItemToSocket(AItem* itemToAdd, FName socketName){
	itemToAdd->AttachRootComponentToActor(itemToAdd, socketName);
}


void ALivingEntity::RollLeft()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		const FVector ForwardDir = GetActorRightVector();
		const FVector AddForce = (ForwardDir * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity;

		GetController()->StopMovement();
		LaunchCharacter(AddForce, true, true);

		DefenseAction* tempDefenseAction = new DefenseAction();
		CurrentAction = tempDefenseAction;
	}
}

void ALivingEntity::RollRight()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		const FVector ForwardDir = GetActorRightVector();
		const FVector AddForce = (ForwardDir * rollDistance) + FVector(0, 0, 1) * rollVelocity;

		GetController()->StopMovement();
		LaunchCharacter(AddForce, true, true);

		DefenseAction* tempDefenseAction = new DefenseAction();
		CurrentAction = tempDefenseAction;
	}
}

void ALivingEntity::RollBackwards()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		const FVector ForwardDir = GetActorForwardVector();
		const FVector AddForce = (ForwardDir * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity;

		GetController()->StopMovement();
		LaunchCharacter(AddForce, true, true);

		DefenseAction* tempDefenseAction = new DefenseAction();
		CurrentAction = tempDefenseAction;
	}
}

void ALivingEntity::RollForwards()
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		const FVector ForwardDir = GetActorForwardVector();
		const FVector AddForce = (ForwardDir * rollDistance) + FVector(0, 0, 1) * rollVelocity;

		GetController()->StopMovement();
		LaunchCharacter(AddForce, true, true);

		DefenseAction* tempDefenseAction = new DefenseAction();
		CurrentAction = tempDefenseAction;
	}
}

void ALivingEntity::TakeDamage(Damage* damage)
{
	if (__raise source.LivingEntityTakeDamageEvent(damage))
	{
		if ((currentHealth - damage->damageDone) > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::SanitizeFloat(damage->damageDone) + " damage dealt to " + entityName);
			currentHealth -= damage->damageDone;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, entityName + " was killed!!!");
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::SanitizeFloat(currentHealth - Damage) +  " overkill damage!!");
			Destroy();
		}
	}
}