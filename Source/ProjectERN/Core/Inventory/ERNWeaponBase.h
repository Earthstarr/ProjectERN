// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ERNWeaponBase.generated.h"

/**
 * ERNWeaponBase - 무기 베이스 클래스
 */
UCLASS(Abstract)
class PROJECTERN_API AERNWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AERNWeaponBase();

protected:
	virtual void BeginPlay() override;

public:
	// 무기 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* WeaponMesh;

	// 무기 스탯
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float LightAttackDamage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float HeavyAttackDamage = 20.0f;

	// 무기 전용 애니메이션 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Animations")
	UAnimMontage* LightAttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Animations")
	UAnimMontage* HeavyAttackMontage;
};
