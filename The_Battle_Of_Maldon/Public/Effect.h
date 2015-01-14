#pragma once
#include "Array.h"
#include "LivingEntity.h"
#include "UnrealString.h"

namespace EffectEnums {
	enum EffectType {
		Default,
		Health,
		ConsecutiveHealth,
		Modifier
	};
}

namespace EffectStructs {
	struct EffectParams {
		double dely = 1.0;
		double lastTimeRan = 0.0;
		double maxDuration = 1.0;
		bool stacks = false;
		FString id = "Default";
	};

	struct HealthParams : EffectParams {
		double amountOfChange = 1.0;
		bool positive = false;
	};

	struct SpeedParams : EffectParams {
		double speedModifier = 0.2;
		bool positive = false;
	};

	struct ModifierParams : EffectParams {
		double modifier = 0.2;
		FString modifierName = "";
		bool positive = false;
	};

	struct ConsecutiveHealthParams : HealthParams {
		double HealthPercentIncrease = 1.0;
		double minChange = 0.0;
		double maxChange = 10000.0;
	};
}

/*An effect is a timed event that performs tasks each tick,used to do damage/healing and buffs/debuffs*/
class Effect {

public:

	Effect(EffectStructs::EffectParams params, ALivingEntity* owner){
		effectOwner = owner;
		type = EffectEnums::Default;
		dely = params.dely;
		lastDuration = params.lastTimeRan;
		maxDuration = params.maxDuration;
		stacks = params.stacks;
		id = params.id;
		//effectOwner->GiveEffect(this);
	}

	double dely = 1.0;
	double lastDuration = 0.0;
	double totalTime = 0.0;
	double maxDuration = 1.0;
	int timesRun = 0;
	FString id = "Default";
	bool stacks = false;

	ALivingEntity* effectOwner;
	EffectEnums::EffectType type;

	virtual void ApplyEffect() = 0;
	virtual void Expired() = 0;

	/*Returns a double based on the time the effect has left
	used to determine if it should be replaced*/
	double Score(){
		return maxDuration - totalTime;
	};

	/*increments the run times of the effect*/
	void EffectApplied() {
		timesRun++;
	};

	/*Determines if the effect should apply, this should happen when the time passed is greater than the delay*/
	bool ShouldApply(){
		return lastDuration >= dely;
	}

	/*Determines if the effects totalTime is over the maxDuration, i.e. the effect has ended*/
	bool EffectExpired(){
		return totalTime >= maxDuration;
	}
};