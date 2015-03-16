// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Person.h"
#include "VillageVolume.h"
#include "Villager.generated.h"

/**
 * 
 */
UCLASS()
class THE_BATTLE_OF_MALDON_API AVillager : public APerson
{
	GENERATED_BODY()
public:
	AVillager();
	AVillageVolume* GetVillage();
	void setVillage(AVillageVolume* inVillage);	
	AVillageVolume* village;
	
};
