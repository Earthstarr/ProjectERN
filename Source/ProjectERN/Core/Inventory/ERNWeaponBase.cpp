// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Inventory/ERNWeaponBase.h"
#include "Components/StaticMeshComponent.h"

AERNWeaponBase::AERNWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// 무기 메시 생성
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	// 리플리케이션 활성화
	bReplicates = true;
}

void AERNWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}
