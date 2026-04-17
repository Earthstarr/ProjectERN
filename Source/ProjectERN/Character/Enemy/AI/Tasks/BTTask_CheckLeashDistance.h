// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CheckLeashDistance.generated.h"

/**
 * Leash(고무줄) 체크 - HomeLocation에서 너무 멀어졌는지 확인
 * 너무 멀면 타겟을 해제하고 집으로 복귀
 */
UCLASS()
class PROJECTERN_API UBTTask_CheckLeashDistance : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CheckLeashDistance();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Leash 거리 (홈에서 이 거리 이상 벗어나면 복귀)
	UPROPERTY(EditAnywhere, Category = "Leash")
	float LeashDistance = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName HomeLocationKey = TEXT("HomeLocation");

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName TargetActorKey = TEXT("TargetActor");
};
