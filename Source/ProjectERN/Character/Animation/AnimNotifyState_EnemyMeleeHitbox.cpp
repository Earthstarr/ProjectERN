// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Animation/AnimNotifyState_EnemyMeleeHitbox.h"
#include "Components/BoxComponent.h"
#include "Character/Enemy/ERNEnemyCharacter.h"

void UAnimNotifyState_EnemyMeleeHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	SetHitboxEnabled(MeshComp, true);
}

void UAnimNotifyState_EnemyMeleeHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	SetHitboxEnabled(MeshComp, false);

	// 히트박스 비활성화 시 중복 히트 방지 목록 초기화
	AERNEnemyCharacter* Enemy = MeshComp ? Cast<AERNEnemyCharacter>(MeshComp->GetOwner()) : nullptr;
	if (Enemy)
	{
		Enemy->ClearHitActors();
	}
}

void UAnimNotifyState_EnemyMeleeHitbox::SetHitboxEnabled(USkeletalMeshComponent* MeshComp, bool bEnabled)
{
	AERNEnemyCharacter* Character = MeshComp ? Cast<AERNEnemyCharacter>(MeshComp->GetOwner()) : nullptr;
	if (!Character || !Character->HasAuthority()) return;

	TArray<UBoxComponent*> Boxes;
	Character->GetComponents<UBoxComponent>(Boxes);

	for (UBoxComponent* Box : Boxes)
	{
		if (HitboxTag == NAME_None || Box->ComponentHasTag(HitboxTag))
		{
			Box->SetCollisionEnabled(bEnabled ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		}
	}
}
