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
		double startTime = 0.0;
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

class Effect {

public:

	Effect(EffectStructs::EffectParams params, ALivingEntity* owner){
		effectOwner = owner;
		type = EffectEnums::Default;
		dely = params.dely;
		lastTimeRan = params.lastTimeRan;
		startTime = params.startTime;
		maxDuration = params.maxDuration;
		stacks = params.stacks;
		id = params.id;
	}

	double dely = 1.0;
	double lastTimeRan = 0.0;
	double startTime = 0.0;
	double maxDuration = 1.0;
	int timesRun = 0;
	FString id = "Default";
	bool stacks = false;

	ALivingEntity* effectOwner;
	EffectEnums::EffectType type;

	virtual void ApplyEffect() = 0;
	virtual void Expired() = 0;

	double Score(){
		return lastTimeRan - startTime;
	};

	void EffectApplied() {
		timesRun++;
	};

	bool ShouldApply(double deltaTime){
		return (deltaTime - lastTimeRan) >= dely;
	}

	bool EffectExpired(double deltaTime){
		return (deltaTime - startTime) >= maxDuration;
	}
};