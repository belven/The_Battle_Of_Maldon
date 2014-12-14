#pragma once
#include "Array.h"
#include "UnrealString.h"

class Modifier {

public:
	Modifier(FString nameIn, double valueIn){
		name = nameIn;
		value = valueIn;
	}

	FString name;
	double value;
};