///////////////////////////////////////////////////////////
//  Equipable.h
//  Implementation of the Interface Equipable
//  Created on:      27-Apr-2015 20:17:21
//  Original author: sam
///////////////////////////////////////////////////////////
#pragma once
#include "LivingEntity.h"

class Equipable
{

public:
	Equipable() {

	}

	virtual void Equip(ALivingEntity* entity) { check(0 && "You must override this") };
	virtual void UnEquip(ALivingEntity* entity) { check(0 && "You must override this") };
	virtual bool IsEquiped() { check(0 && "You must override this"); return false; };
	virtual void SetEquiped(bool newVal) { check(0 && "You must override this") };

	bool isEquiped;
};
