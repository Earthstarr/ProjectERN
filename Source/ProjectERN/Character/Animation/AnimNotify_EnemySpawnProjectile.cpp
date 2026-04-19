// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Animation/AnimNotify_EnemySpawnProjectile.h"
#include "Character/Enemy/ERNEnemyCharacter.h"
#include "Combat/Projectile/ERNProjectileBase.h"

void UAnimNotify_EnemySpawnProjectile::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AERNEnemyCharacter* Enemy = MeshComp ? Cast<AERNEnemyCharacter>(MeshComp->GetOwner()) : nullptr;
	if (!Enemy || !Enemy->HasAuthority()) return;

	// 태그 일치하는 투사체 설정 검색
	const FEnemyProjectileConfig* Config = Enemy->ProjectileConfigs.FindByPredicate(
		[this](const FEnemyProjectileConfig& C) { return C.Tag == ProjectileTag; }
	);

	if (!Config || !Config->ProjectileClass) return;

	// 소켓 위치/회전으로 스폰
	FVector SpawnLocation = Enemy->GetMesh()->GetSocketLocation(Config->SpawnSocket);
	FRotator SpawnRotation = Enemy->GetActorRotation();

	FActorSpawnParameters Params;
	Params.Instigator = Enemy;
	Params.Owner = Enemy;

	Enemy->GetWorld()->SpawnActor<AERNProjectileBase>(Config->ProjectileClass, SpawnLocation, SpawnRotation, Params);
}
