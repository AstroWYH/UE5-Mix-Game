// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MixItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
/*
	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;*/

	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	bool bIsDragging = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	int32 PosIdx = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	TWeakObjectPtr<UUserWidget> OwnerWidget;

private:
/*
	FVector2D DragStartPosition;  // 物品开始拖动时的位置
	FVector2D DragOffset;         // 鼠标与物品的位置偏差*/

};
