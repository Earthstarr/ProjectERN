// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectERNPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;
class AProjectERNPlayerState;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */

UCLASS(abstract)
class AProjectERNPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	UPROPERTY()
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** If true, the player will use UMG touch controls even if not playing on mobile platforms */
	UPROPERTY(EditAnywhere, Config, Category = "Input|Touch Controls")
	bool bForceTouchControls = false;

	// UI (통합 위젯)
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PartyStatusContainerClass;

	// 파티 상태 위젯을 숨길 맵 이름 목록 (부분 일치)
	UPROPERTY(EditAnywhere, Category = "UI")
	TArray<FString> HidePartyWidgetMapNames;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	// UI 생성 (약간 지연)
	void CreatePartyUI();

	// 닉네임 전송 재시도 (PlayerState가 준비될 때까지)
	void TrySendNickname();

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	/** Returns true if the player should use UMG touch controls */
	bool ShouldUseTouchControls() const;

};
