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
#include "The_Battle_of_Maldon.h"

class DefenseAction : public CombatAction
{
public:
	DefenseAction()
	{
		currentCombatActionType = CombatEnums::Defense;
	}

	DefenseEnums::DefenseType currentDefenseType;

};