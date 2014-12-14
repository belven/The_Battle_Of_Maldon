namespace RewardEnums {

	enum RewardType {
		Default,
		Item,
		Quest
	};

};


#pragma once
#include "LivingEntity.h"



class Reward
{
public:
	RewardEnums::RewardType type;
	virtual void GiveRewards(ALivingEntity* pl) = 0;
};