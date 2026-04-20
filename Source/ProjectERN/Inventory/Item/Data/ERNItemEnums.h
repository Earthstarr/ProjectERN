// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ERNItemEnums.generated.h"

// Item Type
UENUM(BlueprintType)
enum class EItemType : uint8
{
	None       UMETA(Hidden),
	// 장착 가능(장비)
	Equipable  UMETA(DisplayName="Equipment"),
	// 소비 가능(소모품)
	Consumable UMETA(DisplayName="Consumable")
};

// Item Grade
UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	None      UMETA(Hidden),
	Common    UMETA(DisplayName="Common"),
	Uncommon  UMETA(DisplayName="Uncommon"),
	Rare      UMETA(DisplayName="Rare"),
	Legendary UMETA(DisplayName="Legendary")
};

// WeaponType
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	None   UMETA(DisplayName="None"),
	Sword  UMETA(DisplayName="Sword"),
	Staff  UMETA(DisplayName="Staff"),
	Rapier UMETA(DisplayName="Rapier")
};
