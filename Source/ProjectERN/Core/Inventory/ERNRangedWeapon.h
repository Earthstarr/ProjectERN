// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/ERNWeaponBase.h"
#include "ERNRangedWeapon.generated.h"

class AERNProjectileBase;
class UNiagaraSystem;

/**
 * AERNRangedWeapon - 원거리 무기
 * 투사체 스폰은 AnimNotify_SpawnProjectile에서 호출
 */
UCLASS()
class PROJECTERN_API AERNRangedWeapon : public AERNWeaponBase
{
	GENERATED_BODY()

public:
	AERNRangedWeapon();

	// 투사체 스폰 (AnimNotify_SpawnProjectile에서 호출)
	UFUNCTION(BlueprintCallable, Category = "Weapon|Ranged")
	void SpawnProjectile();

	// 머즐 이펙트 - 모든 클라이언트에서 재생
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayMuzzleEffect(FVector Location, FRotator Rotation);

	// 머즐 소켓
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	FName MuzzleSocketName = TEXT("MuzzleSocket");

	// 스폰할 투사체 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	TSubclassOf<AERNProjectileBase> ProjectileClass;

	// 발사 시 나이아가라 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	UNiagaraSystem* MuzzleEffect;
};
