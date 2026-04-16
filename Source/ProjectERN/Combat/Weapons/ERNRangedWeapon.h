// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Combat/Weapons/ERNWeaponBase.h"
#include "ERNRangedWeapon.generated.h"

class AERNProjectileBase;
class UNiagaraSystem;
class UArrowComponent;

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
	// bIsHeavyAttack: true면 강공격 투사체, false면 약공격 투사체 사용
	UFUNCTION(BlueprintCallable, Category = "Weapon|Ranged")
	void SpawnProjectile(bool bIsHeavyAttack = false);

	// 머즐 이펙트 - 모든 클라이언트에서 재생
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayMuzzleEffect(FVector Location, FRotator Rotation, UNiagaraSystem* Effect);

	// 머즐 포인트 - 에디터에서 위치/회전 직접 지정 (스태틱 메시는 소켓 미지원)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Ranged")
	UArrowComponent* MuzzlePoint;

	// 레거시 호환용 (스켈레탈 메시 사용 시 소켓 이름 지정 가능)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	FName MuzzleSocketName = TEXT("MuzzleSocket");

	// 약공격 투사체 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	TSubclassOf<AERNProjectileBase> LightProjectileClass;

	// 강공격 투사체 클래스 (미설정 시 LightProjectileClass 사용)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	TSubclassOf<AERNProjectileBase> HeavyProjectileClass;

	// 약공격 발사 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	UNiagaraSystem* LightMuzzleEffect;

	// 강공격 발사 이펙트 (미설정 시 LightMuzzleEffect 사용)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Ranged")
	UNiagaraSystem* HeavyMuzzleEffect;
};
