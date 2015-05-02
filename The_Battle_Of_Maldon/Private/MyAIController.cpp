#include "The_Battle_of_Maldon.h"

AMyAIController::AMyAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	canMove = true;
	isAI = true;
}

void AMyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);
	Bot = Cast<ALivingEntity>(InPawn);
	canMove = true;
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Bot && isAI)
	{
		lookForTarget();
	}
}

/*This method will make the bot go towards it's next PathObject*/
void AMyAIController::lookForTarget()
{
	//Check if there is anything within the bots patrol range otherwise move towards next RouteObject
	goToNextPathObject();
}

#pragma region Perception

/*Check to see if both the pawn and the taraget is within the Bot->patrolRange of currentRouteObject
*
* @param le - The entity to check distance from the currentRouteObject
*/
bool AMyAIController::livingEntityIsWithinPatrolRange(ALivingEntity* le)
{
	if (Bot->PathObjects.Num() > 0)
	{
		if (!currentRouteObject)
		{
			currentRouteObject = Bot->PathObjects[0];
		}

		if (le == NULL || currentRouteObject == NULL)
		{
			return false;
		}

		return (Bot->GetDistanceTo(currentRouteObject) <= Bot->patrolRange	&& le->GetDistanceTo(currentRouteObject) <= Bot->patrolRange);
	}
	else
	{
		return false;
	}
}

#pragma endregion

#pragma region Path Objects

/*This method will set the pawn to focus and move towards the next object within it's PathObjects*/
void AMyAIController::goToNextPathObject()
{
	if (canMove)
	{
		if (currentRouteObject)
		{
			setNextRouteObject();
		}
		else if (Bot->PathObjects.Num() > 0)
		{
			currentRouteObject = Bot->PathObjects[0];
		}

		if (currentRouteObject)
		{
			moveToTarget(currentRouteObject);
			target = currentRouteObject;
		}
	}
}

/*This will set currentRouteObject to the current index in PathObjects + 1 else it will go back to the start*/
void AMyAIController::setNextRouteObject()
{
	int32 index = Bot->PathObjects.IndexOfByKey(currentRouteObject);

	if ((index + 1) >= Bot->PathObjects.Num())
	{
		currentRouteObject = Bot->PathObjects[0];
	}
	else
	{
		currentRouteObject = Bot->PathObjects[index + 1];
	}
}

#pragma endregion

#pragma region Movement

/* This will move and set the focus of the pawn to the passed in Actor but only if the pawn isn't performing another action*/
void AMyAIController::moveToTarget(AActor* tempTarget)
{
	MoveAction* ma = new MoveAction(10);

	SetFocus(tempTarget);
	MoveToActor(tempTarget);
	canMove = false;
	Bot->CurrentAction = ma;
}


/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AMyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	canMove = true;

	if (Result != EPathFollowingResult::Success && target == currentRouteObject)
	{
		goToNextPathObject();
	}
}

#pragma endregion

