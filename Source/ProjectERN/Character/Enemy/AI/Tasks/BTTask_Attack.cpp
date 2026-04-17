// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/AI/Tasks/BTTask_Attack.h"
#include "AIController.h"
#include "Character/Enemy/ERNEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Engine/DamageEvents.h"

UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = false;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	AERNEnemyCharacter* Enemy = Cast<AERNEnemyCharacter>(AIController->GetPawn());
	if (!Enemy)
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(TEXT("TargetActor")));
	if (!Target)
	{
		return EBTNodeResult::Failed;
	}

	// 타겟 방향으로 회전
	FVector Direction = Target->GetActorLocation() - Enemy->GetActorLocation();
	Direction.Z = 0.f;
	FRotator TargetRotation = Direction.Rotation();
	Enemy->SetActorRotation(TargetRotation);

	// 공격 애니메이션 재생
	if (AttackMontage && Enemy->GetMesh())
	{
		UAnimInstance* AnimInstance = Enemy->GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			AnimInstance->Montage_Play(AttackMontage);

			// 데미지 적용 (몽타주 Notify에서 처리하거나 여기서 바로 처리)
			// 여기서는 간단하게 바로 처리
			if (ACharacter* TargetCharacter = Cast<ACharacter>(Target))
			{
				// TODO: GAS 사용 시 GameplayEffect로 변경
				FDamageEvent DamageEvent;
				TargetCharacter->TakeDamage(Enemy->AttackRange, DamageEvent, AIController, Enemy);
			}

			UE_LOG(LogTemp, Log, TEXT("[%s] Attacked %s"), *Enemy->GetName(), *Target->GetName());
		}
	}

	// 공격 쿨다운을 위해 잠시 대기 (실제로는 Wait 노드나 Cooldown Decorator 사용 권장)
	return EBTNodeResult::Succeeded;
}
