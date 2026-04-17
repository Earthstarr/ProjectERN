// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_SetSpeed.generated.h"

UENUM(BlueprintType)
enum class EMovementSpeedType : uint8
{
	Patrol,
	Chase
};

/**
 * 몬스터 이동 속도를 설정하는 BT Service
 */
UCLASS()
class PROJECTERN_API UBTService_SetSpeed : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_SetSpeed();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	// 속도 타입 (순찰/추적)
	UPROPERTY(EditAnywhere, Category = "Speed")
	EMovementSpeedType SpeedType = EMovementSpeedType::Patrol;
};
