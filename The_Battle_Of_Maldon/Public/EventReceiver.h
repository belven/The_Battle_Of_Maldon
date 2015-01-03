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

		return true;
	}

	bool MoveActionEvent(MoveAction* action) {

		return true;
	}

	bool LivingEntityDamageEvent(Damage* damage) {

		return true;
	}

	bool DefenseActionEvent(DefenseAction* action) {

		return true;
	}

	void hookEvent(EventSource* pSource) {
		__hook(&EventSource::AttackActionEvent, pSource, &EventReceiver::AttackActionEvent);
		__hook(&EventSource::DefenseActionEvent, pSource, &EventReceiver::DefenseActionEvent);
		__hook(&EventSource::MoveActionEvent, pSource, &EventReceiver::MoveActionEvent);
		__hook(&EventSource::LivingEntityDamageEvent, pSource, &EventReceiver::LivingEntityDamageEvent);
	}

	void unhookEvent(EventSource* pSource) {
		__unhook(&EventSource::AttackActionEvent, pSource, &EventReceiver::AttackActionEvent);
		__unhook(&EventSource::DefenseActionEvent, pSource, &EventReceiver::DefenseActionEvent);
		__unhook(&EventSource::MoveActionEvent, pSource, &EventReceiver::MoveActionEvent);
		__unhook(&EventSource::LivingEntityDamageEvent, pSource, &EventReceiver::LivingEntityDamageEvent);
	}
};