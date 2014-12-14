#pragma once

#include "CombatAction.h"
#include "Combo.h"

class DefenseAction : public CombatAction
{
public:
	DefenseAction()
	{
		CurrentCombatActionType = CombatEnums::Defense;
	}

	Combo* AttackCombo;
};