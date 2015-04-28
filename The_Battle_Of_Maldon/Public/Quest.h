#pragma once
#include "Entity.h"
#include "Reward.h"
#include "ItemReward.h"
#include "LivingEntity.h"

class Quest
{
public:
	AEntity* startEntity;
	AEntity* endEntity;
	TArray<Reward*> rewards = *new TArray<Reward*>();

	Quest(AEntity* se, AEntity* ee, TArray<Reward*> rs)
	{
		startEntity = se;
		endEntity = ee;
		rewards = rs;
	}

	void GiveRewards(ALivingEntity* pl)
	{
		for (int i = 0; i < rewards.Num(); i++){
			Reward* r = rewards[i];
			r->GiveRewards(pl);			
		}
	}
};