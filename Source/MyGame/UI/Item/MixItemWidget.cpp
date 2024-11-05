// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Item/MixItemWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

/*
FReply UMixItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// ��¼��Ʒ��λ�ú���갴��ʱ��λ��
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
		// ������Ʒ��λ�ã�ʹ��������
		FVector2D NewPosition = InMouseEvent.GetScreenSpacePosition() - DragOffset;
		SetPositionInViewport(NewPosition); // �������λ�ø�����Ʒλ��

		return FReply::Handled();
	}

	return FReply::Unhandled();
}

FReply UMixItemWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsDragging = false;

		// ��Ʒ������λ�ô��������õ��ĸ����ӵ�
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
