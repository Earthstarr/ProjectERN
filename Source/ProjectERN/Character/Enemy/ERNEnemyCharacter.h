// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/ERNCharacterBase.h"
#include "ERNEnemyCharacter.generated.h"

class UWidgetComponent;


 // 드랍 아이템 정보 
USTRUCT(BlueprintType)
struct FDropItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DropChance = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCount = 1;
};

UCLASS(Abstract)
class PROJECTERN_API AERNEnemyCharacter : public AERNCharacterBase
{
	GENERATED_BODY()

public:
	AERNEnemyCharacter();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 체력바 표시 (피격/락온 시 호출)
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowHealthBar();

	// 체력바 숨김
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideHealthBar();

protected:
	virtual void BeginPlay() override;

	// 사망 처리 오버라이드
	virtual void OnDeath() override;

	// 머리 위 체력바 위젯 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* HealthBarWidget;

	// 피격 후 체력바 자동 숨김까지 대기 시간 (블루프린트에서 수정 가능)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	float HealthBarHideDelay = 3.0f;

private:
	FTimerHandle HealthBarHideTimerHandle;

public:
	// 드롭 테이블
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	TArray<FDropItemInfo> DropTable;

	// 골드 보상
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	int32 MinGold = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	int32 MaxGold = 50;

	// 경험치 보상
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drops")
	int32 ExpReward = 100;

	// 탐지 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float DetectionRange = 1000.0f;

	// 공격 범위
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AttackRange = 200.0f;

protected:
	// 드랍 처리
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void SpawnDrops();

	// 골드 드롭
	UFUNCTION(BlueprintCallable, Category = "Enemy")
	virtual void SpawnGold();
};
