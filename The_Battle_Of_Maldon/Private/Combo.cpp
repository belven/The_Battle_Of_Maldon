
#include "The_Battle_of_Maldon.h"

Combo::Combo()
{
	ComboID = 1;
	ComboButton = "";
	ComboDamageScaling = 1;
	ComboDelay = 1;
}

void Combo::Add(Combo* ComboToAdd)
{
	ComboList.Add(ComboToAdd);
}