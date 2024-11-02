// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Inventory/MixInventorySubsystem.h"
#include "Engine/DataTable.h"
#include "DataTable/MixData.h"
#include "MixItem.h"
#include "MixInventoryItem.h"
// #include "Subsystem/UI/MixUISubsystem.h"

void UMixInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
	// Collection.InitializeDependency(UMixUISubsystem::StaticClass());

    static const FString ContextString(TEXT("Item Data Context"));
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/DT_Item.DT_Item'"));
    if (ItemDataTable)
    {
        // Test
		const FMixItemData* ItemData = ItemDataTable->FindRow<FMixItemData>(FName(TEXT("1")), ContextString);
		if (ItemData)
        {
            UE_LOG(LogTemp, Log, TEXT("Item Name: %s"), *ItemData->Name);
        }
		else
        {
            UE_LOG(LogTemp, Warning, TEXT("Item not found!"));
        }

        // 获取全部FMixItemData数据
		ItemDataTable->GetAllRows<FMixItemData>(ContextString, AllItemsCfg);
		for (FMixItemData* Item : AllItemsCfg)
        {
			if (Item)
            {
                AllItemsMapCfg.Add(Item->TID, Item);
			}
		}
    }
}

void UMixInventorySubsystem::AddItem(TSharedPtr<FMixItem> Item)
{
    if (!ensure(Item.IsValid())) return;
    int32 TID = Item->ItemData->TID;

    if (InventoryItems.Contains(TID))
    {
		if (!ensure(InventoryItems[TID].IsValid())) return;
        InventoryItems[TID]->Amount++;
    }
    else
    {
        InventoryItems.Add(TID, MakeShared<FMixInventoryItem>(TID, 1, NextPosIdx));
        NextPosIdx++;
    }

    OnInventoryUpdated.Broadcast();
}

void UMixInventorySubsystem::Deinitialize()
{
    Super::Deinitialize();
}