// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/Enemy/ERNEnemyCharacter.h"
#include "GAS/ERNAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/ERNEnemyHealthBarWidget.h"

AERNEnemyCharacter::AERNEnemyCharacter()
{
	// AI가 자동으로 빙의하도록 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 적은 기본적으로 회전하지 않음
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);

	// 머리 위 체력바 위젯 컴포넌트
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBarWidget"));
	HealthBarWidget->SetupAttachment(RootComponent);
	HealthBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 120.0f));
	HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidget->SetDrawSize(FVector2D(150.0f, 20.0f));
	HealthBarWidget->SetVisibility(false);
}

void AERNEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 서버에서만 GAS 초기화
	if (HasAuthority() && AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	// 체력바 위젯 초기화
	if (HealthBarWidget)
	{
		if (UERNEnemyHealthBarWidget* Widget = Cast<UERNEnemyHealthBarWidget>(HealthBarWidget->GetUserWidgetObject()))
		{
			Widget->InitWidget(this);
		}
	}
}

float AERNEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		Multicast_ShowHealthBar();
	}

	return ActualDamage;
}

void AERNEnemyCharacter::Multicast_ShowHealthBar_Implementation()
{
	if (!HealthBarWidget) return;

	HealthBarWidget->SetVisibility(true);

	// 기존 타이머 초기화 후 재시작
	GetWorld()->GetTimerManager().SetTimer(
		HealthBarHideTimerHandle,
		this,
		&AERNEnemyCharacter::Multicast_HideHealthBar,
		HealthBarHideDelay,
		false
	);
}

void AERNEnemyCharacter::Multicast_HideHealthBar_Implementation()
{
	if (!HealthBarWidget) return;

	HealthBarWidget->SetVisibility(false);
}

void AERNEnemyCharacter::OnDeath()
{
	Super::OnDeath();

	if (HasAuthority())
	{
		// 골드 드롭
		SpawnGold();

		// 아이템 드롭
		SpawnDrops();

		// 3초 후 제거
		FTimerHandle DestroyTimer;
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer, [this]()
		{
			Destroy();
		}, 3.0f, false);
	}
}

void AERNEnemyCharacter::SpawnDrops()
{
	// TODO: 드롭 테이블 기반으로 아이템 스폰
	for (const FDropItemInfo& DropInfo : DropTable)
	{
		float RandomValue = FMath::FRand();
		if (RandomValue <= DropInfo.DropChance)
		{
			int32 DropCount = FMath::RandRange(DropInfo.MinCount, DropInfo.MaxCount);
			UE_LOG(LogTemp, Log, TEXT("Dropped %s x%d"), *DropInfo.ItemID.ToString(), DropCount);
		}
	}
}

void AERNEnemyCharacter::SpawnGold()
{
	int32 GoldAmount = FMath::RandRange(MinGold, MaxGold);
	UE_LOG(LogTemp, Log, TEXT("%s dropped %d gold"), *GetName(), GoldAmount);

	// TODO: 골드 스폰
}
