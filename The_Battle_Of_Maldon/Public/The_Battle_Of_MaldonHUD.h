// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once 
#include "GameFramework/HUD.h"
#include "The_Battle_Of_MaldonHUD.generated.h"

UCLASS()
class AThe_Battle_Of_MaldonHUD : public AHUD
{
	GENERATED_BODY()

public:
	AThe_Battle_Of_MaldonHUD(const FObjectInitializer& ObjectInitializer);

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

