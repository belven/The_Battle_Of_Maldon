#pragma once
#include "Reward.h"
#include "Quest.h"

class QuestReward : Reward
{
public:
	Quest* rewardedQuest;

	QuestReward(Quest* rq)
	{
		rewardedQuest = rq;
		type == RewardEnums::Quest;
	}
};