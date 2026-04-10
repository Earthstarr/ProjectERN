// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Inventory/ERNInventoryComponent.h"
#include "Net/UnrealNetwork.h"

UERNInventoryComponent::UERNInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UERNInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UERNInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UERNInventoryComponent, Items);
}

void UERNInventoryComponent::Server_AddItem_Implementation(FName ItemID, int32 Count)
{
	// TODO: 아이템 추가 로직
	UE_LOG(LogTemp, Log, TEXT("Server_AddItem: %s x%d"), *ItemID.ToString(), Count);
}

void UERNInventoryComponent::Server_RemoveItem_Implementation(int32 SlotIndex, int32 Count)
{
	// TODO: 아이템 제거 로직
	UE_LOG(LogTemp, Log, TEXT("Server_RemoveItem: Slot %d, Count %d"), SlotIndex, Count);
}

void UERNInventoryComponent::Server_UseItem_Implementation(int32 SlotIndex)
{
	// TODO: 아이템 사용 로직
	UE_LOG(LogTemp, Log, TEXT("Server_UseItem: Slot %d"), SlotIndex);
}
