#include "The_Battle_of_Maldon.h"
#include "MyAIController.h"
#include "LivingEntity.h"
#include "Person.h"
#include "MoveAction.h"
#include "DrawDebugHelpers.h"
#include "ColorList.h"
#include "Engine.h"

AMyAIController::AMyAIController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController start"));
	canMove = true;
	isAI = true;
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController end"));
}

void AMyAIController::Possess(APawn* InPawn)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController Possess"));
	Super::Possess(InPawn);
	Bot = Cast<ALivingEntity>(InPawn);
	canMove = true;
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController Possess End"));
}

void AMyAIController::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController Tick start"));
	Super::Tick(DeltaTime);

	if (Bot && isAI)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyAIController lookForTarget"));
		lookForTarget();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController Tick end"));
}

void AMyAIController::lookForTarget()
{
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController lookForTarget start"));
	//Check if there is anything within the bots patrol range otherwise move towards next RouteObject
	goToNextPathObject();
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController lookForTarget end"));
}

#pragma region Perception

/*Check to see if both the pawn and the taraget is within the Bot->patrolRange of currentRouteObject*/
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
		UE_LOG(LogTemp, Warning, TEXT("AMyAIController goToNextPathObject canMove"));
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
			UE_LOG(LogTemp, Warning, TEXT("AMyAIController goToNextPathObject currentRouteObject"));
			moveToTarget(currentRouteObject);
			target = currentRouteObject;
		}
		UE_LOG(LogTemp, Warning, TEXT("AMyAIController goToNextPathObject end"));
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
	UE_LOG(LogTemp, Warning, TEXT("moveToTarget"));
	MoveAction* ma = new MoveAction(10);

	if (__raise Bot->source.MoveActionEvent(ma) && Bot->CurrentAction == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("__raise"));
		SetFocus(tempTarget);
		MoveToActor(tempTarget);
		canMove = false;
		Bot->CurrentAction = ma;
	}
	UE_LOG(LogTemp, Warning, TEXT("moveToTarget end"));
}

/*This is used to make sure that the pawn can only move after it's reached it's current destination.*/
void AMyAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController OnMoveCompleted start"));
	canMove = true;

	if (Result != EPathFollowingResult::Success && target == currentRouteObject)
	{
		goToNextPathObject();
	}
	UE_LOG(LogTemp, Warning, TEXT("AMyAIController OnMoveCompleted end"));
}

#pragma endregion

