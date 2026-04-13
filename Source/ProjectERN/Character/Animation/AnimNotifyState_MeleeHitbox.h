// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_MeleeHitbox.generated.h"

/**
 * UAnimNotifyState_MeleeHitbox
 * 몽타주에서 히트박스를 활성화할 구간에 배치
 * NotifyBegin → 히트박스 ON / NotifyEnd → 히트박스 OFF
 */
UCLASS(DisplayName = "Melee Hitbox")
class PROJECTERN_API UAnimNotifyState_MeleeHitbox : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override { return TEXT("Melee Hitbox"); }
};
