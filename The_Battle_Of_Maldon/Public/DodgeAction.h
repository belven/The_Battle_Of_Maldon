#pragma once
#include "DefenseAction.h"
#include "Combo.h"
class DodgeAction : public DefenseAction
{
public:
	DodgeAction()
	{
		currentDefenseType = DefenseEnums::Dodge;
	}

};