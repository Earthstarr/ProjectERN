// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "ERNEnemyHealthBarWidget.generated.h"

class UProgressBar;
class AERNEnemyCharacter;

UCLASS()
class PROJECTERN_API UERNEnemyHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 적 캐릭터에서 BeginPlay 시 호출
	UFUNCTION(BlueprintCallable, Category = "HealthBar")
	void InitWidget(AERNEnemyCharacter* OwnerCharacter);

protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

private:
	void OnHealthChanged(const FOnAttributeChangeData& Data);
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);

	float CachedMaxHealth = 100.f;
};
