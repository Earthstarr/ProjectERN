// Copyright Epic Games, Inc. All Rights Reserved.

#include "Combat/Projectile/ERNProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
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
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	CollisionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AERNProjectileBase::OnHit);
	RootComponent = CollisionComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->InitialSpeed = 1200.0f;
	ProjectileMovement->MaxSpeed = 1200.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
	if (OtherActor->IsA<AERNEnemyCharacter>())
	{
		OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), GetOwner());
	}

	// 착탄 이펙트 - 모든 클라이언트에 멀티캐스트
	if (ImpactEffect)
	{
		Multicast_PlayImpactEffect(Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}

	Destroy();
}
