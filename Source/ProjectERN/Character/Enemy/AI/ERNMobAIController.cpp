// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/AI/ERNMobAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Character/Player/ProjectERNCharacter.h"

AERNMobAIController::AERNMobAIController()
{
	// AI Perception Component 생성
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp")));
}

void AERNMobAIController::BeginPlay()
{
	Super::BeginPlay();

	// AI Perception 설정
	SetupPerception();
}

void AERNMobAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Behavior Tree 실행
	if (BehaviorTreeAsset)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void AERNMobAIController::SetupPerception()
{
	UAIPerceptionComponent* PerceptionComp = GetPerceptionComponent();
	if (!PerceptionComp)
	{
		return;
	}

	// Sight Config 생성 (BeginPlay에서는 NewObject 사용)
	UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>(this);
	if (SightConfig)
	{
		// 시야 범위 설정
		SightConfig->SightRadius = 1500.0f;
		SightConfig->LoseSightRadius = 2000.0f;
		SightConfig->PeripheralVisionAngleDegrees = 90.0f;

		// 탐지 대상 설정
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

		// Perception Component에 Sight 설정 추가
		PerceptionComp->ConfigureSense(*SightConfig);
		PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	}

	// 타겟 감지 델리게이트 바인딩
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AERNMobAIController::OnTargetDetected);
}

void AERNMobAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	// 플레이어만 타겟팅
	AProjectERNCharacter* Player = Cast<AProjectERNCharacter>(Actor);
	if (Player)
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			// 시야 내 플레이어 감지
			Blackboard->SetValueAsObject(TEXT("TargetActor"), Player);
			UE_LOG(LogTemp, Log, TEXT("[%s] Player detected: %s"), *GetName(), *Player->GetName());
		}
		else
		{
			// 시야에서 사라짐
			AActor* CurrentTarget = Cast<AActor>(Blackboard->GetValueAsObject(TEXT("TargetActor")));
			if (CurrentTarget == Player)
			{
				Blackboard->ClearValue(TEXT("TargetActor"));
				UE_LOG(LogTemp, Log, TEXT("[%s] Player lost: %s"), *GetName(), *Player->GetName());
			}
		}
	}
}
