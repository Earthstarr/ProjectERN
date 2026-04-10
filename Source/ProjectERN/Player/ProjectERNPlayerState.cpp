// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/ProjectERNPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Player/ProjectERNCharacter.h"
#include "Core/ERNAttributeSet.h"

AProjectERNPlayerState::AProjectERNPlayerState()
{
	// 기본값 - Character의 PossessedBy에서 설정됨
	CharacterType = ECharacterType::Warrior;
}

// Replication 명단
void AProjectERNPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjectERNPlayerState, CharacterType);
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
