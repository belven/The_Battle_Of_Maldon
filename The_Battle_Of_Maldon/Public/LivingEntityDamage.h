#pragma once
#include "Damage.h"
#include "LivingEntityDamage.generated.h"

class ALivingEntity;
/*This class is used to define damage delt to an entity and who delt the damage*/
USTRUCT(BlueprintType)
struct FLivingEntityDamage : public FDamage {
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	ALivingEntity* damager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	ALivingEntity* damagee;

};