// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Animation/AnimNotify_SpawnProjectile.h"
#include "Core/Inventory/ERNRangedWeapon.h"
#include "Core/Inventory/ERNEquipmentComponent.h"
#include "GameFramework/Character.h"

void UAnimNotify_SpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	ACharacter* Character = MeshComp ? Cast<ACharacter>(MeshComp->GetOwner()) : nullptr;
	if (!Character || !Character->HasAuthority()) return;

	UERNEquipmentComponent* Equipment = Character->FindComponentByClass<UERNEquipmentComponent>();
	if (!Equipment) return;
	
	// 현재 재생 중인 몽타주가 강공격 몽타주인지 확인
	AERNRangedWeapon* RangedWeapon = Cast<AERNRangedWeapon>(Equipment->CurrentWeapon);
	if (RangedWeapon)
	{
		const bool bIsHeavyAttack = (Animation == RangedWeapon->HeavyAttackMontage);
		RangedWeapon->SpawnProjectile(bIsHeavyAttack);
	}
}
