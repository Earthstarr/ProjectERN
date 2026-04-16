// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/ERNGameState.h"
#include "GameFramework/PlayerState.h"
#include "Player/ERNPlayerState.h"

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

void AERNGameState::CheckAllPlayersReady()
{
	// 서버에서만 실행
	if (!HasAuthority())
	{
		return;
	}

	// 플레이어가 없으면 체크하지 않음
	if (PlayerArray.Num() == 0)
	{
		return;
	}

	// 모든 플레이어가 준비됐는지 확인
	bool bAllReady = true;
	for (APlayerState* PS : PlayerArray)
	{
		if (AERNPlayerState* ERNPlayerState = Cast<AERNPlayerState>(PS))
		{
			if (!ERNPlayerState->bIsReady)
			{
				bAllReady = false;
				UE_LOG(LogTemp, Log, TEXT("Player %s is not ready yet"), *ERNPlayerState->PlayerNickname);
				break;
			}
		}
	}

	// 모두 준비되면 필드맵으로 이동
	if (bAllReady)
	{
		UE_LOG(LogTemp, Log, TEXT("All players ready! Traveling to field map: %s"), *FieldMapName);

		// 방송
		OnAllPlayersReady.Broadcast();

		if (UWorld* World = GetWorld())
		{
			World->ServerTravel(FieldMapName + TEXT("?listen"));
		}
	}
}
