// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectERNGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class AProjectERNGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	AProjectERNGameMode();

	// 플레이어의 CharacterType에 따라 적절한 Pawn 클래스 반환
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
};
