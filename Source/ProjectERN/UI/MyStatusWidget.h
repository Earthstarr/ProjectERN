// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyStatusWidget.generated.h"

class UProgressBar;
class UTextBlock;
class AProjectERNPlayerState;

UCLASS()
class PROJECTERN_API UMyStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	// 위젯 바인딩
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* HealthText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ManaText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* StaminaText;

	// 캐시된 PlayerState
	UPROPERTY()
	AProjectERNPlayerState* CachedPlayerState;

	void UpdateHealth();
	void UpdateMana();
	void UpdateStamina();
};
