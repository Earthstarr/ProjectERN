// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/ERNGameState.h"
#include "GameFramework/PlayerState.h"

AERNGameState::AERNGameState()
{
}

void AERNGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	// 플레이어가 추가되면 델리게이트 브로드캐스트
	UE_LOG(LogTemp, Log, TEXT("Player added to GameState. Total players: %d"), PlayerArray.Num());
	OnPlayerArrayChanged.Broadcast();
}

void AERNGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);

	// 플레이어가 제거되면 델리게이트 브로드캐스트
	UE_LOG(LogTemp, Log, TEXT("Player removed from GameState. Total players: %d"), PlayerArray.Num());
	OnPlayerArrayChanged.Broadcast();
}
