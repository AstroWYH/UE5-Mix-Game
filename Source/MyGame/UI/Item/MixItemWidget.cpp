// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Item/MixItemWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/WidgetTree.h"
#include "Inventory/MixInventorySubsystem.h"
#include "Inventory/MixItem.h"

void UMixItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMixItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOpr = NewObject<UDragDropOperation>(GetTransientPackage());
	DragDropOpr->DefaultDragVisual = this;
	DragDropOpr->Payload = this;
	DragDropOpr->Pivot = EDragPivot::CenterCenter;
	OutOperation = DragDropOpr;

	SetVisibility(ESlateVisibility::Hidden);
}

void UMixItemWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

bool UMixItemWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

void UMixItemWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

bool UMixItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UMixItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
// 	if (!ensure(OwnerWidget.IsValid())) return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
// 	OwnerGrid = Cast<UUniformGridPanel>(OwnerWidget->WidgetTree->FindWidget(FName(TEXT("Grid"))));

	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	if (!ensure(OwnerGrid.IsValid())) return;

	FVector2D MousePosition = InDragDropEvent.GetScreenSpacePosition();
	FVector2D GridMousePosition = OwnerGrid->GetCachedGeometry().AbsoluteToLocal(MousePosition);
	FVector2D GirdSize = OwnerGrid->GetCachedGeometry().GetLocalSize();

	float CellWidth = GirdSize.X / KNumColumns;
	float CellHeight = GirdSize.Y / KNumRows;

	int32 Row = FMath::FloorToInt(GridMousePosition.Y / CellHeight);
	int32 Col = FMath::FloorToInt(GridMousePosition.X / CellWidth);
	int32 CurMousePosIdx = Row * KNumColumns + Col;

	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();

	TSet<int32> AllPosIdx{ 0,1,2,3,4,5 };
	// 拖到原格子松手 || 拖到外部空间松手 
	if (CurMousePosIdx == PosIdx || !AllPosIdx.Contains(CurMousePosIdx))
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	// 拖到其他空格子松手
	else if (!InventorySys->CurPosIdxes.Contains(CurMousePosIdx))
	{

	}
	// 拖到其他非空格子松手
	else if (InventorySys->CurPosIdxes.Contains(CurMousePosIdx))
	{

	}

	InventorySys->RemoveItem(ItemTID);
	TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
	Item->TID = ItemTID;
	Item->ItemCfg = InventorySys->AllItemsCfg[ItemTID];
	InventorySys->AddItem(Item, CurMousePosIdx);

// 	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
// 	TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
// 	Item->TID = ItemTID;
// 	Item->ItemCfg = InventorySys->AllItemsCfg[ItemTID];
// 	InventorySys->AddItem(Item, PosIdx);

}

FReply UMixItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
