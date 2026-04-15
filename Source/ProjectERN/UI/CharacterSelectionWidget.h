// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Player/ProjectERNPlayerState.h"
#include "CharacterSelectionWidget.generated.h"

/**
 * 캐릭터 클래스 선택 위젯
 */
UCLASS()
class PROJECTERN_API UCharacterSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 선택한 캐릭터 타입
	UPROPERTY(BlueprintReadWrite, Category = "Character Selection")
	ECharacterType SelectedCharacterType;

	// 확인 버튼 클릭 시 호출
	UFUNCTION(BlueprintCallable, Category = "Character Selection")
	void ConfirmSelection();

	// 취소 버튼 클릭 시 호출
	UFUNCTION(BlueprintCallable, Category = "Character Selection")
	void CancelSelection();

	// 현재 플레이어의 캐릭터 타입 가져오기
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character Selection")
	ECharacterType GetCurrentCharacterType() const;
};
