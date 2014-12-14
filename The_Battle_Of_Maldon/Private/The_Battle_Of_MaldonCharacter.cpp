// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "The_Battle_Of_Maldon.h"
#include "The_Battle_Of_MaldonCharacter.h"
#include "The_Battle_Of_MaldonProjectile.h"
#include "Animation/AnimInstance.h"
#include "LivingEntity.h"
#include "Person.h"
#include "MoveAction.h"
#include "Weapon.h"
#include "DefenseAction.h"
#include "AttackAction.h"
#include "MyAIController.h"


//////////////////////////////////////////////////////////////////////////
// AThe_Battle_Of_MaldonCharacter

AThe_Battle_Of_MaldonCharacter::AThe_Battle_Of_MaldonCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
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

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

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

	/*InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);*/

	//InputComponent->BindAction("Fire", IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::OnFire);
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AThe_Battle_Of_MaldonCharacter::TouchStarted);

	InputComponent->BindAxis("MoveForward", this, &AThe_Battle_Of_MaldonCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AThe_Battle_Of_MaldonCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AThe_Battle_Of_MaldonCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AThe_Battle_Of_MaldonCharacter::LookUpAtRate);
}

void AThe_Battle_Of_MaldonCharacter::PossessedBy(class AController* NewController)
{
	Super::PossessedBy(NewController);
	AMyAIController* controller = (AMyAIController*)GetController();
	controller->canAttack = true;
	controller->Bot = this;
	controller->isAI = false;
}

void AThe_Battle_Of_MaldonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isLocking)
	{
		if (Target)
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
			return;
		}
	}

	Target = NULL;

	FHitResult testHitResult(ForceInit);
	UWorld* TheWorld = this->GetWorld();
	FVector testStartFVector = this->GetActorLocation();
	FVector testEndFVector = testStartFVector + GetActorForwardVector() * 1000.0f;
	FColor debugColor = FColor::Red;

	FCollisionQueryParams TraceParams(TEXT("MyTrace"), true, this);
	TraceParams.bTraceComplex = true;
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	if (TheWorld->LineTraceSingle(testHitResult, testStartFVector, testEndFVector, ECC_WorldStatic, TraceParams))
	{
		ALivingEntity* tempActor = (testHitResult.GetActor() != NULL ? Cast<ALivingEntity>(testHitResult.GetActor()) : NULL);

		if (tempActor != NULL)
		{
			debugColor = FColor::Red;
			Target = tempActor;
			//DrawDebugBox(TheWorld, testHitResult.Location, FVector(10, 10, 10), debugColor);
		}
	}
}

void AThe_Battle_Of_MaldonCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			// spawn the projectile at the muzzle
			World->SpawnActor<AThe_Battle_Of_MaldonProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

}

void AThe_Battle_Of_MaldonCharacter::CombatActionQ()
{
	DealDamage("Q");
}

void AThe_Battle_Of_MaldonCharacter::CombatActionE()
{
	if (Target)
	{
		if (Target->clan == clan){
			StartConverstation(Target);
		}
		else
		{
			DealDamage("E");
		}
	}
	else
	{
		DealDamage("E");
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

void AThe_Battle_Of_MaldonCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

/**
Creates or moves a conversation on based on the players choice
If the player were to press 'E' then 1 when targeting an NPC
The player would recieve a message from the NPC, then a list of possible responses

@parma index The index of the messages last displayed, starting at 1
*/
void AThe_Battle_Of_MaldonCharacter::GoToConverstation(int index)
{
	//Have we already been talking to them 
	if (currentConversation){
		//Get messages to display
		TArray<FString> messagesToDisplay = currentConversation->SetNextMessages(index);

		//We have reached the end of the Conversation
		if (messagesToDisplay.Num() <= 0){
			currentMessage = NULL;
			currentConversation = NULL;
		}
		else
		{
			//Display each message
			for (int i = 0; i < messagesToDisplay.Num(); i++){
				//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, messagesToDisplay[i]);
			}
		}
	}
	else {
		//Start a new Conversation with the entity and move back into this method
		if (Target && Target->startingMessage)
		{
			//Display a kind of welcome message
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "You started talking to " + Target->entityName);
			currentMessage = Target->startingMessage;

			//Create a new Conversation
			currentConversation = new Conversation(currentMessage);

			//Go back into the method with the new data
			GoToConverstation(index);
		}
	}
}

/**
This method was used to initilse a conversation but is almost unused
Will leave this incase of future changes
*/
void AThe_Battle_Of_MaldonCharacter::StartConverstation(ALivingEntity* le){
	GoToConverstation(1);
}

/**
This method will cause the players camera and pawn to rotate towards thier target as they both move
This is done by the player pressing and holding the shift key
*/
void AThe_Battle_Of_MaldonCharacter::LockOn()
{
	FirstPersonCameraComponent->bUseControllerViewRotation = false;
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
		((AMyAIController*)GetController())->SetFocus(Target);
	}
}

/**
This is run when the player realeses the shift key
It will cuase the camera and movement to go back to default
*/
void AThe_Battle_Of_MaldonCharacter::LockOnStopped()
{
	FirstPersonCameraComponent->bUseControllerViewRotation = true;
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
	if (!CharacterMovement->IsFalling() && !CharacterMovement->IsFlying())
	{
		CharacterMovement->StopMovementImmediately();
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
	AMyAIController* controller = (AMyAIController*)GetController();
	controller->attackTarget(ButtonPressed, Target);
}

void AThe_Battle_Of_MaldonCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && canMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AThe_Battle_Of_MaldonCharacter::MoveRight(float Value)
{
	if (Value != 0.0f && canMove)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AThe_Battle_Of_MaldonCharacter::TurnAtRate(float Rate)
{
	if (canMove){
		// calculate delta for this frame from the rate information
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AThe_Battle_Of_MaldonCharacter::LookUpAtRate(float Rate)
{
	if (canMove){
		// calculate delta for this frame from the rate information
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}
