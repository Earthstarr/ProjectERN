// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SpawnProjectile.generated.h"

/**
 * UAnimNotify_SpawnProjectile
 * 몽타주에서 발사 타이밍 프레임에 배치
 * Notify 발생 시 → 투사체 스폰 + 나이아가라 이펙트
 */
UCLASS(DisplayName = "Spawn Projectile")
class PROJECTERN_API UAnimNotify_SpawnProjectile : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	virtual FString GetNotifyName_Implementation() const override { return TEXT("Spawn Projectile"); }
};
