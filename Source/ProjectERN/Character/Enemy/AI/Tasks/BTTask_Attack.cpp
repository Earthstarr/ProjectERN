// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/AI/Tasks/BTTask_Attack.h"
#include "AIController.h"
#include "Character/Enemy/ERNEnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "GAS/ERNGameplayTags.h"

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

	// 경직 상태면 공격 중단
	if (UAbilitySystemComponent* ASC = Enemy->GetAbilitySystemComponent())
	{
		if (ASC->HasMatchingGameplayTag(TAG_State_Stagger))
		{
			return EBTNodeResult::Failed;
		}
	}

	// 타겟 방향으로 회전
	FVector Direction = Target->GetActorLocation() - Enemy->GetActorLocation();
	Direction.Z = 0.f;
	Enemy->SetActorRotation(Direction.Rotation());

	// 공격 몽타주 재생 (데미지는 AnimNotifyState_EnemyMeleeHitbox / AnimNotify_EnemySpawnProjectile에서 처리)
	if (AttackMontage && Enemy->GetMesh())
	{
		UAnimInstance* AnimInstance = Enemy->GetMesh()->GetAnimInstance();
		if (AnimInstance && !AnimInstance->Montage_IsPlaying(AttackMontage))
		{
			AnimInstance->Montage_Play(AttackMontage);
			UE_LOG(LogTemp, Log, TEXT("[%s] Attack montage played on %s"), *Enemy->GetName(), *Target->GetName());
		}
	}

	return EBTNodeResult::Succeeded;
}
