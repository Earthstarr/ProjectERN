// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyStatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Player/ProjectERNPlayerState.h"

void UMyStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// PlayerState 캐시
	if (APlayerController* PC = GetOwningPlayer())
	{
		CachedPlayerState = PC->GetPlayerState<AProjectERNPlayerState>();
	}
}

void UMyStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CachedPlayerState)
	{
		UpdateHealth();
		UpdateMana();
		UpdateStamina();
	}
}

void UMyStatusWidget::UpdateHealth()
{
	float Current = CachedPlayerState->GetCurrentHealth();
	float Max = CachedPlayerState->GetMaxHealth();

	if (HealthBar && Max > 0.f)
	{
		HealthBar->SetPercent(Current / Max);
	}

	if (HealthText)
	{
		FText HealthString = FText::Format(
			FText::FromString("{0} / {1}"),
			FText::AsNumber(FMath::RoundToInt(Current)),
			FText::AsNumber(FMath::RoundToInt(Max))
		);
		HealthText->SetText(HealthString);
	}
}

void UMyStatusWidget::UpdateMana()
{
	float Current = CachedPlayerState->GetCurrentMana();
	float Max = CachedPlayerState->GetMaxMana();

	if (ManaBar && Max > 0.f)
	{
		ManaBar->SetPercent(Current / Max);
	}

	if (ManaText)
	{
		FText ManaString = FText::Format(
			FText::FromString("{0} / {1}"),
			FText::AsNumber(FMath::RoundToInt(Current)),
			FText::AsNumber(FMath::RoundToInt(Max))
		);
		ManaText->SetText(ManaString);
	}
}

void UMyStatusWidget::UpdateStamina()
{
	float Current = CachedPlayerState->GetCurrentStamina();
	float Max = CachedPlayerState->GetMaxStamina();

	if (StaminaBar && Max > 0.f)
	{
		StaminaBar->SetPercent(Current / Max);
	}

	if (StaminaText)
	{
		FText StaminaString = FText::Format(
			FText::FromString("{0} / {1}"),
			FText::AsNumber(FMath::RoundToInt(Current)),
			FText::AsNumber(FMath::RoundToInt(Max))
		);
		StaminaText->SetText(StaminaString);
	}
}
