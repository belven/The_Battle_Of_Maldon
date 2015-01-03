#pragma once

#include "CombatAction.h"
#include "Combo.h"

class AttackAction : public CombatAction
{
public:
	AttackAction()
	{
		currentCombatActionType = CombatEnums::Attack;
	}

	Combo* AttackCombo;
};