#pragma once
#include <stdio.h>
#include "EventSource.h"
#include "AttackAction.h"
#include "MoveAction.h"
#include "DefenseAction.h"
#include "Damage.h"

[event_receiver(native)]
class EventReceiver {
public:
	bool AttackActionEvent(AttackAction* action) {
		UE_LOG(LogTemp, Warning, TEXT("AttackActionEvent Raised"));

		return true;
	}

	bool MoveActionEvent(MoveAction* action) {
		UE_LOG(LogTemp, Warning, TEXT("MoveActionEvent Raised"));

		return true;
	}

	bool LivingEntityTakeDamageEvent(Damage* damage) {
		UE_LOG(LogTemp, Warning, TEXT("LivingEntityTakeDamageEvent Raised"));

		return true;
	}

	bool DefenseActionEvent(DefenseAction* action) {
		UE_LOG(LogTemp, Warning, TEXT("DefenseActionEvent Raised"));

		return true;
	}

	void hookEvent(EventSource* pSource) {
		__hook(&EventSource::AttackActionEvent, pSource, &EventReceiver::AttackActionEvent);
		__hook(&EventSource::DefenseActionEvent, pSource, &EventReceiver::DefenseActionEvent);
		__hook(&EventSource::MoveActionEvent, pSource, &EventReceiver::MoveActionEvent);
		__hook(&EventSource::LivingEntityTakeDamageEvent, pSource, &EventReceiver::LivingEntityTakeDamageEvent);
	}

	void unhookEvent(EventSource* pSource) {
		__unhook(&EventSource::AttackActionEvent, pSource, &EventReceiver::AttackActionEvent);
		__unhook(&EventSource::DefenseActionEvent, pSource, &EventReceiver::DefenseActionEvent);
		__unhook(&EventSource::MoveActionEvent, pSource, &EventReceiver::MoveActionEvent);
		__unhook(&EventSource::LivingEntityTakeDamageEvent, pSource, &EventReceiver::LivingEntityTakeDamageEvent);
	}
};