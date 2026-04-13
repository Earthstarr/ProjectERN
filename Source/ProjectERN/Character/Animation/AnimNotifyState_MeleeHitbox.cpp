// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Animation/AnimNotifyState_MeleeHitbox.h"
#include "Core/Inventory/ERNMeleeWeapon.h"
#include "Core/Inventory/ERNEquipmentComponent.h"
#include "GameFramework/Character.h"

void UAnimNotifyState_MeleeHitbox::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACharacter* Character = MeshComp ? Cast<ACharacter>(MeshComp->GetOwner()) : nullptr;
	if (!Character || !Character->HasAuthority()) return;

	UERNEquipmentComponent* Equipment = Character->FindComponentByClass<UERNEquipmentComponent>();
	if (!Equipment) return;

	AERNMeleeWeapon* MeleeWeapon = Cast<AERNMeleeWeapon>(Equipment->CurrentWeapon);
	if (MeleeWeapon)
	{
		MeleeWeapon->EnableHitbox();
	}
}

void UAnimNotifyState_MeleeHitbox::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACharacter* Character = MeshComp ? Cast<ACharacter>(MeshComp->GetOwner()) : nullptr;
	if (!Character || !Character->HasAuthority()) return;

	UERNEquipmentComponent* Equipment = Character->FindComponentByClass<UERNEquipmentComponent>();
	if (!Equipment) return;

	AERNMeleeWeapon* MeleeWeapon = Cast<AERNMeleeWeapon>(Equipment->CurrentWeapon);
	if (MeleeWeapon)
	{
		MeleeWeapon->DisableHitbox();
	}
}
