// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_GetNextPatrolPoint.generated.h"

/**
 * 다음 순찰 포인트를 BB에 설정하는 Task
 */
UCLASS()
class PROJECTERN_API UBTTask_GetNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_GetNextPatrolPoint();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Blackboard 키 이름
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName PatrolPointKey = TEXT("PatrolPoint");

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FName PatrolIndexKey = TEXT("PatrolIndex");
};
