// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ProjectERNPlayerState.generated.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	Warrior,
	Support,
	Mage
};

UCLASS()
class PROJECTERN_API AProjectERNPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AProjectERNPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 캐릭터 타입
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Character")
	ECharacterType CharacterType;

	// AttributeSet에서 HP/MP/Stamina 가져오기 (블루프린트용 헬퍼)
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetCurrentMana() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetCurrentStamina() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes")
	float GetMaxStamina() const;
};
