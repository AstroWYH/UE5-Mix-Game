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
	if (ItemTID == -1) return;

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOpr = NewObject<UDragDropOperation>(GetTransientPackage());
	DragDropOpr->DefaultDragVisual = this;
	DragDropOpr->Payload = this;
	DragDropOpr->Pivot = EDragPivot::CenterCenter;
	OutOperation = DragDropOpr;

	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySys->RemoveItem(ItemTID);
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
	if (ItemTID == -1) return false;

	if (!ensure(OwnerWidget.IsValid())) return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	OwnerGrid = Cast<UUniformGridPanel>(OwnerWidget->WidgetTree->FindWidget(FName(TEXT("Grid"))));

	FVector2D MousePosition = InDragDropEvent.GetScreenSpacePosition();
	FVector2D GridMousePosition = OwnerGrid->GetCachedGeometry().AbsoluteToLocal(MousePosition);
	FVector2D GirdSize = OwnerGrid->GetCachedGeometry().GetLocalSize();

	float CellWidth = GirdSize.X / KNumColumns;
	float CellHeight = GirdSize.Y / KNumRows;

	int32 Row = FMath::FloorToInt(GridMousePosition.Y / CellHeight);
	int32 Col = FMath::FloorToInt(GridMousePosition.X / CellWidth);
	int32 NewPosIdx = Row * KNumColumns + Col;

	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	InventorySys->RemoveItem(ItemTID);
	TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
	Item->TID = ItemTID;
	Item->ItemCfg = InventorySys->AllItemsCfg[ItemTID];
	InventorySys->AddItem(Item, NewPosIdx);

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UMixItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (ItemTID == -1) return;

	UMixInventorySubsystem* InventorySys = GetGameInstance()->GetSubsystem<UMixInventorySubsystem>();
	TObjectPtr<UMixItem> Item = NewObject<UMixItem>();
	Item->TID = ItemTID;
	Item->ItemCfg = InventorySys->AllItemsCfg[ItemTID];
	InventorySys->AddItem(Item, PosIdx);

	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

FReply UMixItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
