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
	void NativeConstruct();

	void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	bool bIsDragging = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	int32 PosIdx = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	int32 ItemTID = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	TWeakObjectPtr<UUserWidget> OwnerWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ItemWidget")
	TWeakObjectPtr<class UUniformGridPanel> OwnerGrid;

private:
	int32 KNumRows = 2;
	int32 KNumColumns = 3;

};
