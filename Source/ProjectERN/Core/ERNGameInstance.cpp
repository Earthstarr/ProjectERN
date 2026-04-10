// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/ERNGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Interfaces/OnlineSessionInterface.h"

UERNGameInstance::UERNGameInstance()
{
	PendingMaxPlayers = 3;
}

void UERNGameInstance::Init()
{
	Super::Init();

	// 온라인 서브시스템 가져오기
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			// Delegate 바인딩
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UERNGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UERNGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UERNGameInstance::OnJoinSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UERNGameInstance::OnDestroySessionComplete);
		}
	}
}

void UERNGameInstance::HostSession(FString ServerName, int32 MaxPlayers)
{
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionInterface is not valid!"));
		return;
	}

	// 기존 세션이 있으면 먼저 파괴
	auto ExistingSession = SessionInterface->GetNamedSession(NAME_GameSession);
	if (ExistingSession)
	{
		PendingServerName = ServerName;
		PendingMaxPlayers = MaxPlayers;
		SessionInterface->DestroySession(NAME_GameSession);
		return;
	}

	// 세션 설정
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.NumPublicConnections = MaxPlayers;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = false;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bAllowJoinViaPresence = true;

	// 커스텀 세션 정보 (서버 이름)
	SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

	// 세션 생성
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->CreateSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionSettings);
}

void UERNGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session created successfully!"));

		// 로비 레벨로 이동		
		if (GetWorld())
		{
			GetWorld()->ServerTravel("/Game/Assets/Maps/Map_Lobby?listen");
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to create session!"));
	}
}

void UERNGameInstance::FindSessions()
{
	if (!SessionInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("SessionInterface is not valid!"));
		return;
	}

	// 세션 검색 설정
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true;
	SessionSearch->MaxSearchResults = 20;

	UE_LOG(LogTemp, Log, TEXT("Starting session search..."));

	// 세션 검색 시작
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->FindSessions(*LocalPlayer->GetPreferredUniqueNetId(), SessionSearch.ToSharedRef());
}

void UERNGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
	SessionSearchResults.Empty();

	UE_LOG(LogTemp, Log, TEXT("OnFindSessionsComplete - Success: %s"), bWasSuccessful ? TEXT("true") : TEXT("false"));

	if (bWasSuccessful && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Log, TEXT("Found %d sessions"), SessionSearch->SearchResults.Num());

		// 검색 결과를 배열에 저장
		for (int32 i = 0; i < SessionSearch->SearchResults.Num(); i++)
		{
			FString ServerName;
			SessionSearch->SearchResults[i].Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName);

			int32 CurrentPlayers = SessionSearch->SearchResults[i].Session.SessionSettings.NumPublicConnections - SessionSearch->SearchResults[i].Session.NumOpenPublicConnections;
			int32 MaxPlayers = SessionSearch->SearchResults[i].Session.SessionSettings.NumPublicConnections;

			FString SessionInfo = FString::Printf(TEXT("%s (%d/%d)"), *ServerName, CurrentPlayers, MaxPlayers);
			SessionSearchResults.Add(SessionInfo);

			UE_LOG(LogTemp, Log, TEXT("Session %d: %s - Ping: %d"), i, *SessionInfo, SessionSearch->SearchResults[i].PingInMs);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find sessions! SearchValid: %s"), SessionSearch.IsValid() ? TEXT("true") : TEXT("false"));
	}
}

void UERNGameInstance::JoinSessionByIndex(int32 SessionIndex)
{
	if (!SessionInterface.IsValid() || !SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot join session!"));
		return;
	}

	if (SessionIndex < 0 || SessionIndex >= SessionSearch->SearchResults.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid session index!"));
		return;
	}

	// 세션 참가
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->JoinSession(*LocalPlayer->GetPreferredUniqueNetId(), NAME_GameSession, SessionSearch->SearchResults[SessionIndex]);
}

void UERNGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (Result == EOnJoinSessionCompleteResult::Success)
	{
		UE_LOG(LogTemp, Log, TEXT("Joined session successfully!"));

		// 서버 연결
		FString ConnectInfo;
		if (SessionInterface->GetResolvedConnectString(SessionName, ConnectInfo))
		{
			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (PC)
			{
				PC->ClientTravel(ConnectInfo, TRAVEL_Absolute);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to join session!"));
	}
}

void UERNGameInstance::LeaveSession()
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->DestroySession(NAME_GameSession);
	}
}

void UERNGameInstance::OnDestroySessionComplete(FName SessionName, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		UE_LOG(LogTemp, Log, TEXT("Session destroyed successfully!"));

		// 세션 파괴 후 Host 재시도 (있으면)
		if (!PendingServerName.IsEmpty())
		{
			HostSession(PendingServerName, PendingMaxPlayers);
			PendingServerName.Empty();
		}
	}
}

void UERNGameInstance::JoinByIP(FString IPAddress)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		FString TravelURL = IPAddress;
		if (!IPAddress.Contains(":"))
		{
			TravelURL += ":7777";
		}

		UE_LOG(LogTemp, Log, TEXT("Joining by IP: %s"), *TravelURL);
		PC->ClientTravel(TravelURL, TRAVEL_Absolute);
	}
}
