///////////////////////////////////////////////////////////
//  AArmor.h
//  Implementation of the Class Armor
//  Created on:      27-Apr-2015 19:37:53
//  Original author: sam
///////////////////////////////////////////////////////////


#pragma once
#include "Item.h"
#include "Stat.h"
#include "Equipable.h"
#include "Armor.generated.h"

UCLASS()
class AArmor : public AItem, public Equipable
{
	GENERATED_BODY()

public:
	AArmor();

	double GetArmourStrength();
	void SetArmourStrength(Stat newVal);
	void SetArmourStrength(double newVal);

	virtual void Equip(ALivingEntity entity);

	bool IsEquiped();
	void SetEquiped(bool newVal);

private:
	Stat armourStrength = *new Stat(10);

};
