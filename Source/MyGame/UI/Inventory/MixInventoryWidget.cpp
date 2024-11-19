// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/MixInventoryWidget.h"
#include "Inventory/MixInventorySubsystem.h"
#include "Subsystem/Inventory/MixItem.h"

void UMixInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!ensure(Grid)) return;
}

void UMixInventoryWidget::DragToOtherEmptySlot(int32 TID, int32 OldPosIdx, int32 NewPosIdx)
{
	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySys->RemoveItem(TID);

	TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
	Item->TID = TID;
	if (!ensure(InventorySys->AllItemsCfg.Contains(TID))) return;
	Item->ItemCfg = InventorySys->AllItemsCfg[TID];
	InventorySys->AddItem(Item, NewPosIdx);
}

void UMixInventoryWidget::DragToExchange(int32 OldPosIdx, int32 NewPosIdx)
{
	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySys->ExchangeItem(OldPosIdx, NewPosIdx);
}