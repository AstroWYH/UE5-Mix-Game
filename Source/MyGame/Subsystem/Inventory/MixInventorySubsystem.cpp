// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Inventory/MixInventorySubsystem.h"
#include "Engine/DataTable.h"
#include "DataTable/MixData.h"
#include "MixItem.h"
#include "MixInventoryItem.h"

void UMixInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const FString ContextString(TEXT("Item Data Context"));
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/Data/DT_Item.DT_Item'"));
    if (!ensure(ItemDataTable)) return;

	// 获取全部FMixItemData数据
    TArray<FMixItemData*> AllFItemsCfg;
	ItemDataTable->GetAllRows<FMixItemData>(ContextString, AllFItemsCfg);
	for (FMixItemData* FItemData : AllFItemsCfg)
	{
		if (!ensure(FItemData)) return;

        TObjectPtr<UMixItemCfg> UItemData = NewObject<UMixItemCfg>();
        UItemData->CopyFromFV(FItemData);
		AllItemsCfg.Add(UItemData->TID, UItemData);
	}
}

void UMixInventorySubsystem::InventoryTestBtn()
{
    TSharedPtr<FMixItem> Item = MakeShared<FMixItem>();
    Item->XID = Cnt;

    const FString ContextString(TEXT("Item Data Context"));
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/Data/DT_Item.DT_Item'"));
    if (!ensure(ItemDataTable)) return;
	const FMixItemData* ItemData = ItemDataTable->FindRow<FMixItemData>(FName(FString::Printf(TEXT("%d"), Cnt)), ContextString);
	Item->ItemData = ItemData;

    // 模拟添加第1、2件物品
    AddItem(Item);
    Cnt++;
}

void UMixInventorySubsystem::AddItem(TSharedPtr<FMixItem> Item)
{
    if (!ensure(Item.IsValid())) return;
    int32 TID = Item->ItemData->TID;

    if (InventoryItems.Contains(TID))
    {
        if (!ensure(InventoryItems[TID])) return;
        InventoryItems[TID]->Amount++;
    }
    else
    {
        TObjectPtr<UMixInventoryItem> NewInventoryItem = NewObject<UMixInventoryItem>();
		NewInventoryItem->Init(TID, 1, NextPosIdx);
		InventoryItems.Add(TID, NewInventoryItem);
        NextPosIdx++;
    }

    // 暂传一个参数测试
    OnInventoryUpdated.Broadcast(100);
}

void UMixInventorySubsystem::Deinitialize()
{
    Super::Deinitialize();

    InventoryItems.Empty();
    Cnt = 1;
}