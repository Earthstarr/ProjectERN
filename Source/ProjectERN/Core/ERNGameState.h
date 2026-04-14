// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ERNGameState.generated.h"

// 플레이어 배열 변경 시 호출되는 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerArrayChanged);

UCLASS()
class PROJECTERN_API AERNGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AERNGameState();

	// 플레이어 배열 변경 이벤트
	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnPlayerArrayChanged OnPlayerArrayChanged;

	// 모든 플레이어 준비 상태 확인 (서버에서만 호출)
	void CheckAllPlayersReady();

	// 필드맵 이름 (블루프린트에서 설정 가능, 예: "Map_Field")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	FString FieldMapName = TEXT("Map_Field");

protected:
	// PlayerArray 리플리케이션 콜백
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
