// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/Inventory/MixInventorySubsystem.h"
#include "Data/Item/MixItemData.h"
#include "MixItem.h"
#include "MixInventoryItem.h"
#include "Data/MixDataSubsystem.h"
#include "Engine/DataTable.h"

void UMixInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

	UMixDataSubsystem* DataSys = GetGameInstance()->GetSubsystem<UMixDataSubsystem>();
	// TODO: AssetMgr
    TArray<FMixItemData*> AllFItemsCfg = DataSys->LoadDataTableFromPath<FMixItemData>(TEXT("/Script/Engine.DataTable'/Game/MixGame/UI/Inventory/Data/DT_Item.DT_Item'"), TEXT("ItemDataContext"));

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
    // Test
    int32 TestTID = -1;
    if (Cnt == 0)
    {
        TestTID = 100;
    }
    else if (Cnt == 1)
    {
        TestTID = 101;
    }

    TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
    Item->TID = TestTID;
    if (!ensure(AllItemsCfg.Contains(TestTID))) return;
    Item->ItemCfg = AllItemsCfg[TestTID];

    // ģ����ӵ�1��2����Ʒ
    AddItem(Item);
    Cnt++;
}

void UMixInventorySubsystem::InventoryTestRemoveBtn()
{
    Cnt--;

    // Test
    int32 TestTID = -1;
    if (Cnt == 0)
    {
        TestTID = 100;
    }
    else if (Cnt == 1)
    {
        TestTID = 101;
    }

    RemoveItem(TestTID);
}

void UMixInventorySubsystem::AddItem(TObjectPtr<UMixItem> Item, int32 PosIdx)
{
    // ���ܳ�����������
    if (!ensure(InventoryItems.Num() < KSlotNum)) return;

    if (!ensure(Item)) return;
    int32 TID = Item->TID;

    if (InventoryItems.Contains(TID))
    {
        if (!ensure(InventoryItems[TID])) return;
        InventoryItems[TID]->Amount++;
    }
    else
    {
        TObjectPtr<UMixInventoryItem> NewInventoryItem = NewObject<UMixInventoryItem>();
        int32 SavePosIdx = 0;

        // �Զ����������1����λ���
        if (PosIdx == -1)
        {
            // ��ΪRemoveλ�õĲ�ȷ���ԣ�ÿ�����¼���SavePosIdx��λ��
            for (int32 Idx = 0; Idx < KSlotNum; Idx++)
            {
                if (CurPosIdxes.Contains(Idx))
                {
                    SavePosIdx++;
                }
                else
                {
                    break;
                }
            }
        }
        // ָ��λ�ô��
        else
        {
            SavePosIdx = PosIdx;
        }

		NewInventoryItem->Init(TID, 1, SavePosIdx);
		InventoryItems.Add(TID, NewInventoryItem);
        CurPosIdxes.Add(SavePosIdx);
        PosToTIDMap.Add(SavePosIdx, TID);
    }

    OnInventoryUpdated.Broadcast();
}

void UMixInventorySubsystem::RemoveItem(int32 TID)
{
    if (!ensure(InventoryItems.Contains(TID))) return;
    if (!ensure(InventoryItems[TID])) return;

    CurPosIdxes.Remove(InventoryItems[TID]->PosIdx);
    PosToTIDMap.Remove(InventoryItems[TID]->PosIdx);
    InventoryItems.Remove(TID);
    OnInventoryUpdated.Broadcast();
}

void UMixInventorySubsystem::ExchangeItem(int32 OldPosIdx, int32 NewPosIdx)
{
    if (!ensure(CurPosIdxes.Contains(OldPosIdx))) return;
    if (!ensure(CurPosIdxes.Contains(NewPosIdx))) return;
    if (!ensure(PosToTIDMap.Contains(OldPosIdx))) return;
    if (!ensure(PosToTIDMap.Contains(NewPosIdx))) return;

    int32 OldTID = PosToTIDMap[OldPosIdx];
    int32 NewTID = PosToTIDMap[NewPosIdx];

	TObjectPtr<UMixInventoryItem>& OldInventoryItem = InventoryItems.FindOrAdd(OldTID);
    if (!ensure(OldInventoryItem)) return;
    OldInventoryItem->PosIdx = NewPosIdx;

    TObjectPtr<UMixInventoryItem>& NewInventoryItem = InventoryItems.FindOrAdd(NewTID);
    if (!ensure(NewInventoryItem)) return;
    NewInventoryItem->PosIdx = OldPosIdx;

    PosToTIDMap[OldPosIdx] = NewTID;
    PosToTIDMap[NewPosIdx] = OldTID;

    OnInventoryUpdated.Broadcast();
}

void UMixInventorySubsystem::Deinitialize()
{
    Super::Deinitialize();

    InventoryItems.Empty();
    CurPosIdxes.Empty();
    PosToTIDMap.Empty();
    Cnt = 1;
}