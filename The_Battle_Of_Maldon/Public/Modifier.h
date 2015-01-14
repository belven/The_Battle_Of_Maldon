#pragma once
#include "Array.h"
#include "UnrealString.h"

/*A modifier is a change in an entities stats, i.e. thier damage/defense a value of 1 is 100%, 0.5 is 50% etc*/
class Modifier {

public:
	Modifier(FString nameIn, double valueIn){
		name = nameIn;
		value = valueIn;
	}

	FString name;
	double value;
};