#pragma once
#include "DefenseAction.h"
#include "Combo.h"
class BlockAction : public DefenseAction
{
public:
	BlockAction()
	{
		currentDefenseType = DefenseEnums::Block;
	}

};