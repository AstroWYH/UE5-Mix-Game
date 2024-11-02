// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MixInventorySubsystem.generated.h"

struct FMixItemData;
class FMixItem;
class FMixInventoryItem;

/**
 * 
 */
UCLASS()
class MYGAME_API UMixInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void Initialize(FSubsystemCollectionBase& Collection) override;

	void Deinitialize() override;

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMixOnInventoryUpdated);
	UPROPERTY(BlueprintAssignable)
    FMixOnInventoryUpdated OnInventoryUpdated;

public:
	void AddItem(TSharedPtr<FMixItem> Item);

private:
	// 读表ItemData信息
	TArray<FMixItemData*> AllItemsCfg;
	TMap<int32, FMixItemData*> AllItemsMapCfg;

	// 背包InventoryItem格子数据
	TMap<int32, TSharedPtr<FMixInventoryItem>> InventoryItems;
	int32 NextPosIdx = 0;

};
