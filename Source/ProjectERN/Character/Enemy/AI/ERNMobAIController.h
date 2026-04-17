// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "ERNMobAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

/**
 * 일반 몬스터용 AI Controller
 */
UCLASS()
class PROJECTERN_API AERNMobAIController : public AAIController
{
	GENERATED_BODY()

public:
	AERNMobAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	// AI Perception 설정
	void SetupPerception();

	// 타겟 감지 콜백
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

protected:
	// Behavior Tree
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;

public:
	// Blackboard Component 접근자
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return Blackboard; }
};
