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

	// 플레이어 배열 변경 이벤트 (블루프린트에서 바인딩 가능)
	UPROPERTY(BlueprintAssignable, Category = "GameState")
	FOnPlayerArrayChanged OnPlayerArrayChanged;

protected:
	// PlayerArray 리플리케이션 콜백
	virtual void AddPlayerState(APlayerState* PlayerState) override;
	virtual void RemovePlayerState(APlayerState* PlayerState) override;
};
