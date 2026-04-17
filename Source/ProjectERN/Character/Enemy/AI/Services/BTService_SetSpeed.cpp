// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/AI/Services/BTService_SetSpeed.h"
#include "AIController.h"
#include "Character/Enemy/ERNEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_SetSpeed::UBTService_SetSpeed()
{
	NodeName = TEXT("Set Speed");
	Interval = 0.5f;
	RandomDeviation = 0.0f;
}

void UBTService_SetSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}

	AERNEnemyCharacter* Enemy = Cast<AERNEnemyCharacter>(AIController->GetPawn());
	if (!Enemy)
	{
		return;
	}

	UCharacterMovementComponent* MovementComp = Enemy->GetCharacterMovement();
	if (!MovementComp)
	{
		return;
	}

	// 속도 타입에 따라 설정
	switch (SpeedType)
	{
	case EMovementSpeedType::Patrol:
		MovementComp->MaxWalkSpeed = Enemy->PatrolSpeed;
		break;
	case EMovementSpeedType::Chase:
		MovementComp->MaxWalkSpeed = Enemy->ChaseSpeed;
		break;
	}
}
