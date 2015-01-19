#pragma once
#include "LivingEntity.h"
#include "Damage.h"

/*This class is used to define damage delt to an entity and who delt the damage*/
class LivingEntityDamage : public Damage {
public:
	ALivingEntity* damager;
	ALivingEntity* damagee;

	LivingEntityDamage(ALivingEntity* inDamager, ALivingEntity* inDamagee, float damage) : Damage(damage){
		damager = inDamager;
		damagee = inDamagee;
	}



};