// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_EnemyMeleeHitbox.generated.h"

/**
 * 적 전용 근접 히트박스 NotifyState
 * HitboxTag와 일치하는 BoxComponent를 찾아 ON/OFF
 * BP에서 BoxComponent에 태그를 부여
 */
UCLASS(DisplayName = "Enemy Melee Hitbox")
class PROJECTERN_API UAnimNotifyState_EnemyMeleeHitbox : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override { return TEXT("Enemy Melee Hitbox"); }

	// 활성화할 BoxComponent의 태그 (BP마다 다르게 설정)
	UPROPERTY(EditAnywhere, Category = "Hitbox")
	FName HitboxTag = NAME_None;

private:
	void SetHitboxEnabled(USkeletalMeshComponent* MeshComp, bool bEnabled);
};
