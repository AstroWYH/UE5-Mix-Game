// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MixInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMixInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DragToOtherEmptySlot(int32 TID, int32 OldPosIdx, int32 NewPosIdx);

	void DragToExchange(int32 OldPosIdx, int32 NewPosIdx);
};
