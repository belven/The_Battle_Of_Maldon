#include "The_Battle_Of_Maldon.h"
#include "Engine.h"

AThe_Battle_Of_MaldonCharacter::AThe_Battle_Of_MaldonCharacter(const FObjectInitializer& ObjectInitializer)
: Super()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	clan = "1";
	health = 1000;
	entityName = "Player";
	isLocking = false;
	canMove = true;

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = GetCapsuleComponent();
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
}

/**
 * APawn interface
 */
void AThe_Battle_Of_MaldonCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("CombatActionQ", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::CombatActionQ);
	InputComponent->BindAction("CombatActionE", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::CombatActionE);
	InputComponent->BindAction("CombatActionR", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::CombatActionR);
	InputComponent->BindAction("CombatActionF", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::CombatActionF);

	InputComponent->BindAction("ConverstationActionOne", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::ConverstationActionOne);
	InputComponent->BindAction("ConverstationActionTwo", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::ConverstationActionTwo);
	InputComponent->BindAction("ConverstationActionThree", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::ConverstationActionThree);
	InputComponent->BindAction("ConverstationActionFour", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::ConverstationActionFour);

	InputComponent->BindAction("Block", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::Block);
	InputComponent->BindAction("Block", IE_Released, this, &AThe_Battle_Of_MaldonCharacter::BlockStopped);

	InputComponent->BindAction("Lock", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::LockOn);
	InputComponent->BindAction("Lock", IE_Released, this, &AThe_Battle_Of_MaldonCharacter::LockOnStopped);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::TouchStarted);

	InputComponent->BindAxis("MoveForward", this, &AThe_Battle_Of_MaldonCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AThe_Battle_Of_MaldonCharacter::MoveRight);

	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AThe_Battle_Of_MaldonCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AThe_Battle_Of_MaldonCharacter::LookUpAtRate);
	UE_LOG(LogTemp, Log, TEXT("Test 4"));
}

void AThe_Battle_Of_MaldonCharacter::PossessedBy(class AController* NewController)
{
	Super::PossessedBy(NewController);
	ACombatAIController* controller = (ACombatAIController*)NewController;
	controller->isAI = false;
	controller->Bot = this;
	controller->canAttack = true;
}

void AThe_Battle_Of_MaldonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Target && isLocking)
	{
		FVector Direction = Target->GetActorLocation() - GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();

		if (GetMovementComponent() && GetMovementComponent()->IsMovingOnGround())
		{
			NewControlRotation.Pitch = 0.f;
		}

		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);
		GetController()->SetControlRotation(NewControlRotation);

		FaceRotation(NewControlRotation, DeltaTime);
	}
	else
	{
		Target = NULL;

		FHitResult testHitResult(ForceInit);
		FVector testStartFVector = GetActorLocation();
		FVector testEndFVector = testStartFVector + GetActorForwardVector() * 1000.0f;

		FCollisionQueryParams TraceParams(TEXT("MyTrace"), true, this);
		TraceParams.bTraceComplex = true;
		TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = false;

		if (GetWorld()->LineTraceSingle(testHitResult, testStartFVector, testEndFVector, ECC_WorldStatic, TraceParams))
		{
			AActor* tempActor = testHitResult.GetActor();

			if (tempActor != NULL &&
				(tempActor->GetClass()->IsChildOf(AItem::StaticClass()) || tempActor->GetClass()->IsChildOf(ALivingEntity::StaticClass())))
			{
				ACombatAIController* controller = (ACombatAIController*)GetController();
				Target = tempActor;
				controller->target = Target;
			}
		}
	}
}

/**
 * Fires a projectile.
 */
void AThe_Battle_Of_MaldonCharacter::OnFire()
{
	// try and fire a projectile
	//if (ProjectileClass != NULL)
	//{
	//	const FRotator SpawnRotation = GetControlRotation();
	//	// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	//	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

	//	UWorld* const World = GetWorld();
	//	if (World != NULL)
	//	{
	//		// spawn the projectile at the muzzle
	//		World->SpawnActor<AThe_Battle_Of_MaldonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
	//	}
	//}

	//// try and play the sound if specified
	//if (FireSound != NULL)
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	//}

	//// try and play a firing animation if specified
	//if (FireAnimation != NULL)
	//{
	//	// Get the animation object for the arms mesh
	//	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
	//	if (AnimInstance != NULL)
	//	{
	//		//AnimInstance->Montage_Play(FireAnimation, 1.f);
	//	}
	//}

}

void AThe_Battle_Of_MaldonCharacter::CombatActionQ()
{
	DealDamage("Q");
}

void AThe_Battle_Of_MaldonCharacter::CombatActionE()
{
	if (Target && Target->GetClass()->IsChildOf(ALivingEntity::StaticClass()))
	{
		ALivingEntity* target = Cast<ALivingEntity>(Target);
		if (target->clan == clan){
			StartConverstation(target);
		}
		else
		{
			DealDamage("E");
		}
	}
	else if (Target && Target->GetClass()->IsChildOf(AItem::StaticClass())){
		AItem* target = Cast<AItem>(Target);
		Inventory.Add(target);
		target->SetActorHiddenInGame(true);
		target->SetActorEnableCollision(false);
	}
}

void AThe_Battle_Of_MaldonCharacter::CombatActionR()
{
	DealDamage("R");
}

void AThe_Battle_Of_MaldonCharacter::CombatActionF()
{
	DealDamage("F");
}

void AThe_Battle_Of_MaldonCharacter::ConverstationActionOne()
{
	GoToConverstation(1);
}

void AThe_Battle_Of_MaldonCharacter::ConverstationActionTwo()
{
	GoToConverstation(2);
}

void AThe_Battle_Of_MaldonCharacter::ConverstationActionThree()
{
	GoToConverstation(3);
}

void AThe_Battle_Of_MaldonCharacter::ConverstationActionFour()
{
	GoToConverstation(4);
}

/**
Creates or moves a conversation on based on the players choice
If the player were to press 'E' then 1 when targeting an NPC
The player would recieve a message from the NPC, then a list of possible responses

@parma index The index of the messages last displayed, starting at 1
*/
void AThe_Battle_Of_MaldonCharacter::GoToConverstation(int index)
{
	if (currentConversation){
		currentConversation->SelectChoice(index - 1);

		if (currentConversation->GetCurrentResponse()->GetQuest() != NULL){
			GiveQuest(currentConversation->GetCurrentResponse()->GetQuest());
		}

		OutputConversation();
	}
}

/**
This method was used to initilse a conversation but is almost unused
Will leave this incase of future changes
*/
void AThe_Battle_Of_MaldonCharacter::StartConverstation(ALivingEntity* le){
	ALivingEntity* target = Cast<ALivingEntity>(Target);

	if (target->GetConversation() != NULL && currentConversation == NULL) {
		currentConversation = target->GetConversation();
		OutputConversation();
	}
}

void AThe_Battle_Of_MaldonCharacter::OutputConversation(){
	// Write out the NPCs response
	WriteMessage(currentConversation->GetCurrentResponse()->GetText());

	TArray<UConversationChoice*> choices = currentConversation->GetCurrentChoices();

	// If we have any choices then write them out
	if (choices.Num() > 0){
		for (UConversationChoice* choice : choices){
			WriteMessage(choice->GetText());
		}
	}
	else // Otherwise we've reached the end of the conversation 
	{
		currentConversation->ResetConversation();
		currentConversation = NULL;
	}

	WriteMessage("------------------------------");
}

/**
This method will cause the players camera and pawn to rotate towards thier target as they both move
This is done by the player pressing and holding the shift key
*/
void AThe_Battle_Of_MaldonCharacter::LockOn()
{
	FirstPersonCameraComponent->bUsePawnControlRotation = false;
	FocusOnLockOn();
	isLocking = true;
}

/**
Used by the LockOn() method to use the controllers base SetFocus() method
*/
void AThe_Battle_Of_MaldonCharacter::FocusOnLockOn()
{
	if (Target)
	{
		((ACombatAIController*)GetController())->SetFocus(Target);
	}
}

/**
This is run when the player realeses the shift key
It will cuase the camera and movement to go back to default
*/
void AThe_Battle_Of_MaldonCharacter::LockOnStopped()
{
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	isLocking = false;
	Target = NULL;
}

/**
While holding ctrl, the player will then block all attacks
If hit by an attack the attacker will be inactive for 1.5 seconds
Allowing for counter attacks
*/
void AThe_Battle_Of_MaldonCharacter::Block()
{
	if (!GetCharacterMovement()->IsFalling() && !GetCharacterMovement()->IsFlying())
	{
		GetCharacterMovement()->StopMovementImmediately();
		DefenseAction* tempDefenseAction = new DefenseAction();
		CurrentAction = tempDefenseAction;
		canMove = false;
	}
}

/**
When ctrl is realesed the player will stop blocking
*/
void AThe_Battle_Of_MaldonCharacter::BlockStopped()
{
	CurrentAction = NULL;
	canMove = true;
}

/*
This forms the starting point for the players combos
The player presses a button, e.g. 'E', 'F', 'Q'
And this will check if they have pressed the right button, this is all handled in the AIController

@parma ButtonPressed The string value of the button the player pressed e.g. 'E', 'F', 'Q'
*/
void AThe_Battle_Of_MaldonCharacter::DealDamage(FString ButtonPressed)
{
	ACombatAIController* controller = (ACombatAIController*)GetController();
	controller->attackTarget(ButtonPressed, Target);
}

/**
 * Handles moving forward/backward
 */
void AThe_Battle_Of_MaldonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && canMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

/**
 * Handles stafing movement, left and right
 */
void AThe_Battle_Of_MaldonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && canMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

/**
 * Called via input to turn at a given rate.
 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
 */
void AThe_Battle_Of_MaldonCharacter::TurnAtRate(float Rate)
{
	if (canMove && !isLocking){
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

/**
 * Called via input to turn look up/down at a given rate.
 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
 */
void AThe_Battle_Of_MaldonCharacter::LookUpAtRate(float Rate)
{
	if (canMove && !isLocking){
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}



void AThe_Battle_Of_MaldonCharacter::WriteMessage(FString message){
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, message);
}


void AThe_Battle_Of_MaldonCharacter::GiveQuest(Quest* quest){
	currentQuests.Add(quest);
}