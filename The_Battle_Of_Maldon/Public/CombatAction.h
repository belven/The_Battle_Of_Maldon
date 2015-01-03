namespace CombatEnums
{
	enum CombatType
	{
		Attack,
		Defense,
		Other
	};
}

#pragma once
#include "Action.h"

class CombatAction : public Action
{
public:
	CombatAction()
	{
		CurrentActionType = ActionEnums::Combat;
	}

	CombatEnums::CombatType currentCombatActionType;
};
