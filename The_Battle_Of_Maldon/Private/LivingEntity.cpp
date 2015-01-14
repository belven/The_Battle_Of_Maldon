#include "The_Battle_of_Maldon.h"
#include "CombatAIController.h"
#include "LivingEntity.h"
#include "Engine.h"
#include "HealthEffect.h"
#include "ModifierEffect.h"
#include <iostream>
#include <string>

ALivingEntity::ALivingEntity(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	CurrentEntityType = EntityEnums::Living;
	AIControllerClass = ACombatAIController::StaticClass();
	EntityCombos = new Combos(this);
	health = 1000;
	entityName = "Test";
	clan = "2";
	attackDamage = 200;
	currentHealth = health;
	rollDistance = 400;
	rollVelocity = 300;

	/*EffectStructs::HealthParams hp;
	hp.amountOfChange = 100;
	hp.positive = false;
	hp.dely = 3;
	hp.id = "Basic Damage";
	hp.stacks = false;
	hp.maxDuration = 30;

	HealthEffect* he = new HealthEffect(hp, this);
	GiveEffect(he);*/

	EffectStructs::ModifierParams mp;
	mp.id = "Damage Reduction";
	mp.dely = 9;
	mp.stacks = true;
	mp.maxDuration = 9;
	mp.positive = false;
	mp.modifier = 0.3;
	mp.modifierName = ModifierManager::defenseModiferName;

	ModifierEffect* me = new ModifierEffect(mp, this);
	GiveEffect(me);

	mp.dely = 18;
	ModifierEffect* me2 = new ModifierEffect(mp, this);
	GiveEffect(me2);

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

void ALivingEntity::Tick(float deltaTime){
	Super::Tick(deltaTime);
	CheckEffects(deltaTime);
}

void ALivingEntity::CheckEffects(float deltaTime){
	for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it != NULL; it++){
		Effect* e = (Effect*)*it;
		CheckEffect(e, deltaTime);
	}
}

void ALivingEntity::CheckEffect(Effect* e, float deltaTime){
	e->lastDuration += deltaTime;
	e->totalTime += deltaTime;

	if (e->ShouldApply()) {
		e->ApplyEffect();
		e->EffectApplied();
		e->lastDuration = 0;

		if (e->EffectExpired()) {
			e->Expired();
			currentEffects.Remove(e);
		}
	}
}

bool ALivingEntity::HasEffect(Effect* newE) {
	for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it != NULL; it++){
		Effect* e = (Effect*)*it;
		if (e->id.Equals(newE->id)){
			return true;
		}
	}
	return false;
}

void ALivingEntity::GiveEffect(Effect* newE) {
	if (!newE->stacks && HasEffect(newE)) {
		for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it != NULL; it++){
			Effect* e = (Effect*)*it;
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
	//GetWorldTimerManager().ClearTimer(this, &ALivingEntity::StopCombo);
	GetWorldTimerManager().ClearAllTimersForObject(this);
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

		DodgeAction* tempDefenseAction = new DodgeAction();
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

		DodgeAction* tempDefenseAction = new DodgeAction();
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

		DodgeAction* tempDefenseAction = new DodgeAction();
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

		DodgeAction* tempDefenseAction = new DodgeAction();
		CurrentAction = tempDefenseAction;
	}
}

void ALivingEntity::InflictDamage(Damage* damage)
{
	Modifier* m = GetModifier(ModifierManager::defenseModiferName);

	if (m){
		damage->damageDone = damage->damageDone * m->value;
	}

	if (__raise source.LivingEntityDamageEvent(damage))
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