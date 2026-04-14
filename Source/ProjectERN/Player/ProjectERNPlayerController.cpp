// Copyright Epic Games, Inc. All Rights Reserved.


#include "Player/ProjectERNPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "ProjectERN.h"
#include "Widgets/Input/SVirtualJoystick.h"
#include "Player/ProjectERNPlayerState.h"
#include "GameFramework/GameStateBase.h"
#include "Core/ERNGameInstance.h"

void AProjectERNPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogProjectERN, Error, TEXT("Could not spawn mobile controls widget."));

		}
	}

	// UI 생성 (로컬 플레이어만)
	if (IsLocalPlayerController() && PartyStatusContainerClass)
	{
		// 현재 맵 이름 가져오기
		FString CurrentMapName = GetWorld()->GetMapName();

		// 숨겨야 할 맵인지 확인
		bool bShouldHide = false;
		for (const FString& MapName : HidePartyWidgetMapNames)
		{
			if (CurrentMapName.Contains(MapName))
			{
				bShouldHide = true;
				break;
			}
		}

		// 숨겨야 할 맵이 아니면 위젯 생성
		if (!bShouldHide)
		{
			UUserWidget* Container = CreateWidget<UUserWidget>(this, PartyStatusContainerClass);
			if (Container)
			{
				Container->AddToViewport();
			}
		}
	}

	// 닉네임 전송 (로컬 플레이어만) - 타이머로 재시도
	if (IsLocalPlayerController())
	{
		// 0.1초 후에 시도 (PlayerState가 준비될 시간 확보)
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectERNPlayerController::TrySendNickname, 0.1f, false);
	}
}

void AProjectERNPlayerController::TrySendNickname()
{
	if (!IsLocalPlayerController())
	{
		return;
	}

	UERNGameInstance* GI = Cast<UERNGameInstance>(GetGameInstance());
	AProjectERNPlayerState* PS = GetPlayerState<AProjectERNPlayerState>();

	UE_LOG(LogTemp, Warning, TEXT("[DEBUG] GI valid: %s, PS valid: %s, Nickname: %s"),
		GI ? TEXT("YES") : TEXT("NO"),
		PS ? TEXT("YES") : TEXT("NO"),
		GI ? *GI->CurrentPlayerNickname : TEXT("GI is null"));

	if (GI && PS && !GI->CurrentPlayerNickname.IsEmpty())
	{
		PS->Server_SetNickname(GI->CurrentPlayerNickname);
		UE_LOG(LogTemp, Log, TEXT("Sending nickname to server: %s"), *GI->CurrentPlayerNickname);
	}
	else if (GI && !GI->CurrentPlayerNickname.IsEmpty())
	{
		// PlayerState가 아직 null이면 0.1초 후 재시도 (최대 50번)
		static int32 RetryCount = 0;
		if (RetryCount < 50)
		{
			RetryCount++;
			UE_LOG(LogTemp, Warning, TEXT("PlayerState not ready, retrying... (Attempt %d/50)"), RetryCount);
			FTimerHandle RetryTimer;
			GetWorld()->GetTimerManager().SetTimer(RetryTimer, this, &AProjectERNPlayerController::TrySendNickname, 0.1f, false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to send nickname: PlayerState never became valid"));
			RetryCount = 0;
		}
	}
}

void AProjectERNPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
}

bool AProjectERNPlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}

