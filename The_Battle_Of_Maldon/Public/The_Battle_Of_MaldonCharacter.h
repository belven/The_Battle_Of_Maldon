// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Person.h"
#include "UnrealString.h"
#include "LivingEntity.h"
#include "Quest.h"
#include "The_Battle_Of_MaldonCharacter.generated.h"

UCLASS(config=Game)
class AThe_Battle_Of_MaldonCharacter : public APerson
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;
private:
	UConversation* currentConversation;

public:
	AThe_Battle_Of_MaldonCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
			
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Message)
		TArray<FString> currentMessages = *new TArray<FString>();

	TArray<Quest*> currentQuests = *new TArray<Quest*>();
	bool isLocking;
	bool canMove;

	void CombatActionQ();
	void CombatActionE();
	void CombatActionR();
	void CombatActionF();
	void ConverstationActionOne();
	void ConverstationActionTwo();
	void ConverstationActionThree();
	void ConverstationActionFour();
	void GoToConverstation(int index);
	void StartConverstation(ALivingEntity* le);

	void LockOn();
	void LockOnStopped();
	void FocusOnLockOn();
	void Block();
	void BlockStopped();
	void DealDamage(FString ButtonPressed);

	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(class AController* NewController) override;
	void WriteMessage(FString message);
	void OutputConversation();
	void GiveQuest(Quest* quest);

protected:
	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

};