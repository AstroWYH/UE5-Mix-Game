// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/NoExportTypes.h"
#include "Templates/SharedPointer.h"
#include "MixData.h"
#include "MixInventorySubsystem.generated.h"

class FMixItem;
class UMixInventoryItem;

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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMixOnInventoryUpdated, int32, TID);
	UPROPERTY(BlueprintAssignable)
    FMixOnInventoryUpdated OnInventoryUpdated;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InventoryTestBtn();

	void AddItem(TSharedPtr<FMixItem> Item);

public:
	// 读表ItemData信息
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TMap<int32, TObjectPtr<UMixItemCfg>> AllItemsCfg;

	// 背包InventoryItem格子数据
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TMap<int32, TObjectPtr<UMixInventoryItem>> InventoryItems;

	// 新入背包的格子位置
	int32 NextPosIdx = 0;

	// Test
	int32 Cnt = 1;
};
