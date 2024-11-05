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

	// ��ȡȫ��FMixItemData����
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

void UMixInventorySubsystem::InventoryTestAddBtn()
{
    TSharedPtr<FMixItem> Item = MakeShared<FMixItem>();
    Item->XID = Cnt;

    const FString ContextString(TEXT("Item Data Context"));
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/Data/DT_Item.DT_Item'"));
    if (!ensure(ItemDataTable)) return;

	const FMixItemData* ItemData = ItemDataTable->FindRow<FMixItemData>(FName(FString::Printf(TEXT("%d"), Cnt)), ContextString);
    if (!ensure(ItemData)) return;
	Item->ItemData = ItemData;

    // ģ����ӵ�1��2����Ʒ
    AddItem(Item);
    Cnt++;
}

void UMixInventorySubsystem::InventoryTestRemoveBtn()
{
    Cnt--;
    TSharedPtr<FMixItem> Item = MakeShared<FMixItem>();
    Item->XID = Cnt;

    const FString ContextString(TEXT("Item Data Context"));
    UDataTable* ItemDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/Data/DT_Item.DT_Item'"));
    if (!ensure(ItemDataTable)) return;

    const FMixItemData* ItemData = ItemDataTable->FindRow<FMixItemData>(FName(FString::Printf(TEXT("%d"), Cnt)), ContextString);
    if (!ensure(ItemData)) return;
    Item->ItemData = ItemData;

    // ģ����ӵ�1��2����Ʒ
    RemoveItem(Item);
}

void UMixInventorySubsystem::AddItem(TSharedPtr<FMixItem> Item)
{
    // ���ܳ�����������
    if (!ensure(NextPosIdx < KSlotNum)) return;
    if (!ensure(InventoryItems.Num() < KSlotNum)) return;

    if (!ensure(Item.IsValid())) return;
    if (!ensure(Item->ItemData)) return;
    int32 TID = Item->ItemData->TID;

    if (InventoryItems.Contains(TID))
    {
        if (!ensure(InventoryItems[TID])) return;
        InventoryItems[TID]->Amount++;
    }
    else
    {
        TObjectPtr<UMixInventoryItem> NewInventoryItem = NewObject<UMixInventoryItem>();
        
        // ��ΪRemoveλ�õĲ�ȷ���ԣ�ÿ�����¼���NextPosIdx��λ��
		NextPosIdx = 0;
        for (int32 Idx = 0; Idx < KSlotNum; Idx++)
        {
            if (CurPosIdxes.Contains(Idx))
            {
                NextPosIdx++;
            }
            else
            {
                break;
            }
        }

		NewInventoryItem->Init(TID, 1, NextPosIdx);
		InventoryItems.Add(TID, NewInventoryItem);
        CurPosIdxes.Add(NextPosIdx);
    }

    OnInventoryUpdated.Broadcast(true);
}

void UMixInventorySubsystem::RemoveItem(TSharedPtr<FMixItem> Item)
{
    if (!ensure(Item.IsValid())) return;
    if (!ensure(Item->ItemData)) return;
    int32 TID = Item->ItemData->TID;

    if (!ensure(InventoryItems.Contains(TID))) return;
    if (!ensure(InventoryItems[TID])) return;

    CurPosIdxes.Remove(InventoryItems[TID]->PosIdx);
    InventoryItems.Remove(TID);
    OnInventoryUpdated.Broadcast(false);
}

void UMixInventorySubsystem::Deinitialize()
{
    Super::Deinitialize();

    InventoryItems.Empty();
    CurPosIdxes.Empty();
	NextPosIdx = 0;
    Cnt = 1;
}