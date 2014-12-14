#pragma once

#include "CombatAction.h"
#include "Combo.h"

class AttackAction : public CombatAction
{
public:
	AttackAction()
	{
		CurrentCombatActionType = CombatEnums::Attack;
	}

	Combo* AttackCombo;
};