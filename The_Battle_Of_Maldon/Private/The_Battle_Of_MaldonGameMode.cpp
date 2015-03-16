// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "The_Battle_Of_Maldon.h"

AThe_Battle_Of_MaldonGameMode::AThe_Battle_Of_MaldonGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AThe_Battle_Of_MaldonHUD::StaticClass();
}
