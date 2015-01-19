#pragma once
#include "The_Battle_of_Maldon.h"

class DodgeAction : public DefenseAction
{
public:
	DodgeAction()
	{
		currentDefenseType = DefenseEnums::Dodge;
	}

};