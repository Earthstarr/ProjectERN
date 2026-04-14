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

	// 플레이어 닉네임
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Info")
	FString PlayerNickname;

	// 준비 상태 (로비용)
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Player Info")
	bool bIsReady;

	// 블루프린트에서 닉네임 설정 (자동으로 서버 RPC 호출)
	UFUNCTION(BlueprintCallable, Category = "Player Info")
	void SetNickname(const FString& Nickname);

	// 서버에 닉네임 설정 요청
	UFUNCTION(Server, Reliable)
	void Server_SetNickname(const FString& Nickname);

	// 서버에 준비 상태 설정 요청
	UFUNCTION(Server, Reliable)
	void Server_SetReady(bool bReady);

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
