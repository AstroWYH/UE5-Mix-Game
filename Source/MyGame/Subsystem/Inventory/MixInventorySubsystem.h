// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/NoExportTypes.h"
#include "Templates/SharedPointer.h"
#include "Data/Item/MixItemData.h"
#include "MixInventorySubsystem.generated.h"

class UMixItem;
class UMixInventoryItem;

// TODO: 这个类是多余的，直接用那个就行应该
UCLASS(BlueprintType)
class UMixItemCfg : public UObject
{
	GENERATED_BODY()

public:
	void CopyFromFV(const FMixItemData* ItemData)
	{
		TID = ItemData->TID;
		Name = ItemData->Name;
		Icon = ItemData->Icon;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

};

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
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InventoryTestAddBtn();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InventoryTestRemoveBtn();

	void AddItem(TObjectPtr<UMixItem> Item, int32 PosIdx = -1);

	void RemoveItem(int32 TID);

	void ExchangeItem(int32 OldPosIdx, int32 NewPosIdx);

public:
	// 读表ItemData信息，所有的装备信息表
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TMap<int32, TObjectPtr<UMixItemCfg>> AllItemsCfg;

	// 背包InventoryItem格子数据
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TMap<int32, TObjectPtr<UMixInventoryItem>> InventoryItems;

	// 通过Pos查询TID
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TMap<int32, int32> PosToTIDMap;

	// 当前占格位
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TSet<int32> CurPosIdxes;

	// 格子数量
	const int32 KSlotNum = 6;

	// Test
	int32 Cnt = 0;
};
