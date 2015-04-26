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
#include "ModifierManager.h"
#include "Entity.h"
#include "Combos.h"
#include "Weapon.h"
#include "Damage.h"
#include "Conversation.h"
#include "EffectManager.h"
#include "Body.h"
#include "LivingEntity.generated.h"

UCLASS()
class ALivingEntity : public AEntity, public ModifierManager
{
	GENERATED_BODY()
private:
	Body* body;
	UConversation* conversation;

public:
	ALivingEntity();
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
	Combos* EntityCombos;
	AActor* Target;
	float currentHealth;
	int intelligence;

	Body* GetBody();
	double GetHealth();

	void ClearStopComboTimer();
	void StopCombo();

	void SetStopComboTimer(float ComboDelay);
	void InflictDamage(Damage* damage);
	void Dodge(DodgeEnums::DodgeDirection dodgeDirection);
	void SetBody(Body* value);

	UFUNCTION(BlueprintCallable, Category = "AddItem")
		void AddItemToInventory(AItem* itemToAdd);

	void AttachItemToSocket(AItem* itemToAdd, FName socketName);
	void Tick(float deltaTime) override;

	UConversation* GetConversation();
	void SetConversation(UConversation* newVal);

protected:
	FVector GetForceForRoll(DodgeEnums::DodgeDirection dodgeDirection, FVector ForwardDir);
};