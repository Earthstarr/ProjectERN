// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Inventory/ERNEquipmentComponent.h"
#include "Core/Inventory/ERNWeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UERNEquipmentComponent::UERNEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UERNEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UERNEquipmentComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UERNEquipmentComponent, CurrentWeapon);
}

void UERNEquipmentComponent::Server_EquipWeapon_Implementation(TSubclassOf<AERNWeaponBase> WeaponClass)
{
	// 기존 무기 제거
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	// 새 무기 스폰
	if (WeaponClass)
	{
		AActor* Owner = GetOwner();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Owner;

		CurrentWeapon = GetWorld()->SpawnActor<AERNWeaponBase>(WeaponClass, SpawnParams);

		// 캐릭터 메시에 부착
		if (CurrentWeapon && Owner)
		{
			ACharacter* Character = Cast<ACharacter>(Owner);
			if (Character && Character->GetMesh())
			{
				CurrentWeapon->AttachToComponent(
					Character->GetMesh(),
					FAttachmentTransformRules::SnapToTargetIncludingScale,
					FName("WeaponSocket")
				);

				UE_LOG(LogTemp, Log, TEXT("Weapon equipped: %s"), *WeaponClass->GetName());
			}
		}
	}
}

void UERNEquipmentComponent::Server_UnequipWeapon_Implementation()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
		UE_LOG(LogTemp, Log, TEXT("Weapon unequipped"));
	}
}
