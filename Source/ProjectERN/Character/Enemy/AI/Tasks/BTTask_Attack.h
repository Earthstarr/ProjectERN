// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 근접 공격 BT Task
 */
UCLASS()
class PROJECTERN_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// 공격 애니메이션 몽타주
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackMontage;

	// 공격 쿨다운 시간
	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackCooldown = 1.5f;
};
