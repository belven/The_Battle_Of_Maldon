#include "The_Battle_of_Maldon.h"
#include "CombatAIController.h"
#include "LivingEntity.h"
#include "Engine.h"
#include "HealthEffect.h"
#include "ModifierEffect.h"
#include "LivingEntityDamage.h"
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

/*This method is used to control the effects on the entity, this runs each frame*/
void ALivingEntity::Tick(float deltaTime){
	Super::Tick(deltaTime);
	CheckEffects(deltaTime);
}

/*This will check all current effects to see if they need applying or removing*/
void ALivingEntity::CheckEffects(float deltaTime){
	for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it != NULL; it++){
		Effect* e = (Effect*)*it;
		CheckEffect(e, deltaTime);
	}
}

/*Checks a single effect to allow for re-usability*/
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

/*Checks to see if an entity has an effect with a matching ID*/
bool ALivingEntity::HasEffect(Effect* newE) {
	for (TArray<Effect*>::TConstIterator it = currentEffects.CreateConstIterator(); it != NULL; it++){
		Effect* e = (Effect*)*it;
		if (e->id.Equals(newE->id)){
			return true;
		}
	}
	return false;
}

/*Assigns a new effect to an entity or replaces an existing one, based on if the effect stacks*/
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

/*Clears the entities combo timer, restting there combo to the start, 
may be run when blocked or the player fails to press the button in time*/
void ALivingEntity::SetStopComboTimer(float ComboDelay){
	ClearStopComboTimer();
	GetWorldTimerManager().SetTimer(this, &ALivingEntity::StopCombo, ComboDelay);
}

/*Removes the current time from the entity, possibly to add a new one*/
void ALivingEntity::ClearStopComboTimer(){
	//GetWorldTimerManager().ClearTimer(this, &ALivingEntity::StopCombo);
	GetWorldTimerManager().ClearAllTimersForObject(this);
}

/*Resets the entities combo to the start*/
void ALivingEntity::StopCombo()
{
	EntityCombos->StopCombo();
}

/*Adds an item to the entities inventory and will attach it to a socket if any*/
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

/*Places the items mesh at the inputted socket*/
void ALivingEntity::AttachItemToSocket(AItem* itemToAdd, FName socketName){
	itemToAdd->AttachRootComponentToActor(itemToAdd, socketName);
}

/*Launchs the character in the desired direction*/
void ALivingEntity::Dodge(DodgeEnums::DodgeDirection dodgeDirection = DodgeEnums::Backwards)
{
	if (GetCharacterMovement()->IsMovingOnGround())
	{
		const FVector ForwardDir = GetActorRightVector();
		const FVector AddForce = GetForceForRoll(dodgeDirection, ForwardDir);

		GetController()->StopMovement();
		LaunchCharacter(AddForce, true, true);

		DodgeAction* tempDefenseAction = new DodgeAction();
		CurrentAction = tempDefenseAction;
	}
}

/*Returns a vector based on another vector and the desired direction*/
FVector ALivingEntity::GetForceForRoll(DodgeEnums::DodgeDirection dodgeDirection, FVector ForwardDir) {
	switch (dodgeDirection)
	{
	case DodgeEnums::Left:
		return (ForwardDir * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity; 
	case DodgeEnums::Right:
		return (ForwardDir * rollDistance) + FVector(0, 0, 1) * rollVelocity;
	case DodgeEnums::Forwards:
		return	(ForwardDir * rollDistance) + FVector(0, 0, 1) * rollVelocity;
	case DodgeEnums::Backwards:
		return (ForwardDir * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity;
	default:
		return (ForwardDir * (0 - rollDistance)) + FVector(0, 0, 1) * rollVelocity;
	}
}

/*This damages the entiies health and will include damage reduction from defense modifiers**/
void ALivingEntity::InflictDamage(Damage* damage)
{
	Modifier* m = GetModifier(ModifierManager::defenseModiferName);
	LivingEntityDamage* led = (LivingEntityDamage*)damage;
	FString damageDone = FString::SanitizeFloat(damage->damageDone);

	FString damagedBy = "Other";

	if (led) {
		damagedBy = led->damager->entityName;
	}

	if (m) {
		damage->damageDone = damage->damageDone * m->value;
	}

	if (__raise source.LivingEntityDamageEvent(damage))
	{
		if ((currentHealth - damage->damageDone) > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, damagedBy + " delt " + damageDone + " damage to " + entityName);
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