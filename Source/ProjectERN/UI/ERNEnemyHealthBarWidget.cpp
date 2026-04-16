// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/ERNEnemyHealthBarWidget.h"
#include "Character/Enemy/ERNEnemyCharacter.h"
#include "GAS/ERNAttributeSet.h"
#include "Components/ProgressBar.h"

void UERNEnemyHealthBarWidget::InitWidget(AERNEnemyCharacter* OwnerCharacter)
{
	if (!OwnerCharacter) return;

	UAbilitySystemComponent* ASC = OwnerCharacter->GetAbilitySystemComponent();
	if (!ASC) return;

	// 초기 MaxHealth 캐싱
	bool bFound = false;
	CachedMaxHealth = ASC->GetGameplayAttributeValue(UERNAttributeSet::GetMaxHealthAttribute(), bFound);
	if (CachedMaxHealth <= 0.f) CachedMaxHealth = 100.f;

	// 초기 체력바 퍼센트 설정
	float CurrentHealth = ASC->GetGameplayAttributeValue(UERNAttributeSet::GetHealthAttribute(), bFound);
	if (HealthBar)
	{
		HealthBar->SetPercent(CurrentHealth / CachedMaxHealth);
	}

	// Attribute 변경 Delegate 바인딩
	ASC->GetGameplayAttributeValueChangeDelegate(UERNAttributeSet::GetHealthAttribute())
		.AddUObject(this, &UERNEnemyHealthBarWidget::OnHealthChanged);

	ASC->GetGameplayAttributeValueChangeDelegate(UERNAttributeSet::GetMaxHealthAttribute())
		.AddUObject(this, &UERNEnemyHealthBarWidget::OnMaxHealthChanged);
}

void UERNEnemyHealthBarWidget::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Data.NewValue / CachedMaxHealth);
	}
}

void UERNEnemyHealthBarWidget::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	CachedMaxHealth = Data.NewValue > 0.f ? Data.NewValue : 100.f;

	// MaxHealth 변경 시 현재 퍼센트 재계산
	if (HealthBar)
	{
		HealthBar->SetPercent(HealthBar->GetPercent() * (Data.OldValue / CachedMaxHealth));
	}
}
