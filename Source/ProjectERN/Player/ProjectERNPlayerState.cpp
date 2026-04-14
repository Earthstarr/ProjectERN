// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ProjectERNPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Character/Player/ProjectERNCharacter.h"
#include "Core/ERNAttributeSet.h"

AProjectERNPlayerState::AProjectERNPlayerState()
{
	// 기본값 - Character의 PossessedBy에서 설정됨
	CharacterType = ECharacterType::Warrior;
	PlayerNickname = TEXT("Player");
	bIsReady = false;
}

// Replication 명단
void AProjectERNPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectERNPlayerState, CharacterType);
	DOREPLIFETIME(AProjectERNPlayerState, PlayerNickname);
	DOREPLIFETIME(AProjectERNPlayerState, bIsReady);
}

void AProjectERNPlayerState::SetNickname(const FString& Nickname)
{
	Server_SetNickname(Nickname);
}

void AProjectERNPlayerState::Server_SetNickname_Implementation(const FString& Nickname)
{
	if (!Nickname.IsEmpty() && Nickname.Len() <= 20)
	{
		PlayerNickname = Nickname;
		UE_LOG(LogTemp, Log, TEXT("Player nickname set to: %s"), *PlayerNickname);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid nickname: %s"), *Nickname);
	}
}

void AProjectERNPlayerState::Server_SetReady_Implementation(bool bReady)
{
	bIsReady = bReady;
	UE_LOG(LogTemp, Log, TEXT("Player %s ready state: %s"), *PlayerNickname, bIsReady ? TEXT("Ready") : TEXT("Not Ready"));
}

// AttributeSet에서 값 가져오기
float AProjectERNPlayerState::GetCurrentHealth() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetHealth();
			}
		}
	}
	return 0.f;
}

float AProjectERNPlayerState::GetMaxHealth() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetMaxHealth();
			}
		}
	}
	return 100.f;
}

float AProjectERNPlayerState::GetCurrentMana() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetMana();
			}
		}
	}
	return 0.f;
}

float AProjectERNPlayerState::GetMaxMana() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetMaxMana();
			}
		}
	}
	return 100.f;
}

float AProjectERNPlayerState::GetCurrentStamina() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetStamina();
			}
		}
	}
	return 0.f;
}

float AProjectERNPlayerState::GetMaxStamina() const
{
	if (APawn* Pawn = GetPawn())
	{
		if (AProjectERNCharacter* Character = Cast<AProjectERNCharacter>(Pawn))
		{
			if (const UERNAttributeSet* AS = Character->GetAttributeSet())
			{
				return AS->GetMaxStamina();
			}
		}
	}
	return 100.f;
}
