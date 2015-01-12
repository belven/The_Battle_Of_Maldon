UENUM(BlueprintType)
namespace LivingEntityEnums
{
	enum AggressionType
	{
		Passive UMETA(DisplayName = "Passive"),
		Neutral UMETA(DisplayName = "Neutral"),
		Aggressive UMETA(DisplayName = "Aggressive")
	};

}

UENUM(BlueprintType)
namespace DodgeEnums
{
	enum DodgeDirection
	{
		Left,
		Right,
		Forwards,
		Backwards
	};
}

#pragma once
#include "GameFramework/Actor.h"
#include "Entity.h"
#include "Array.h"
#include "Combos.h"
#include "CombosBP.h"
#include "DodgeAction.h"
#include "Item.h"
#include "UnrealString.h"
#include "Message.h"
#include "MessageBP.h"
#include "TimerManager.h"
#include "Weapon.h"
#include "Damage.h"
#include "ModifierManager.h"
#include "Effect.h"
#include "LivingEntity.generated.h"

UCLASS()
class ALivingEntity : public AEntity, public ModifierManager
{
	GENERATED_BODY()
public:
	ALivingEntity(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AggressionType)
		TEnumAsByte<LivingEntityEnums::AggressionType> CurrentAggressionType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Senses)
		float sightRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Senses)
		float hearingRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		float attackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Senses)
		float hearingLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
		float attackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Routes)
		TArray<AActor*> PathObjects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Routes)
		float patrolRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Person)
		FString entityName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Clan)
		FString clan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float rollDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
		float rollVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		AWeapon* Weapon;

	TArray<AItem*> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combo)
		ACombosBP* EntityCombosBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Messages)
		UMessageBP* startingMessageBP;

	Combos* EntityCombos;
	ALivingEntity* Target;
	float currentHealth;
	int intelligence;
	Message* startingMessage;
	TArray<Effect*> currentEffects;

	void InflictDamage(Damage* damage);
	void Dodge(DodgeEnums::DodgeDirection dodgeDirection);
	void StopCombo();
	void SetStopComboTimer(float ComboDelay);
	void ClearStopComboTimer();

	UFUNCTION(BlueprintCallable, Category = "AddItem")
		void AddItemToInventory(AItem* itemToAdd);

	void AttachItemToSocket(AItem* itemToAdd, FName socketName);
	void CheckEffects(float deltaTime);
	void CheckEffect(Effect* e, float deltaTime);
	bool HasEffect(Effect* newE);
	void GiveEffect(Effect* newE);
	void Tick(float deltaTime) override;
protected:
	void RollRight();
	void RollLeft();
	void RollForwards();
	void RollBackwards();
};
