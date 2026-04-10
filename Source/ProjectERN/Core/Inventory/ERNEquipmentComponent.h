// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ERNEquipmentComponent.generated.h"

class AERNWeaponBase;

/**
 * ERNEquipmentComponent - 장비 관리 (무기 장착/해제)
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTERN_API UERNEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UERNEquipmentComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

public:
	// 현재 장착된 무기
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Equipment")
	AERNWeaponBase* CurrentWeapon;

	// 무기 장착
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Equipment")
	void Server_EquipWeapon(TSubclassOf<AERNWeaponBase> WeaponClass);

	// 무기 해제
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Equipment")
	void Server_UnequipWeapon();
};
