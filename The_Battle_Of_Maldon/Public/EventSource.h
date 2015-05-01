
#pragma once
#include <stdio.h>
#include "AttackAction.h"
#include "MoveAction.h"
#include "DefenseAction.h"
#include "Damage.h"

[event_source(native)]
class EventSource {
public:
	__event bool AttackActionEvent(AttackAction* action);
	__event bool DefenseActionEvent(DefenseAction* action);
	__event bool MoveActionEvent(MoveAction* action);
	//__event bool LivingEntityDamageEvent(Damage* damage);
};