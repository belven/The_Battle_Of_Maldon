// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "The_Battle_Of_Maldon.h"

AMerchant::AMerchant(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	AIControllerClass = AMerchantAIController::StaticClass();
}



