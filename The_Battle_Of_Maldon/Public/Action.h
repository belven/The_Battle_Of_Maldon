
namespace ActionEnums
{
	enum ActionType
	{
		Movement,
		Combat,
		Other
	};
}
#pragma once

class Action
{
public:
	Action()
	{

	}
	ActionEnums::ActionType CurrentActionType;

	//TSubclassOf<class CombatAction> parentCombatAction;
};
