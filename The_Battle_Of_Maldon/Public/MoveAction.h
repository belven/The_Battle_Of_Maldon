#pragma once

#include "Action.h"

class MoveAction : public Action
{
public:
	MoveAction(int inMovementSpeed)
	{
		CurrentActionType = ActionEnums::Movement;
		movementSpeed = inMovementSpeed;
	}

	int movementSpeed;
};
