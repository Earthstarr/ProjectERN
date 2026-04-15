// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/CharacterSelectionWidget.h"
#include "Player/ProjectERNPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "Core/ERNGameInstance.h"

void UCharacterSelectionWidget::ConfirmSelection()
{
	// PlayerController 가져오기
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		return;
	}

	// PlayerState 가져오기
	AProjectERNPlayerState* PS = PC->GetPlayerState<AProjectERNPlayerState>();
	if (!PS)
	{
		return;
	}

	// 클라이언트의 GameInstance에 저장 (맵 이동 시 유지되도록)
	if (UERNGameInstance* GI = Cast<UERNGameInstance>(PC->GetGameInstance()))
	{
		GI->SetPlayerCharacterType(SelectedCharacterType);
		UE_LOG(LogTemp, Log, TEXT("[Client] Saved CharacterType to GameInstance: %d"), static_cast<int32>(SelectedCharacterType));
	}

	// 서버에 캐릭터 변경 요청
	PS->Server_ChangeCharacterClass(SelectedCharacterType);

	// 입력 모드 복원 (게임 전용 모드로 변경하여 마우스 회전 가능하게)
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetShowMouseCursor(false);

	// 위젯 닫기
	RemoveFromParent();
}

void UCharacterSelectionWidget::CancelSelection()
{
	// PlayerController 가져오기
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		return;
	}

	// 입력 모드 복원 (게임 전용 모드로 변경하여 마우스 회전 가능하게)
	PC->SetInputMode(FInputModeGameOnly());
	PC->SetShowMouseCursor(false);

	// 위젯 닫기
	RemoveFromParent();
}

ECharacterType UCharacterSelectionWidget::GetCurrentCharacterType() const
{
	// PlayerController 가져오기
	APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		return ECharacterType::None;
	}

	// PlayerState 가져오기
	AProjectERNPlayerState* PS = PC->GetPlayerState<AProjectERNPlayerState>();
	if (!PS)
	{
		return ECharacterType::None;
	}

	// 현재 캐릭터 타입 반환
	return PS->CharacterType;
}
