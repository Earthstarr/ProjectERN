// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/ProjectERNGameMode.h"
#include "Player/ProjectERNPlayerState.h"
#include "Character/Player/ProjectERNCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Core/ERNGameInstance.h"

AProjectERNGameMode::AProjectERNGameMode()
{
}

UClass* AProjectERNGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	// PlayerController에서 PlayerState 가져오기
	if (APlayerController* PC = Cast<APlayerController>(InController))
	{
		if (AProjectERNPlayerState* PS = PC->GetPlayerState<AProjectERNPlayerState>())
		{
			// PlayerState의 CharacterType이 None인 경우, GameInstance에서 복원 시도
			if (PS->CharacterType == ECharacterType::None)
			{
				if (UERNGameInstance* GI = Cast<UERNGameInstance>(GetGameInstance()))
				{
					ECharacterType SavedType = GI->GetPlayerCharacterType();
					if (SavedType != ECharacterType::None)
					{
						PS->CharacterType = SavedType;
						UE_LOG(LogTemp, Warning, TEXT("[GetDefaultPawnClassForController] Restored CharacterType from GameInstance: %d"), static_cast<int32>(SavedType));
					}
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("[GetDefaultPawnClassForController] Player %s has CharacterType: %d"), *PS->PlayerNickname, static_cast<int32>(PS->CharacterType));

			// PlayerState의 CharacterType에 따라 적절한 캐릭터 클래스 반환
			UClass* SelectedClass = nullptr;

			switch (PS->CharacterType)
			{
			case ECharacterType::Warrior:
				SelectedClass = PS->WarriorClass.Get();
				if (SelectedClass)
				{
					UE_LOG(LogTemp, Log, TEXT("Spawning Warrior for %s"), *PS->PlayerNickname);
					return SelectedClass;
				}
				break;
			case ECharacterType::Mage:
				SelectedClass = PS->MageClass.Get();
				if (SelectedClass)
				{
					UE_LOG(LogTemp, Log, TEXT("Spawning Mage for %s"), *PS->PlayerNickname);
					return SelectedClass;
				}
				break;
			case ECharacterType::Support:
				SelectedClass = PS->SupporterClass.Get();
				if (SelectedClass)
				{
					UE_LOG(LogTemp, Log, TEXT("Spawning Supporter for %s"), *PS->PlayerNickname);
					return SelectedClass;
				}
				break;
			case ECharacterType::None:
				// 캐릭터를 선택하지 않은 경우 기본값(Warrior) 설정
				UE_LOG(LogTemp, Warning, TEXT("CharacterType is None for %s, setting to Warrior"), *PS->PlayerNickname);
				PS->CharacterType = ECharacterType::Warrior;
				SelectedClass = PS->WarriorClass.Get();
				if (SelectedClass)
				{
					return SelectedClass;
				}
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("CharacterType is invalid for %s, using default"), *PS->PlayerNickname);
				break;
			}
		}
	}

	// 기본 Pawn 클래스 반환 (블루프린트에서 설정된 DefaultPawnClass)
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
