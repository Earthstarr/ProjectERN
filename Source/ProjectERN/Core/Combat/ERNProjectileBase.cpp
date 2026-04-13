// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Combat/ERNProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/DamageEvents.h"
#include "Character/Enemy/ERNEnemyCharacter.h"

AERNProjectileBase::AERNProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AERNProjectileBase::OnHit);
	RootComponent = CollisionComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.1f;

	TrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(RootComponent);

	InitialLifeSpan = 5.0f;
}

void AERNProjectileBase::Multicast_PlayImpactEffect_Implementation(FVector Location, FRotator Rotation)
{
	if (ImpactEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, Location, Rotation);
	}
}

void AERNProjectileBase::BeginPlay()
{
	Super::BeginPlay();
}

void AERNProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!HasAuthority()) return;

	if (!OtherActor || OtherActor == GetOwner())
	{
		return;
	}
	
	// 적 캐릭터에게만 데미지 적용
	if (!OtherActor->IsA<AERNEnemyCharacter>())
	{
		return;
	}

	// 데미지 적용
	OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), GetOwner());

	// 착탄 이펙트 - 모든 클라이언트에 멀티캐스트
	if (ImpactEffect)
	{
		Multicast_PlayImpactEffect(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	Destroy();
}
