// Fill out your copyright notice in the Description page of Project Settings.

#include "The_Battle_Of_Maldon.h"
#include "Gatherer.h"
#include "GathererAIController.h"


AGatherer::AGatherer() : Super()
{
	AIControllerClass = AGathererAIController::StaticClass();
}


