// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/AI/Tasks/BTTask_CheckLeashDistance.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"

UBTTask_CheckLeashDistance::UBTTask_CheckLeashDistance()
{
	NodeName = TEXT("Check Leash Distance");
}

EBTNodeResult::Type UBTTask_CheckLeashDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* Pawn = AIController->GetPawn();
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	FVector HomeLocation = BlackboardComp->GetValueAsVector(HomeLocationKey);
	FVector CurrentLocation = Pawn->GetActorLocation();

	float DistanceFromHome = FVector::Dist(CurrentLocation, HomeLocation);

	// Leash 거리를 초과하면 타겟 해제
	if (DistanceFromHome > LeashDistance)
	{
		BlackboardComp->ClearValue(TargetActorKey);
		UE_LOG(LogTemp, Warning, TEXT("[%s] Leash distance exceeded! Returning home. Distance: %.2f / %.2f"),
			*Pawn->GetName(), DistanceFromHome, LeashDistance);

		return EBTNodeResult::Failed; // 전투 시퀀스 실패 → 순찰로 복귀
	}

	return EBTNodeResult::Succeeded;
}
