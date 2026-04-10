// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ERNCharacterBase.generated.h"


class UAbilitySystemComponent;
class UERNAttributeSet;


UCLASS(Abstract)
class PROJECTERN_API AERNCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AERNCharacterBase();

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// AttributeSet 가져오기
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	UERNAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	// GAS 컴포넌트들
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UERNAttributeSet> AttributeSet;

	// 사망 처리
	UFUNCTION(BlueprintCallable, Category = "Character")
	virtual void OnDeath();

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool bIsDead = false;

public:
	// 데미지 처리
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsDead() const { return bIsDead; }
};
