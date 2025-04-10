// Fill out your copyright notice in the Description page of Project Settings.


#include "MixUIInventorySubsystem.h"

#include "Components/Image.h"
#include "Components/NamedSlot.h"
#include "Components/UniformGridPanel.h"
#include "Inventory/MixInventoryItem.h"
#include "Inventory/MixInventorySubsystem.h"
#include "UI/Inventory/MixInventoryWidget.h"
#include "UI/Inventory/MixItemWidget.h"

void UMixUIInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UMixUIInventorySubsystem::CreateUI()
{
	Super::CreateUI();

	InventoryUI = Cast<UMixInventoryWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), UIMgr->GetUIClass(GetClass()->GetFName(), "Inventory"), TEXT("Inventory")));
	if (!ensure(InventoryUI)) return;

	UNamedSlot* InventoryNS = Cast<UNamedSlot>(UIMgr->GetMainLayoutSlots()["Inventory"]);
	InventoryNS->SetContent(InventoryUI);
}

void UMixUIInventorySubsystem::BindUIEvent()
{
	Super::BindUIEvent();

	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySubsystem->OnInventoryUpdated.AddDynamic(this, &ThisClass::UpdateInventory);
}

void UMixUIInventorySubsystem::UpdateInventory()
{
	if (!ensure(InventoryUI)) return;
	if (!ensure(InventoryUI->Grid)) return;

	// 清理背包UI网格的ItemWidget
	for (const auto& ItemWidget : ItemUIPool)
	{
		InventoryUI->Grid->RemoveChild(ItemWidget.Get());
	}

	// 清理ItemUIPool引用池
	ItemUIPool.Empty();

	// 重新生成背包内全部ItemWidget
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	for (const auto& [ItemTID, InventoryItem] : InventorySubsystem->InventoryItems)
	{
		if (!ensure(InventoryItem)) continue;
		if (!ensure(InventorySubsystem->AllItemsCfg.Contains(InventoryItem->TID))) continue;
		if (!ensure(InventorySubsystem->AllItemsCfg[InventoryItem->TID]->Icon)) continue;

		// 生成ItemWidget
		UMixItemWidget* ItemWidget = Cast<UMixItemWidget>(UUserWidget::CreateWidgetInstance(*GetGameInstance(), UIMgr->GetUIClass(GetClass()->GetFName(), "Item"), FName(*FString::Printf(TEXT("Item_%d"), ItemTID))));
		if (!ensure(ItemWidget)) continue;

		ItemWidget->OwnerWidget = InventoryUI;
		ItemWidget->OwnerGrid = InventoryUI->Grid;
		ItemWidget->PosIdx = InventoryItem->PosIdx;
		ItemWidget->ItemTID = InventoryItem->TID;
		ItemWidget->Img->SetBrushFromTexture(InventorySubsystem->AllItemsCfg[InventoryItem->TID]->Icon);
		ItemUIPool.Add(ItemWidget);

		// ItemWidget添加到Grid
		int32 Row = InventoryItem->PosIdx / 3;
		int32 Col = InventoryItem->PosIdx % 3;
		InventoryUI->Grid->AddChildToUniformGrid(ItemWidget, Row, Col);
	}
}

void UMixUIInventorySubsystem::Deinitialize()
{
	UMixInventorySubsystem* InventorySubsystem = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySubsystem->OnInventoryUpdated.RemoveAll(this);

	Super::Deinitialize();
}