// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Inventory/ERNRangedWeapon.h"
#include "Core/Combat/ERNProjectileBase.h"
#include "NiagaraFunctionLibrary.h"

AERNRangedWeapon::AERNRangedWeapon()
{
}

void AERNRangedWeapon::SpawnProjectile()
{
	if (!ProjectileClass || !GetOwner())
	{
		return;
	}

	// 발사구 위치/방향 계산
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetOwner()->GetActorRotation();

	// 무기 메시에 MuzzleSocket이 있으면 해당 위치 사용
	if (WeaponMesh && WeaponMesh->DoesSocketExist(MuzzleSocketName))
	{
		SpawnLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		SpawnRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}

	// 나이아가라 이펙트 - 모든 클라이언트에 멀티캐스트
	if (MuzzleEffect)
	{
		Multicast_PlayMuzzleEffect(SpawnLocation, SpawnRotation);
	}

	// 투사체 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AERNProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
}

void AERNRangedWeapon::Multicast_PlayMuzzleEffect_Implementation(FVector Location, FRotator Rotation)
{
	if (MuzzleEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleEffect, Location, Rotation);
	}
}
