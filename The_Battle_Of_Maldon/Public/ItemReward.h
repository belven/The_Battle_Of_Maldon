#pragma once
#include "Reward.h"
#include "Item.h"
#include "LivingEntity.h"

class ItemReward : public Reward
{
public:
	TArray<AItem*> rewardedItems = *new TArray<AItem*>();

	ItemReward(TArray<AItem*> ri)
	{
		rewardedItems = ri;
		type = RewardEnums::Item;
	}
	
	void GiveRewards(ALivingEntity* pl) {
		/*for (int i = 0; i < rewardedItems.Num(); i++){
			pl->Inventory.Add(rewardedItems[i]);
		}*/
	}
};