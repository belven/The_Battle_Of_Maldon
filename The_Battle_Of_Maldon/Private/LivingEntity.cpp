#include "The_Battle_of_Maldon.h"
#include "Engine.h"

ALivingEntity::ALivingEntity() : Super()
{
	CurrentEntityType = EntityEnums::Living;
	AIControllerClass = ACombatAIController::StaticClass();
	EntityCombos = new Combos(this);
	health = 1000;
	entityName = "Test";
	clan = "2";
	currentHealth = health;
	rollDistance = 400;
	rollVelocity = 300;

	UChoiceResponse* start = new UChoiceResponse("Hello");
	UChoiceResponse* middle = new UChoiceResponse("Greg");
	UChoiceResponse* end = new UChoiceResponse("Good bye");

	UConversationChoice* name = new UConversationChoice("What's you're name?");
	name->SetResponse(middle);
	
	UConversationChoice* sorry = new UConversationChoice("Sorry to disturb you, cya");
	sorry->SetResponse(end);

	start->AddChoice(name);
	start->AddChoice(sorry);

	middle->AddChoice(sorry);

	SetConversation(new UConversation(start));
}

/*This method is used to control the effects on the entity, this runs each frame*/
void ALivingEntity::Tick(float deltaTime){
	Super::Tick(deltaTime);
	CheckEffects(deltaTime);
}

double ALivingEntity::GetHealth(){
	return body->GetTotalVitality();
}

Body* ALivingEntity::GetBody(){
	return body;
}


void ALivingEntity::SetBody(Body* value){
	body = value;
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
	inventory->AddItem(itemToAdd);
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
	Modifier* modifier = GetModifier(ModifierManager::defenseModiferName);
	LivingEntityDamage* led = (LivingEntityDamage*)damage;
	FString damagedBy = "Other";

	if (led) {
		damagedBy = led->damager->entityName;
	}

	if (modifier) {
		damage->damageDone *= modifier->value;
	}

	if (__raise source.LivingEntityDamageEvent(damage))
	{
		FString damageDone = FString::SanitizeFloat(damage->damageDone);
		if ((currentHealth - damage->damageDone) > 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, damagedBy + " delt " + damageDone + " damage to " + entityName);
			currentHealth -= damage->damageDone;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, entityName + " was killed!!!");
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::SanitizeFloat(currentHealth - Damage) +  " overkill damage!!");

			std::unique_lock<std::mutex> lk(m);
			cv.wait(lk, [&]{ return !beingRed; });
			beingRed = true;
			lk.unlock();
			cv.notify_one();
			Destroy();
		}
	}
}


UConversation* ALivingEntity::GetConversation(){
	return conversation;
}


void ALivingEntity::SetConversation(UConversation* newVal){
	conversation = newVal;
}


Inventory* ALivingEntity::GetInventory(){
	return inventory;
}


void ALivingEntity::SetInventory(Inventory* newVal){
	inventory = newVal;
}


AActor* ALivingEntity::GetTarget(){

	return target;
}


void ALivingEntity::SetTarget(AActor* newVal){

	target = newVal;
}