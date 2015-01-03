namespace DefenseEnums
{
	enum DefenseType
	{
		Block,
		Dodge,
		Other
	};
}


#pragma once
#include "CombatAction.h"
#include "Combo.h"

class DefenseAction : public CombatAction
{
public:
	DefenseAction()
	{
		currentCombatActionType = CombatEnums::Defense;
	}

	DefenseEnums::DefenseType currentDefenseType;

};