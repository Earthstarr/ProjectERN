// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "ERNGameInstance.generated.h"

UCLASS()
class PROJECTERN_API UERNGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UERNGameInstance();

	virtual void Init() override;

	// 세션 생성 (Host)
	UFUNCTION(BlueprintCallable, Category = "Network")
	void HostSession(FString ServerName, int32 MaxPlayers = 3);

	// 세션 검색
	UFUNCTION(BlueprintCallable, Category = "Network")
	void FindSessions();

	// 세션 참가 (Join)
	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinSessionByIndex(int32 SessionIndex);

	// IP로 직접 접속
	UFUNCTION(BlueprintCallable, Category = "Network")
	void JoinByIP(FString IPAddress);

	// 현재 세션 나가기
	UFUNCTION(BlueprintCallable, Category = "Network")
	void LeaveSession();

	// 블루프린트에서 세션 목록 가져오기
	UFUNCTION(BlueprintPure, Category = "Network")
	TArray<FString> GetSessionList() const { return SessionSearchResults; }

protected:
	// 세션 인터페이스
	IOnlineSessionPtr SessionInterface;

	// 세션 검색 결과
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// 블루프린트용 검색 결과
	UPROPERTY(BlueprintReadOnly, Category = "Network")
	TArray<FString> SessionSearchResults;

	// 세션 생성 완료 콜백
	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	// 세션 검색 완료 콜백
	void OnFindSessionsComplete(bool bWasSuccessful);

	// 세션 참가 완료 콜백
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	// 세션 파괴 완료 콜백
	void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	// Delegate Handles
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	// 생성할 세션 정보 임시 저장
	FString PendingServerName;
	int32 PendingMaxPlayers;
};
