// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#ifndef __THE_BATTLE_OF_MALDON_H__
#define __THE_BATTLE_OF_MALDON_H__
#endif

//DECLARE_LOG_CATEGORY_EXTERN(CombatDecisions, Log, All)
//DECLARE_LOG_CATEGORY_EXTERN(CombatCombos, Log, All)

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "EngineGlobals.h"
//#include "Engine.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Array.h"
#include "UnrealString.h"

#include "Entity.h"
#include "LivingEntity.h"
#include "Person.h"
#include "Merchant.h"
#include "Villager.h"
#include "Creature.h"
#include "Forester.h"

#include "Effect.h"
#include "HealthEffect.h"
#include "ConsecutiveHealthEffect.h"

#include "CombatAction.h"
#include "DefenseAction.h"
#include "DodgeAction.h"
#include "AttackAction.h"
#include "MoveAction.h"
#include "BlockAction.h"

#include "Combo.h"
#include "ComboBP.h"
#include "CombosBP.h"

#include "Message.h"
#include "MessageBP.h"


#include "Conversation.h"
#include "ConversationChoice.h"
#include "ChoiceResponse.h"

#include "MyAIController.h"
#include "CombatAIController.h"
#include "MerchantAIController.h"

#include "VillagerAIController.h"

#include "Item.h"
#include "Weapon.h"
#include "Supply.h"
#include "SupplyRequirement.h"
#include "Supply.h"

#include "Damage.h"
#include "LivingEntityDamage.h"

#include "Body.h"
#include "PersonBody.h"
#include "CreatureBody.h"

#include "Arm.h"
#include "Leg.h"
#include "Head.h"
#include "Chest.h"

#include "Modifier.h"
#include "ModifierEffect.h"
#include "ModifierManager.h"

#include "BaseVolume.h"
#include "VillageVolume.h"
#include "Forest.h"
#include "Quarry.h"

#include "DrawDebugHelpers.h"
#include "ColorList.h"
#include "TimerManager.h"

#include <iostream>
#include <string>

#include "The_Battle_Of_MaldonCharacter.h"
#include "The_Battle_Of_MaldonGameMode.h"
#include "The_Battle_Of_MaldonHUD.h"
#include "The_Battle_Of_MaldonProjectile.h"

#include "TextureResource.h"

#include "CanvasItem.h"