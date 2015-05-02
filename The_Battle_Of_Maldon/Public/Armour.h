///////////////////////////////////////////////////////////
//  AArmour.h
//  Implementation of the Class Armour
//  Created on:      27-Apr-2015 19:37:53
//  Original author: sam
///////////////////////////////////////////////////////////


#pragma once
#include "Item.h"
#include "Stat.h"
#include "Equipable.h"
#include "Part.h"
#include "Armour.generated.h"

UCLASS()
class AArmour : public AItem, public Equipable
{
	GENERATED_BODY()

public:
	AArmour();

	double GetArmourStrength();
	void SetArmourStrength(UStat<double> newVal);
	void SetArmourStrength(double newVal);

	virtual void Equip(ALivingEntity* entity);
	virtual void UnEquip(ALivingEntity* entity);

	bool IsEquiped();
	void SetEquiped(bool newVal);

	PartEnums::PartType GetBodyPart();
	void SetBodyPart(PartEnums::PartType newVal);

private:
	UStat<double> armourStrength = *new UStat<double>(10, "Armour");
	TEnumAsByte<PartEnums::PartType> bodyPart = PartEnums::Chest;

};
