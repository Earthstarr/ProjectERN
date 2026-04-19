// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERNProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UStaticMeshComponent;

/**
 * AERNProjectileBase - 원거리 투사체 베이스
 */
UCLASS()
class PROJECTERN_API AERNProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	AERNProjectileBase();

protected:
	virtual void BeginPlay() override;

	// 충돌 처리
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	// 충돌 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	USphereComponent* CollisionComponent;

	// 투사체 비주얼 메시 (화살, 마법구 등)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UStaticMeshComponent* ProjectileMesh;

	// 이동 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovement;

	// 비행 중 나이아가라 이펙트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* TrailEffect;

	// 착탄 시 나이아가라 이펙트
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraSystem* ImpactEffect;

	// 착탄 이펙트 - 모든 클라이언트에서 재생
	UFUNCTION(NetMulticast, Unreliable)
	void Multicast_PlayImpactEffect(FVector Location, FRotator Rotation);

	// 데미지 (무기의 AttackDamage가 여기로 전달됨)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float Damage = 20.0f;

	// 경직력 (BP_투사체마다 다르게 설정)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	float StaggerPower = 15.f;
};
