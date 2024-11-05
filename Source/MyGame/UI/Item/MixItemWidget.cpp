// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Item/MixItemWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

/*
FReply UMixItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 记录物品的位置和鼠标按下时的位置
		DragStartPosition = InGeometry.GetAbsolutePosition();
		DragOffset = InMouseEvent.GetScreenSpacePosition() - DragStartPosition;

		bIsDragging = true;
		TSharedRef<SWidget> SWidget = TakeWidget();
		return FReply::Handled().CaptureMouse(SWidget);
	}

	return FReply::Unhandled();
}

FReply UMixItemWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bIsDragging)
	{
		// 更新物品的位置，使其跟随鼠标
		FVector2D NewPosition = InMouseEvent.GetScreenSpacePosition() - DragOffset;
		SetPositionInViewport(NewPosition); // 根据鼠标位置更新物品位置

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UMixItemWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsDragging = false;

		// 物品的最终位置处理，检查放置到哪个格子等
		FVector2D DropPosition = InMouseEvent.GetScreenSpacePosition();
		return FReply::Handled().ReleaseMouseCapture();
	}

	return FReply::Unhandled();
}*/

void UMixItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOpr = NewObject<UDragDropOperation>(GetTransientPackage());
	DragDropOpr->DefaultDragVisual = this;
	DragDropOpr->Payload = this;
	DragDropOpr->Pivot = EDragPivot::CenterCenter;

	OutOperation = DragDropOpr;
}

bool UMixItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

FReply UMixItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
