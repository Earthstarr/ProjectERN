// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERNItemEnums.h"
#include "Engine/DataTable.h"
#include "ERNItemTable.generated.h"

class UItemDataAssetBase;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FERNItemTable : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	// 고유 Key값
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID = NAME_None;
	
	// 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::GetEmpty();
	
	// 종류
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::None;
	
	// 무기 종류(무기일 때)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponType WeaponType = EWeaponType::None;
	
	// 사용 가능 여부(소모품일 때)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bUsable = false;
	
	// 등급
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemGrade Grade = EItemGrade::None;
	
	// 해당 아이템의 DataAsset(Icon Texture, Mesh 등)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UItemDataAssetBase> DataAsset = nullptr;
		
};
